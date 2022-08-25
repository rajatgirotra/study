#pragma once

#include "PriceBucket.hpp"
#include <memory>
#include <map>

namespace raj {
    // need to manage multiple PriceBuckets.
    class PriceBucketSet {
    public:
        using price_bucket_type = std::shared_ptr<PriceBucket>;
    private:
        using bucket_set_type = std::map<int64_t, price_bucket_type>;
        bucket_set_type m_buckets;

    public:
        price_bucket_type insert(const bucket_set_type::value_type& arg) noexcept {
            auto [it, added] = m_buckets.emplace(arg);
            return it->second;
        }

        void remove(uint64_t price) noexcept {
            m_buckets.erase(price);
        }

        price_bucket_type find(uint64_t price) const noexcept {
            if(auto it = m_buckets.find(price); it != m_buckets.end()) {
                return it->second;
            }
            return nullptr;
        }

        price_bucket_type successor(uint64_t price) const noexcept {
            if(auto it = m_buckets.upper_bound(price); it != m_buckets.end()) {
                return it->second;
            }
            return nullptr;
        }

        price_bucket_type predecessor(uint64_t price) const noexcept {
            if(auto it = m_buckets.lower_bound(price); it != m_buckets.end()) {
                if(price <= it->second->pricePoint()) {
                    if(it == m_buckets.begin()) {
                        return nullptr;
                    }
                    --it;
                }
                return it->second;
            }
            return nullptr;
        }

        uint64_t minPrice() const noexcept { return (m_buckets.empty() ? 0 : m_buckets.begin()->first); }
        uint64_t maxPrice() const noexcept { return (m_buckets.empty() ? 0 : m_buckets.rbegin()->first); }
    };
}