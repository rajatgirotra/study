#pragma once

#include "PriceBucketSet.hpp"
#include <iterator>
#include <type_traits>

namespace raj {
    template <typename PriceBucketSetType = ::raj::PriceBucketSet>
    class PriceBucketManager {
    private:
        PriceBucketSetType m_buckets;
        using price_bucket_type = typename PriceBucketSetType::price_bucket_type;

    public:
        price_bucket_type addBucket(uint64_t price) {
            auto pb = std::make_shared<typename price_bucket_type::element_type>(price);
            return m_buckets.insert(std::make_pair(price, pb));
        }

        bool removeBucket(uint64_t price) { return m_buckets.remove(price); }

        price_bucket_type nextBucket(uint64_t price) { return m_buckets.successor(price); }

        price_bucket_type prevBucket(uint64_t price) { return m_buckets.predecessor(price); }

        price_bucket_type findBucket(uint64_t price) { return m_buckets.find(price); }

        uint64_t minPrice() const noexcept { return m_buckets.minPrice();  }
        uint64_t maxPrice() const noexcept { return m_buckets.maxPrice();  }

        friend class iterator;

        template <Side BidAskTrait>
        class iterator {
        public:
            using iterator_category_tag = std::bidirectional_iterator_tag;
            using value_type = uint64_t; // iterator over the price level
            using difference_type = std::ptrdiff_t;
            using pointer = uint64_t*;
            using reference = uint64_t&;
        private:
            PriceBucketManager& pbm;
            uint64_t m_price{}; // end is denoted by value 0.

        public:
            iterator(PriceBucketManager& arg, bool isEnd = false) : pbm(arg) {
                m_price = (isEnd ? 0 : initialPrice());
            }

            uint64_t initialPrice() noexcept {
                if constexpr (BidAskTrait == Side::BUY) {
                    return pbm.maxPrice();
                } else {
                    return pbm.minPrice();
                }
            }

            uint64_t operator * () const noexcept {
                return m_price;
            }

            iterator& operator ++ () noexcept {
                price_bucket_type pb{};
                if constexpr (BidAskTrait == Side::BUY) {
                    pb = pbm.prevBucket(m_price);
                } else {
                    pb = pbm.nextBucket(m_price);
                }
                if(!pb) {
                    m_price = 0;
                } else {
                    m_price = pb->pricePoint();
                }
                return *this;
            }

            iterator operator ++ (int) noexcept {
                auto tmp = *this;
                this->operator++();
                return tmp;
            }

            bool operator == (const iterator& rhs) const noexcept {
                return (m_price == rhs.m_price);
            }
            bool operator != (const iterator& rhs) const noexcept {
                return !operator==(rhs);
            }
        };

        template <Side BidAskTrait>
        auto begin() { return iterator<BidAskTrait>(*this); }

        template <Side BidAskTrait>
        auto end() { return iterator<BidAskTrait>(*this, true); }
    };
}