#include "Switch.hpp"
#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>
using std::string;

using namespace rg::util;

/* options that do not require an argument can specify a default value or implicit value or both. If
* default value is not given, default value will be TRUE. Similarly, if implicit value is not given, implicit value will be FALSE.
*
* options that do require an argument can only specify an implicit value. If option is not given on command line, then we fallback to implicit value.
*
* options with optional argument can specify a default value or implicit value or both.
* Put a check to make sure, options with optional argument must specify a default value.
* If default value is not given error out. if implicit value is not given, ignore and leave it std::optional<empty>
 */
Switch::Switch(string argName, string argDesc, SwitchArgument optArg, char shortOption, string longOption,
               string defValue, string implicitVal) :
        m_switchname(argName), m_description(argDesc), m_switch_arg(optArg), m_shortswitch(shortOption), m_longswitch(longOption),
        m_default_value(defValue), m_implicit_value(implicitVal) {

    try {
        auto res = validate();
    } catch(const std::exception& e) {
        std::throw_with_nested(std::runtime_error("Error processing program_options!"));
    }

    switch(m_switch_arg) {
        case SwitchArgument::not_required: {
            m_default_value = (m_default_value.empty() ? "1" : "0");
            m_implicit_value = (m_implicit_value.empty() ? "0" : "1");
            break;
        }

        case SwitchArgument::optional: {
            if(m_default_value.empty()) {
                std::ostringstream ostr;
                ostr << "missing default value for switch \"" << m_switchname << "\", which requires an optional argument.\n";
                string err(ostr.str());
                throw std::runtime_error(err);
            }
            break;
        }

        case SwitchArgument::required: {
            if(!m_default_value.empty()) {
                std::ostringstream ostr;
                ostr << "default value for switch \"" << m_switchname << "\", which requires a mandatory argument is not allowed.\n";
                string err(ostr.str());
                throw std::runtime_error(err);
            }
            break;
        }
    }
}

bool Switch::validate() {
    SwitchMap::iterator iter {};
    iter = m_switches.find(m_switchname);
    if(iter != m_switches.end()) {
        std::ostringstream ostr;
        ostr << "Duplicate argument name [" << m_switchname << "] found in program_options";
        throw std::runtime_error(ostr.str());
    }

//    if
    // use a boost::multi_index_map to access Switch using argument name, or short option or long option and also sequenced.

}
