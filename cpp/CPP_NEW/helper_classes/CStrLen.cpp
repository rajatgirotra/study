#include "CStrLen.hpp"
#include <cstring>

namespace util {
    CStrLen::CStrLen(const char* s_arg, int len_arg) noexcept {
        // find length of string
        std::size_t len = (len_arg < 0 ? strlen(s_arg) : static_cast<std::size_t>(len_arg));
        this->m_s = s_arg;
        this->m_len = len;
    }

    std::ostream& operator << (std::ostream& os, const CStrLen& rhs) noexcept {
        if(rhs) {
            os.write(rhs.m_s, static_cast<std::streamsize>(rhs.m_len));
        } else {
            os << "[null]";
        }
        return os;
    }
}

