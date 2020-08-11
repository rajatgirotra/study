#include "CSVar.hpp"

namespace util {
    CSVar::CSVar() : m_type(CSVar::VarType::nil_type) {}

    void CSVar::_init(bool arg) {
        m_data.m_bool = arg;
        m_type = CSVar::VarType::bool_type;
    }

    void CSVar::_init_T(std::int64_t arg) {
        m_data.m_int64 = arg;
        m_type = CSVar::VarType::int64_type;
    }

    void CSVar::_init_T(std::uint64_t arg) {
        m_data.m_uint64 = arg;
        m_type = CSVar::VarType::uint64_type;
    }
}