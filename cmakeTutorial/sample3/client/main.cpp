#include "roof.h"
#include "roof_p.h"
#include <iostream>
using namespace std;

int main() {
	A a;
	cout << "A::m_A: " << a.getA() << endl;
	cout << "A::m_A squared: " << foo(a.getA()) << endl;
	a.setA(100);
	cout << "A::m_A after change: " << a.getA() << endl;

	return 0;
}

