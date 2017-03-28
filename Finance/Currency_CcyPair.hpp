#pragma once

#include <iostream>
#include <string>
#include <stdint.h>
#include <stdexcept>

namespace puma { namespace common { namespace md
{
// TODO: Replace with
// enum class Side { Bid=0, Ask=1 };
// once we switch to C++11
struct Side
{
	enum SideEnum { Bid=0, Ask=1 };
	Side() : value(Bid) {}
	Side(SideEnum v) : value(v) {}
	operator SideEnum() const { return value; }
	SideEnum value;
};

inline size_t side_index(Side side) { return static_cast<Side::SideEnum>(side); }

class Currency
{
public:
	Currency() : ccy_(0) {}
	explicit Currency(uint32_t code) : ccy_(code) {}
	explicit Currency(const std::string& ccy) { set_from_str(ccy.c_str()); }
	explicit Currency(const char* ccy) { set_from_str(ccy); }
	bool is_set() const { return ccy_ != 0; }
	friend bool operator < (Currency lhs, Currency rhs) { return lhs.ccy_ < rhs.ccy_; }
	friend bool operator == (Currency lhs, Currency rhs) { return lhs.ccy_ == rhs.ccy_; }
	friend bool operator != (Currency lhs, Currency rhs) { return lhs.ccy_ != rhs.ccy_; }
	const char* c_str() const
	{
		return static_cast<const char*>(static_cast<const void*>(&ccy_));
	}
	uint32_t code() const { return ccy_; }
	friend std::ostream& operator << (std::ostream& os, Currency c) { os << c.c_str(); return os; }
private:
	void set_from_str(const char* ccy)
	{
		if (ccy[0] == 0 || ccy[1] == 0 || ccy[2] == 0 || ccy[3] != 0)
			throw std::runtime_error("Invalid currency string " + std::string(ccy));
		ccy_ =
			(static_cast<uint32_t>(ccy[0]) << 0)
			| (static_cast<uint32_t>(ccy[1]) << 8)
			| (static_cast<uint32_t>(ccy[2]) << 16)
			;
	}
	uint32_t ccy_;
};

class CurrencyPair
{
public:
	CurrencyPair() : ccy_pair_(0) {}
	explicit CurrencyPair(const std::string& ccy_pair) { set_from_str(ccy_pair.c_str()); }
	explicit CurrencyPair(const char* ccy_pair) { set_from_str(ccy_pair); }
	CurrencyPair(Currency lhs, Currency rhs)
	{
		ccy_pair_ =
			(static_cast<uint64_t>(lhs.code()) << (8*0))
			| (static_cast<uint64_t>(rhs.code()) << (8*3))
			;
	}
	bool is_set() const { return ccy_pair_ != 0; }
	friend bool operator < (CurrencyPair lhs, CurrencyPair rhs) { return lhs.ccy_pair_ < rhs.ccy_pair_; }
	friend bool operator == (CurrencyPair lhs, CurrencyPair rhs) { return lhs.ccy_pair_ == rhs.ccy_pair_; }
	friend bool operator != (CurrencyPair lhs, CurrencyPair rhs) { return lhs.ccy_pair_ != rhs.ccy_pair_; }
	const char* c_str() const
	{
		return static_cast<const char*>(static_cast<const void*>(&ccy_pair_));
	}
	Currency lhs() const { return Currency((ccy_pair_ >> (8*0)) & 0xFFFFFF); }
	Currency rhs() const { return Currency(0xFFFFFF & (ccy_pair_ >> (8*3))); }
	friend std::ostream& operator << (std::ostream& os, CurrencyPair c) { os << c.c_str(); return os; }

	friend bool operator == (const std::string& lhs, CurrencyPair rhs)
	{
		return lhs.size() == 6
			&& lhs[0] == rhs.c_str()[0]
			&& lhs[1] == rhs.c_str()[1]
			&& lhs[2] == rhs.c_str()[2]
			&& lhs[3] == rhs.c_str()[3]
			&& lhs[4] == rhs.c_str()[4]
			&& lhs[5] == rhs.c_str()[5];
	}
	friend bool operator != (const std::string& lhs, CurrencyPair rhs) { return !(lhs==rhs); }
	friend bool operator == (CurrencyPair rhs, const std::string& lhs) { return rhs==lhs; }
	friend bool operator != (CurrencyPair rhs, const std::string& lhs) { return !(rhs==lhs); }
private:
	void set_from_str(const char* ccy_pair)
	{
		if (ccy_pair[0] == 0 || ccy_pair[1] == 0 || ccy_pair[2] == 0 || ccy_pair[3] == 0 || ccy_pair[4] == 0 || ccy_pair[5] == 0 || ccy_pair[6] != 0)
			throw std::runtime_error("Invalid currency string " + std::string(ccy_pair));
		ccy_pair_ =
			(static_cast<uint64_t>(ccy_pair[0]) << (8*0))
			| (static_cast<uint64_t>(ccy_pair[1]) << (8*1))
			| (static_cast<uint64_t>(ccy_pair[2]) << (8*2))
			| (static_cast<uint64_t>(ccy_pair[3]) << (8*3))
			| (static_cast<uint64_t>(ccy_pair[4]) << (8*4))
			| (static_cast<uint64_t>(ccy_pair[5]) << (8*5))
			;
	}
	uint64_t ccy_pair_;
};

} } } // namespace puma::common::md
} } } // namespace puma::common::md