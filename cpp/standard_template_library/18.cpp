/*
a collection of key/value pairs with
unique keys could also be thought of as an associative array. Consider the following example:
*/

// stl/map1.cpp
#include <iostream>
#include <map>
#include <string>
using namespace std;
int main()
{
/* type of the container:
* - map: elements key/value pairs
* - string: keys have type string
* - float: values have type float
*/
typedef map<string,float> StringFloatMap;
StringFloatMap coll;
//insert some elements into the collection
coll["VAT"] = 0.15;
coll["Pi"] = 3.1415;
coll["an arbitrary number"] = 4983.223;
coll["Null"] = 0;
/*print all elements
* - iterate over all elements
* - element member first is the key
* - element member second is the value
*/
StringFloatMap::iterator pos;
for (pos = coll.begin(); pos != coll.end(); ++pos) {
cout << "key: \"" << pos->first << "\" "
<< "value: " << pos->second << endl;
}

cout<<coll["MY NAME IS RAJAT"]; // the value will be 0.
}

/*
The declaration of the container type must specify both the type of the key and the type of the
value:
typedef map<string,float> StringFloatMap;
Maps enable you to insert elements by using the subscript operator [ ]:
coll["VAT"] = 0.15;
coll["Pi"] = 3.1415;
coll["an arbitrary number"] = 4983.223;
coll["Null"] = 0;
Here, the index is used as the key and may have any type. This is the interface of an associative
array. An associative array is an array in which the index may be of an arbitrary type.


Note that the subscript operator behaves differently than the usual subscript operator for arrays:
Not having an element for an index is not an error. A new index (or key) is taken as a reason to
create and to insert a new element of the map that has the index as the key. Thus, you can't have
a wrong index. Therefore, in this example in the statement

coll["Null"] = 0;
the expression
coll["Null"]

creates a new element that has the key "Null". The assignment operator assigns 0 (which gets
converted into float) as the value.

You can't use the subscript operator for multimaps. Multimaps allow multiple elements that have
the same key, so the subscript operator makes no sense because it can handle only one value.
As shown on page 90, you must create key/value pairs to insert elements into a multimap.

*/
