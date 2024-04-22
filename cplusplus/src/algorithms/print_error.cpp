/*
 * write a function that returns an error message
 * string solution(const string& text, int Y, int Z)
 *
 * S is the error text.
 * Y is the index where the error is.
 * Z is an integer denoting the maximum number of characters to print on either side of the error.
 *
 * Example: if text is
 * "// comment\n"
 * "int main() {\n"
 * "    return 0\n"
 * "}\n"
 *
 * Then you have to print the previous line, followed by line containing the error, followed by a line containing only spaces and a caret sign below the error index,
 * followed by the next line. But remember only to print Z chars at max before and after the error index.
 *
 * Output:
 * "int main() {\n"
 * "    return 0\n"
 * "            ^\n"
 * "}\n"
 */

#include <iostream>
#include <string>
using namespace std;

string solution(const string& text, int Y, int Z) {
    // find start and end indices of the error line
    string::size_type errLineStartIdx {0};
    if(auto pos = text.find_last_of('\n', static_cast<string::size_type>(Y-1)); pos != string::npos) {
        errLineStartIdx = pos + 1;
    }
    string::size_type errLineEndIdx {text.size()-1};
    if(auto pos = text.find_first_of('\n', static_cast<string::size_type>(Y)); pos != string::npos) {
        errLineEndIdx = pos;
    }

    // find start and end indices of the previous line
    string::size_type prevLineEndIdx = (errLineStartIdx == 0 ? errLineStartIdx : errLineStartIdx-1);
    string::size_type prevLineStartIdx = prevLineEndIdx;
    if(prevLineStartIdx != 0) {
        if(auto pos = text.find_last_of('\n', prevLineStartIdx-1); pos == string::npos) {
            prevLineStartIdx = 0;
        } else {
            prevLineStartIdx = pos+1;
        }
    }

    // find start and end indices of the next line
    string::size_type nextLineStartIdx = (errLineEndIdx == text.size()-1 ? errLineEndIdx : errLineEndIdx+1);
    string::size_type nextLineEndIdx = nextLineStartIdx;
    if(auto pos = text.find_first_of('\n', nextLineStartIdx); pos != string::npos) {
        nextLineEndIdx = pos;
    } else {
        nextLineEndIdx = text.size()-1;
    }

    auto startIdx = (Y-Z >= 0 ? static_cast<string::size_type>(Y-Z) : prevLineStartIdx);
    auto endIdx = (static_cast<string::size_type>(Y+Z) >= text.size() ? nextLineEndIdx : static_cast<string::size_type>(Y+Z));

    // cout << "ErrLine Start, End: " << errLineStartIdx << "  " << errLineEndIdx << endl;
    // cout << "PrevLine Start, End: " << prevLineStartIdx << "  " << prevLineEndIdx << endl;
    // cout << "NextLine Start, End: " << nextLineStartIdx << "  " << nextLineEndIdx << endl;
    // cout << "Start Idx: " << startIdx << endl;
    // cout << "End Idx: " << endIdx << endl;
    // cout << endl << endl;

    string result(text, startIdx, static_cast<unsigned long>(Y) - startIdx + 1);

    if(endIdx >= errLineEndIdx) {
        result.append(text, static_cast<unsigned long>(Y + 1), errLineEndIdx - static_cast<unsigned long>(Y));
    } else {
        result.append(text, static_cast<unsigned long>(Y + 1), endIdx - static_cast<unsigned long>(Y)).append("\n");
    }

    // append blank line with caret
    if(!result.empty() && result.back() != '\n') result.append("\n");
    if(errLineStartIdx >= startIdx) {
        result.append(static_cast<unsigned long>(Y) - errLineStartIdx, ' ').append("^\n");
    } else {
        result.append(static_cast<unsigned long>(Y) - startIdx, ' ').append("^\n");
    }

    // append line after
    if(endIdx > errLineEndIdx) {
        result.append(text, nextLineStartIdx, endIdx-nextLineStartIdx+1);
    }
    return result;
}

int main() {
    string S1 = "// comment\n"
                "int main() {\n"
                "    return 0\n"
                "}\n";

    string S2 = "123";

    string S3 = "This text is pretty long, but will be\n"
                "concatenated into just a single string.\n"
                "The disadvantage is that you have to quote\n"
                "each part, and newlines must be literal as\n"
                "usual.";

    auto res1 = solution(S1, 36, 126);
    cout << res1 << endl;

    auto res2= solution(S2, 1, 0);
    cout << res2 << endl;

    auto res3 = solution(S3, 121, 43);
    cout << res3 << endl;

    auto res4 = solution(S3, 165, 43);
    cout << res4 << endl;
}
