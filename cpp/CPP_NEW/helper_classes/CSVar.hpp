#pragma once

#include <cstdint>
#include <utility>
#include <type_traits>

namespace util {
    /**
    * \class CSVar
            * Encapsulates a type-safe union.
    *
    * CSVar is a variant which can hold one of the following underlying types
    * -# bool
    * -# 64 bit signed value
    * -# 64 bit unsigned value
    * -# floating point value.
    * -# a string
    */
    class CSVar final {
    public:
        enum class VarType : unsigned int {
            nil_type,
            missing_type,
            bool_type,
            int64_type,
            uint64_type,
            double_type,
            string_type
        };

    private:
        struct Nil {};
        struct Missing {};
        union {
            Nil m_nil;
            Missing m_missing;
            bool m_bool;
            std::int64_t m_int64;
            std::uint64_t m_uint64;
            double m_double;
            char* m_str; // null terminated.
            char m_embedded[sizeof(double)]; // embedded string, if it fits.
        } m_data;

        static constexpr std::size_t CSVAR_EMBEDDED_STRING_SIZE = sizeof(double) - 1;
        VarType m_type;

    public:
        CSVar(); // default ctor

        template <typename T>
        explicit CSVar(T&& val);

        void _init(bool);

        template <typename T, typename std::enable_if_t<std::is_signed_v<std::remove_reference_t<T>>>* = nullptr>
        void _init(T&& val) {
            _init_T(static_cast<int64_t>(std::forward<T>(val)));
        }

        template <typename T, typename std::enable_if_t<std::is_unsigned_v<std::remove_reference_t<T>>>* = nullptr>
        void _init(T&& val) {
            _init_T(static_cast<uint64_t>(std::forward<T>(val)));
        }

        void _init_T(std::int64_t arg);
        void _init_T(std::uint64_t arg);

        unsigned int getType() const noexcept {
            return std::underlying_type_t<VarType>(m_type);
        }
    };

    template <typename T>
    inline CSVar::CSVar(T&& val) {
        _init(std::forward<T>(val));
    }
}