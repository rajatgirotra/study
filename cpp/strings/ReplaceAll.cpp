#include <cstddef>
#include "ReplaceAll.h"
using namespace std;
 
string& replaceAll(string& context, const string& from,
  const string& to) {
  size_t lookHere = 0;
  size_t foundHere;
  while((foundHere = context.find(from, lookHere))
    != string::npos) {
    context.replace(foundHere, from.size(), to);
    lookHere = foundHere + to.size();
  }
  return context;
} ///:~

