We'll study the jsoncpp details on GitHub.
Very simple interface.

#include <json/json.h> to get everything.

You can read a json from
1) a document
2) a string
3) an input stream.

/*
  default reader will all features enabled. This should be OK. You can otherwise specify your own features to use; but its hardly ever necessary.
  create an object of Json::Reader
*/
Json::Reader reader;

reader.parse(string document, Json::Value& root, bool allowComments=true); // to read a file
reader.parse(const char* beginDoc, const char* endDoc, Json::Value& root, bool allowComments=true); // to read a string
reader.parse(std::istream& is, Json::Value& root, bool allowComments=true); // to read from an input stream. A file stream or stringstream

The return value is the second parameter. Json::Value which is THE OBJECT IN JSON for accessing/manipulating data. By default it refers to the root of the document.
The Json::Value object is an opaque object used to represent

1) an integer, a string, a double, a bool, a json list or json object
functions to get coersce Json::Value to other types

Json::Value val;
val.asInt()
val.asUInt()
val.asBool()
val.asDouble()
val.asString()
val.asCString()
val.asDouble()

Then there are methods to test what a Json::Value is:

val.isInt()
val.isUInt()
val.isBool()
val.isDouble()
val.isNumeric()
val.isBool()
val.isArray()
val.isObject()
val.isString()
val.isIntegral()
val.isNull()
!val // same as isNull

Some more helpers when Value is of type Array/Object/Null
bool isEmpty(); // returns true if Value is of type Array, Object or Null and its size is 0.
UInt size(); // only valid for Array or Object. Returns the no. of items in the array or number of members in the Object
void clear(); // remove all items from array or members from the object
void resize(UInt new_size); // Only valid for Array or Null type. New elements are initialized with null.

//C'tors, again trivial
Value() ; default is with Null value
Value(Int);
Value(UInt);
Value(bool);
Value(double);
Value(string);
Value(char*);


//Getting/setting a key-value pair.
Value& operator[](const char* key);
Value& operator[](const string& key); // Will insert Value() (ie a null Json::Value if key does not exist)
const Value& operator[](const char* key) const;
const Value& operator[](const string& key) const;

Value get(const char* key, const Value& defaultValue); //same as above but return default value instead of Json::Value()
Value get(const char* key, const Value& defaultValue);


//Getter/setter for Array
Value& operator[](UInt index); // return value at index. otherwise extend array to have index+1 elements of type Json::Value() and then return the value at that index
const Value& operator[](UInt index) const;
Value get( UInt index,  const Value &defaultValue ) const; // Return defaultValue if index > size() of array
bool isValidIndex(UInt index);

//Removing key value pair from an object
Value removeMember(const char* key); // return the value removed or null
Value removeMember(const std::string& key);
bool isMember(const char* key);
bool isMember(const string& key);
Members getMemberNames() const; //get all member names, Members is nothing but an std::vector<string>

//Iterators
const_iterator begin() const;
const_iterator end() const;
iterator begin();
iterator end();
