//: C03:StringStorage.h
#ifndef STRINGSTORAGE_H
#define STRINGSTORAGE_H
#include <iostream>
#include <string>
#include "../TestSuite/Test.h"
using std::cout;
using std::endl;
using std::string;
 
class StringStorageTest : public TestSuite::Test {
public:
  void run() {
    string s1("12345");
    // This may copy the first to the second or
    // use reference counting to simulate a copy:
    string s2 = s1;
    test_(s1 == s2);
    // Either way, this statement must ONLY modify s1:
    s1[0] = '6';
    cout << "s1 = " << s1 << endl;  // 62345
    cout << "s2 = " << s2 << endl;  // 12345
    test_(s1 != s2);
  }
};
#endif // STRINGSTORAGE_H ///:~

