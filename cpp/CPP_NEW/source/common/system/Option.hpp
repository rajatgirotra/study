#pragma once

/*
 * option that starts with - or -- and IS NOT EXACTLY - or -- is an option element.
 * The characters of such an element are option characters.
 *
 * optind -> index in argv of the next element to be parsed. default is 1 so argv[0] is program name is skipped.
 *
 * single argument options can be specified as -xarg or -x arg. in both cases, code should first see if -x takes a mandatory
 * or optional argument. if yes, we store a pointer to the next character in optarg, otherwise optarg should be nullptr.
 * so optarg should point to arg.
 *
 * options and non-options can be mixed. all non options should be treated like they belong to an option character with character code '1'. can be any non-printable
 * option character so users cannot used it. this way all non-options can be put together.
 *
 * -- means end of option-scanning mode.
 *
 * provide API to throw error or return std::error_code if exception is not required.
 *
 * error while processing options
 * 1) If you receive an option not specified in the optstring,
 *    a) Check if ignore_unknown_args is TRUE or FALSE. Default should be FALSE.
 *    a) Log an INFO msg in log file and on console if ignore_unknown_args is TRUE, Log an Error msg in log file and console if ignore_unknown_args is FALSE.
 *    b) depending on whether you want to throw or return std::error_code, and the value of ignore_unknown_args, do that. *
 *
 * Only allow long options to be prefixed with --, not with -
 * Long options can be specified as --arg=param or --arg param
 *
 * option can have no_argument, required_argument, optional_argument. Create such an enum.
 *
 * long option should be optional.
 *
 * arguments should have an argument_name using which they can be accessed.
 * arguments should have a default and implicit value.
 * ------------------------------------------------------------------------------------------------------------------------------------
 *
 * options that do not require an argument can specify a default value or implicit value or both. If
 * default value is not given, default value will be TRUE. Similarly, if implicit value is not given, implicit value will be FALSE.
 *
 * options that do require an argument can only specify an implicit value. If option is not given on command line, then we fallback to implicit value.
 *
 * options with optional argument can specify a default value or implicit value or both.
 * Put a check to make sure, options with optional argument must specify a default value.
 * If default value is not given error out. if implicit value is not given, ignore and leave it std::optional<empty>
 *
 * IsShortOption(argv[i])
 * 1) if strlen(argv[i]) >= 2 and argv[i][0] == '-' and argv[i][1] != '-', it is option, otherwise false
 *
 * IsLongOption(argv[i])
 * 2) if strlen(argv[i]) >= 3 and argv[i][0] == '-' and argv[i][1] == '-', it is option, otherwise false
 *
 * ParseShortOption(argv) // maintain a global optind pointing to index of argv under process
 * ParseLongOption(argv) // maintain a global optind pointing to index of argv under process
 * should parse the argument, increment optind to the next argv index and return
 * (argument_name, value).
 * If option does not require an argument, fallback to default value as string. Mark option as processed.
 * If option requires an option, should return that argument as string. Mark option as processed.
 * If option requires an optional argument, should return that argument as string, otherwise should return the argument default argument. Mark option as processed.
 *
 * EndOfOptionScanningMode()
 * if argv[optind].size() == 2 and arv[optind] == "--"
 *
 * If EndOfOptionScanningMode() is true,
 * visit all available options, and those not marked as processed. For those fill in the implicit values.
 *
 * For now, if both short and long option is give, the later option will override the first.
 * But slowly we will add a "dest" attribute to Option, which can be "sum", "accumulate", etc.
 * So
 * -x 123 -x 123 -dest sum will store args["x"] = 246
 *
 * -x 123 -x 89 -x -98 -dest accumulate will store args["x"] = [123, 89, -98]
 *
 * NOT IsShortOption() and NOT IsLongOption() and NOT EndoFScanningMode(), add the argument to
 * a short option -'1' --> so all positional arguments go here in the same order as given on the command line.
 */

#include <unordered_map>
#include <string_view>
#include <string>

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
