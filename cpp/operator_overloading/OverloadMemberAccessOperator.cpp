#include <iostream>
#include <string>

using namespace std;

class HelloWorldProxy {

private:
	class HelloWorldImpl {
		private:
			string str;

		public:
			HelloWorldImpl(const string& strArg) : str(strArg) {
			}

			string toString() const {
				return str;
			}
	};

	HelloWorldImpl* poImpl;

public:
	HelloWorldImpl* operator-> () {
		return poImpl;
	}

	HelloWorldProxy() : poImpl(new HelloWorldImpl("Hello World")) {
	}

	~HelloWorldProxy() {
		if(poImpl) {
			delete poImpl;
		}
	}

};

int main() {
	HelloWorldProxy proxy;
	cout << proxy->toString() << endl;
}
