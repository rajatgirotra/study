#pragma once

#include "PriceBucketManager.hpp"

namespace raj {

    template <Side BidAskTrait>
    class Book {
    private:
        PriceBucketManager<> m_pbm;
    public:
        void addBucket(uint32_t price) {
            if(m_pbm.findBucket(price) == nullptr) {
                m_pbm.addBucket(price);
            }
        }
        void addOrder(const Order& o) {
            auto bucket = m_pbm.addBucket(o.m_price);
            bucket->addOrder(o);
        }

        void removeOrder(const Order& o) {
            auto bucket = m_pbm.findBucket(o.m_price);
            bucket->removeOrder(o.m_orderid);
            if (bucket->getTotalCount() == 0) {
                m_pbm.removeBucket(o.m_price);
            }
        }

        auto getBucket(uint32_t price) {
            return m_pbm.findBucket(price);
        }

        void removeOrder(uint32_t orderid) {
    //  TODO.
//            auto bucket = m_pbm.findBucket(o.m_price);
        }

        auto volumeForPricePoint(uint32_t price) {
            auto bucket = m_pbm.findBucket(price);
            if(bucket != nullptr) {
                return bucket->getTotalVolume();
            }
            return 0;
        }

        auto bestPrice() const noexcept {
            if constexpr (BidAskTrait == Side::BUY) {
                return m_pbm.maxPrice();
            } else {
                return m_pbm.minPrice();
            }
        }

        friend class iterator;

        class iterator {
        private:
            typename PriceBucketManager<>::iterator<BidAskTrait> m_base_iter;
        public:
            using iterator_category_tag = std::bidirectional_iterator_tag;
            using value_type = uint64_t; // iterator over the price level
            using difference_type = std::ptrdiff_t;
            using pointer = uint64_t*;
            using reference = uint64_t&;
            iterator(PriceBucketManager<>& arg, bool isEnd = false) : m_base_iter(arg, isEnd) {
            }

            uint64_t operator * () const noexcept {
                return m_base_iter.operator*();
            }

            iterator& operator ++ () noexcept {
                m_base_iter.operator++();
                return *this;
            }

            iterator operator ++ (int) noexcept {
                m_base_iter.operator++(0);
                return *this;
            }

            iterator& operator -- () noexcept {
                m_base_iter.operator--();
                return *this;
            }

            iterator operator -- (int) noexcept {
                m_base_iter.operator--(0);
                return *this;
            }

            bool operator == (const iterator& rhs) const noexcept {
                auto lp = m_base_iter.operator*();
                auto rp = rhs.operator*();
                return lp==rp;
            }
            bool operator != (const iterator& rhs) const noexcept {
                return !this->operator==(rhs);
            }
        };

        auto begin() { return iterator(m_pbm); }
        auto end() { return iterator(m_pbm, true); }
    };
}