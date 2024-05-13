#pragma once

#include <type_traits>
#include <atomic>
#include <cstdint>
#include <concepts>


class Block {
private:
    std::atomic<int32_t> m_use_count;
    std::atomic<int32_t> m_weak_count;

public:
    Block() noexcept : m_use_count(1), m_weak_count(1) {}
    virtual ~Block() noexcept = default;

    int32_t use_count() const noexcept { return m_use_count.load(); }
    bool unique() const noexcept { return use_count() == 1; }

    void release() {
        constexpr long long unique_ref = 1LL + (1LL << 32);
        std::atomic<long long> both_counts(*(reinterpret_cast<long long*>(&m_use_count)));
        if (std::atomic_load(&both_counts) == unique_ref) {
            dispose();
            destroy();
        }
    }

    virtual void dispose() noexcept  = 0;

    virtual void destroy() noexcept {
        delete this;
    }

    void add_reference() noexcept {
        m_use_count.fetch_add(1);
    }

    void remove_reference() noexcept {
        m_use_count.fetch_sub(1);
        release();
    }
};

template <typename Ptr>
class BlockDefaultDeleter : public Block {
public:
    explicit BlockDefaultDeleter(Ptr* p) : m_ptr(p) {}

    void dispose() noexcept override {
        delete m_ptr;
    }
private:
    Ptr* m_ptr;
};

class BlockCustomDeleter : public Block {
};

class ArrayDeleter {
    template <typename Y>
    void operator ()(Y* ptr) const {
        delete[] ptr;
    }
};

class SPControlBlock {
private:
    Block* m_block_impl{};

public:
    int32_t use_count() const noexcept { return m_block_impl ? m_block_impl->use_count() : 1; }
    bool unique() const noexcept { return m_block_impl ? m_block_impl->unique() : true ; }

    constexpr SPControlBlock() noexcept : m_block_impl{nullptr} {}

    template <typename Y>
    SPControlBlock(Y* ptr) {
        m_block_impl = new BlockDefaultDeleter(ptr);
    }

    template <typename Y>
    SPControlBlock(Y* ptr, std::true_type) : SPControlBlock(ptr, ArrayDeleter{}) {}

    template <typename Y>
    SPControlBlock(Y* ptr, std::false_type) : SPControlBlock(ptr) {}

    template <typename Y, typename Deleter>
    SPControlBlock(Y* ptr, Deleter d) noexcept {
//        m_block_impl = new BlockCustomDeleter(ptr, std::move(d));
    }

    ~SPControlBlock() noexcept {
        if(m_block_impl) {
            m_block_impl->release();
        }
    }

    void swap(SPControlBlock& block) {
        std::swap(m_block_impl, block.m_block_impl);
    }
};

template <typename T>
class SharedPtr {
    using element_type = std::remove_extent_t<T>;

    template <typename... Args>
    using Constructible = std::enable_if_t<std::is_constructible_v<SharedPtr<T>, Args...>>;

public:
    // swap
    void swap(SharedPtr& rhs) noexcept {
        std::swap(m_ptr, rhs.m_ptr);
        m_control_block.swap(rhs.m_control_block);
    }

    void reset() noexcept {
        SharedPtr().swap(*this);
    }

    explicit operator bool() const noexcept {
        return m_ptr != nullptr;
    }

    element_type* operator ->() const noexcept { return *m_ptr; }
    element_type& operator *() const noexcept { return m_ptr; }

    template <typename Y>
    void reset(Y* ptr) noexcept {
        SharedPtr(ptr).swap(*this);
    }

    int32_t use_count() const noexcept { return m_control_block.use_count(); }
    bool unique() const noexcept { return m_control_block.unique(); }

    // ctor
    constexpr SharedPtr() noexcept : m_ptr{nullptr}, m_control_block() {}

    template <typename Y>
    SharedPtr(Y* ptr) noexcept : m_ptr(ptr), m_control_block(ptr, std::is_array<T>::type) {}

    template <typename Y, typename Deleter>
    SharedPtr(Y* ptr, Deleter d) noexcept : m_ptr(ptr), m_control_block(ptr, std::move(d)) {}

    template <typename Deleter>
    SharedPtr(std::nullptr_t, Deleter d) noexcept : m_ptr(nullptr), m_control_block(nullptr, std::move(d)) {}

    // copy constructor
    SharedPtr(const SharedPtr&) = default;
    SharedPtr& operator = (const SharedPtr&) = default;

    template <typename Y, typename = Constructible<const SharedPtr<Y>&>>
    SharedPtr(const SharedPtr<Y>& rhs) : m_ptr(rhs.m_ptr), m_control_block(rhs.m_control_block) {}

    // move ctor
    SharedPtr(SharedPtr&& rhs) noexcept = default;

    SharedPtr& operator = (SharedPtr&& rhs) noexcept {
        if(this != &rhs) {
          rhs.swap(*this);
        }
        return *this;
    }

    ~SharedPtr() = default;

private:
    T* m_ptr{};
    SPControlBlock m_control_block;
};