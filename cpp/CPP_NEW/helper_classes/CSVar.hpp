#pragma once

#include <cstdint>

namespace util {
    class CSVar {
    private:
        union {
            bool m_bool,
            std::int32_t m_int32,
            std::int64_t m_int64,
            double m_double,
            const char* m_str;
        } m_data;

        enum class VarType {
            null_type,
            missing_type,
            bool_type,
            int32_type,
            int64_type,
            double_type,
            string_type;
        };

        VarType m_type;
    };
}