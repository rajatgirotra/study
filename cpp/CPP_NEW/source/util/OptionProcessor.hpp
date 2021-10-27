#include <unordered_map>
#include <string_view>
#include <string>
using std::string;

namespace rg {
    namespace util {
        struct OptionsProcessor {
            static void parse(int argc, char** argv);
        public:
            static int m_opt_idx;
            static int m_argc;
            static char** m_argv;
            static bool m_opt_scanning_ended;
            using OptionsMap = std::unordered_map<std::string_view, std::string>;
            OptionsMap m_map;
        };

        inline int OptionsProcessor::m_opt_idx {1};
        inline int OptionsProcessor::m_argc {};
        inline char** OptionsProcessor::m_argv {nullptr};
        inline bool OptionsProcessor::m_opt_scanning_ended {false};
    }
}

