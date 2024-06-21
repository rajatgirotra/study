#pragma once

class ABC {
  public:
    void print() const;
    ABC() { }
};

const ABC conABC; // const in c++ has internal linkage, so you can include this header in multiple translation units.

const char* const msg = "How are you?"; // const in c++ has internal linkage, so you can include this header in multiple translation units.

