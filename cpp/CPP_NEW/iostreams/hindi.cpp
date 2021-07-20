#include <iostream>
using namespace std;

int main() {
	cout.imbue(std::locale("de_AT.utf8"));
	cout << 19.99 << '\t' << fixed << 10000000 << endl;
}
