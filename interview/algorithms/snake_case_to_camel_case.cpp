#include <algorithm> 
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    std::string variable_name;
    getline(cin, variable_name);
    std::string camelCase{};
    bool upper {false};
    for(auto idx = 0; idx < variable_name.size(); ++idx) {
        if(variable_name[idx] == '_') {
            upper = true;
            continue;
        }

	char ch = (upper ? static_cast<char>(toupper(variable_name[idx])) : variable_name[idx]);
	camelCase.append(string(1, ch));
        upper = false;
    }
    cout << camelCase << endl;
}
