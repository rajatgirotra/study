#include "OptionProcessor.hpp"
#include "Switch.hpp"
#include <cstring>
#include <cassert>
using namespace rg::util;

#include <iostream>
using std::cout;
using std::endl;

namespace {
    bool IsShortOption() noexcept {
        using Op = OptionsProcessor;
        assert(Op::m_opt_scanning_ended == false);
        if ((strlen(Op::m_argv[Op::m_opt_idx]) >= 2) && Op::m_argv[Op::m_opt_idx][0] == '-'
            && Op::m_argv[Op::m_opt_idx][1] != '-') {
            return true;
        }
        return false;
    }

    bool IsLongOption() noexcept {
        using Op = OptionsProcessor;
        assert(Op::m_opt_scanning_ended == false);
        if ((strlen(Op::m_argv[Op::m_opt_idx]) >= 3) && !strncmp(Op::m_argv[Op::m_opt_idx], "--", 2)) {
            return true;
        }
        return false;
    }

    bool OptionScanningEnded() noexcept {
        using Op = OptionsProcessor;
        if ((strlen(Op::m_argv[Op::m_opt_idx]) == 2) && !strncmp(Op::m_argv[Op::m_opt_idx], "--", 2)) {
            Op::m_opt_scanning_ended = true;
            return true;
        }
        return false;
    }

    void ParseShortOption() noexcept {
        using Op = OptionsProcessor;
        assert(Op::m_opt_scanning_ended == false);
        if(strlen(Op::m_argv[Op::m_opt_idx]) > 2) {
            cout << "Processing Short Switch: " << Op::m_argv[Op::m_opt_idx] << endl;
            ++Op::m_opt_idx;
        } else {
            ++Op::m_opt_idx;
            cout << "Processing Short Switch: " << Op::m_argv[Op::m_opt_idx-1] << " " << Op::m_argv[Op::m_opt_idx] << endl;
            ++Op::m_opt_idx;
        }
    }

    void ParseLongOption() noexcept {
        using Op = OptionsProcessor;
        assert(Op::m_opt_scanning_ended == false);
        if(strchr(Op::m_argv[Op::m_opt_idx], '=') != nullptr) {
            cout << "Processing Long Switch: " << Op::m_argv[Op::m_opt_idx] << endl;
            ++Op::m_opt_idx;
        } else {
            ++Op::m_opt_idx;
            cout << "Processing Long Switch: " << Op::m_argv[Op::m_opt_idx-1] << " " << Op::m_argv[Op::m_opt_idx] << endl;
            ++Op::m_opt_idx;
        }
    }
}


void OptionsProcessor::parse(int argc, char **argv) {
    OptionsProcessor::m_argc = argc;
    OptionsProcessor::m_argv = argv;

    while(OptionsProcessor::m_opt_idx < OptionsProcessor::m_argc) {
        if(!OptionScanningEnded()) {
            if(IsShortOption()) {
                ParseShortOption();
            } else if (IsLongOption()) {
                ParseLongOption();
            }
        }
    }
}
