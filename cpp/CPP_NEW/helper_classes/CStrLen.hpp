#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <type_traits>

namespace util {

#define STRLEN(s)  ( ( (sizeof ( s ) ) / ( sizeof ( char ) ) ) - 1)
#define CSL(s)   (s), (static_cast<int>(STRLEN(s)))
#define CSLO(s)  CStrLen(CSL(s))
    class CStrLen
    {
    private:
        const char* m_s {nullptr};
        std::size_t m_len {0};

    public:

        // for string literals and character pointers.
        CStrLen(const char*, int = -1) noexcept;

        // for std::string
        template <typename T, typename std::enable_if_t<std::is_same_v<const char*, decltype(std::declval<const T>().data())>>* = nullptr>
        explicit CStrLen(const T& arg) noexcept : m_s(arg.c_str()), m_len(arg.size()) {
        }

        // for arrays
        template <std::size_t N>
        explicit CStrLen(const char (&arr)[N]) : m_s(arr), m_len(N-1) {
        }

        explicit operator const char* () const noexcept { return m_s; }
        explicit operator bool() const noexcept { return m_s != nullptr; }

        friend std::ostream& operator << (std::ostream& os, const CStrLen& rhs) noexcept;

    };
}