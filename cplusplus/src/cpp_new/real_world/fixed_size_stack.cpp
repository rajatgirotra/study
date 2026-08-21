/*
* Fixed-size stack: Build a class template Stack<T, std::size_t N> backed by std::array.
* Implement push, pop, top, empty, size.
*/

#include <print>
#include <array>
#include <iostream>
#include <string>
#include <random>
#include <cassert>
#include <utility>
#include <cstring>
using namespace std;

class Item
{
private:
    char* m_buffer{};

public:
    explicit Item() : m_buffer(new char[16])
    {
        std::cout << "created: " << *this << std::endl;
    }

    ~Item()
    {
        std::cout << "destructed: " << *this << std::endl;
        if (m_buffer)
            delete[] m_buffer;
        m_buffer = nullptr;
    }

    Item(const Item&) : m_buffer(new char[16])
    {
        std::cout << "copy constructed at: " << *this << std::endl;
    }

    Item(Item&& rhs) noexcept
    {
        std::swap(m_buffer, rhs.m_buffer);
        std::cout << "move constructed at: " << *this << std::endl;
    }

    Item& operator=(const Item& rhs)
    {
        if (this != &rhs)
        {
            std::memcpy(m_buffer, rhs.m_buffer, 16);
            std::cout << "copy assigned at: " << *this << std::endl;
        }
        return *this;
    }

    Item& operator=(Item&& rhs)
    {
        if (this != &rhs)
        {
            std::swap(m_buffer, rhs.m_buffer);
            std::cout << "move assigned at: " << *this << std::endl;
        }
        return *this;
    }

    friend std::ostream& operator << (std::ostream& os, const Item& item)
    {
        os << "Item at " << std::addressof(item.m_buffer);
        return os;
    }
};

template <typename T, auto N>
class Stack
{
    // std::array<T, N> m_arr;
    alignas(T) std::byte m_storage[N * sizeof(T)]{};
    size_t m_tos = 0;

    // [[nodiscard]] const T* slot(size_t idx) const noexcept
    // {
    //     assert(idx < N);
    //     return std::launder(reinterpret_cast<const T*>(m_storage + idx * sizeof(T)));
    // }
    //
    // T* slot(size_t idx) noexcept
    // {
    //     assert(idx < N);
    //     return std::launder(reinterpret_cast<T*>(m_storage + idx * sizeof(T)));
    // }

    [[nodiscard]] auto* slot(this auto&& self, size_t idx) noexcept
    {
        assert(idx < N);
        using Ptr = std::conditional_t<std::is_const_v<std::remove_reference_t<decltype(self)>>, const T*, T*>;
        return std::launder(reinterpret_cast<Ptr>(self.m_storage + idx * sizeof(T)));
    }

public:

    using value_type = T;
    using size_type = size_t;
    using reference = value_type&;
    using const_reference = const value_type&;

    [[nodiscard]] bool empty() const { return m_tos == 0; }
    [[nodiscard]] bool full() const { return m_tos == N; }
    [[nodiscard]] size_type size() const { return m_tos; }
    [[nodiscard]] constexpr static auto capacity() noexcept { return N; }

    Stack() = default;

    ~Stack()
    {
        while (!empty())
            std::destroy_at(slot(--m_tos));
    }

    [[nodiscard]] decltype(auto) top(this auto&& self)
    {
        if (self.empty())
            throw std::underflow_error{"failed to return top element in stack. stack empty!"};
        return *self.slot(self.m_tos-1);
    }

    void pop() noexcept
    {
        if (!empty())
        {
            std::destroy_at(slot(--m_tos));
        }
    }

    void push(const T& elem)
    {
        if (full())
            throw std::overflow_error{"failed to push element into stack. stack full!"};
        std::construct_at(slot(m_tos), elem);
        ++m_tos;
    }

    void push(T&& elem)
    {
        if (full())
            throw std::overflow_error{"failed to push element into stack. stack full!"};
        std::construct_at(slot(m_tos), std::move(elem));
        ++m_tos;
    }

    template <typename... Args>
    void emplace(Args&&... args)
    {
        if (full())
            throw std::overflow_error{"failed to push element into stack. stack full!"};
        std::construct_at(slot(m_tos), std::forward<Args>(args)...);
        ++m_tos;
    }

    Stack(const Stack& rhs) noexcept
    {
        for (int i = 0; i < rhs.m_tos; ++i)
        {
            std::construct_at(slot(i), *rhs.slot(i));
        }
        m_tos = rhs.m_tos;
    }

    Stack& operator = (Stack& rhs) noexcept
    {
        if (this != &rhs)
        {
            while (!empty()) pop();
            for (int i = 0; i < rhs.m_tos; ++i)
            {
                std::construct_at(slot(i), *rhs.slot(i));
            }
            m_tos = rhs.m_tos;
        }
        return *this;
    }

    Stack(Stack&& rhs) noexcept
    {
        std::swap(m_storage, rhs.m_storage);
        std::swap(m_tos, rhs.m_tos);
    }

    Stack& operator = (Stack&& rhs) noexcept
    {
        if (this != &rhs)
        {
            std::swap(m_storage, rhs.m_storage);
            std::swap(m_tos, rhs.m_tos);
        }
        return *this;
    }
};

int main()
{
    srand(time(nullptr));
    Stack<Item, 10> stack;
    try
    {
        for (int i = 0; i < 10; ++i)
        {
            stack.emplace();
        }
        stack.emplace();
    } catch (const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    try
    {
        while (!stack.empty())
        {
            std::cout << "Top element: " << stack.top() << std::endl;
            stack.pop();
        }
        stack.pop();
    } catch (const std::exception& e)
    {
        std::cout << "error: " << e.what() << std::endl;
    }

    Stack<Item, 2> old_stack;
    old_stack.emplace();
    Stack<Item, 2> new_stack;
    new_stack.emplace(); new_stack.emplace();
    old_stack = new_stack;

}