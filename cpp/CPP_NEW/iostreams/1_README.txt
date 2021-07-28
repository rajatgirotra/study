IOStream class hierarchy
------------------------
We have two sets of class hierarchies in IOStreams library. the stream classes and the stream buffer classes.

stream class hierarchy
=====================

ios_base: ios_base is the top level base class which contains data members, functions, enums, nested classes etc that are common to all stream classes. example:
- fmtflags enum
- functions setf(), unsetf()
- iostate enum (goodbit, eofbit, failbit, badbit)
- stream storage functions xalloc/iword/pword
- seekdir enum (beg, cur, end)
- openmode enum (in, out, trunc, ate, end, binary)
- width(), precision() etc
- class failure (exception class object thrown by stream operations).

basic_ios<charT, char_traits<charT>>: this is stream class which contains data member, functions etc that are common to all stream classes but are dependant on the character type.
- stream state functions like rdstate(), setstate(), clear(), good(), eof(), fail(), operator !(), operator void*() etc
- functions for setting and clearing stream exceptions
- some format functions like fill() which are dependant on the character type.
- functions like copyfmt(), tie() for copying stream data members and for tying an input or output stream to an output stream.
- a reference or pointer to the stream buffer base class: basic_streambuf<charT, char_traits<T>>.

the reason why the stream state functions and functions for setting and clearing exceptions are not in ios_base (even though they dont depend on character type) is that ios_base reference is also passed to the locale class. this would allow locale classes to raise set and test stream state and throw exceptions which isn't really a good design. Also basic_ios just stores the stream buffer reference, it does not use it at all.

basic_istream<charT, char_traits<charT>>: 
basic_ostream<charT, char_traits<charT>>: 
basic_iostream<charT, char_traits<charT>>: 
These derive from basic_ios. These are general stream classes that implement all the functions related to formatting and parsing. You will find implementation of all the overloaded formatting and parsing for various data types like bool, signed/unsigned char, signed/unsigned uint8_t/uint16_t/uint32_t, float/double etc. All the concrete stream classes use the formatting logic from these classes. 
These classes use the stream buf reference/pointer in the basic_ios class to call all the formatting/parsing functions.

basic_ifstream<charT, char_traits<charT>>
basic_ofstream<charT, char_traits<charT>>
basic_fstream<charT, char_traits<charT>>
basic_istringstream<charT, char_traits<charT>>
basic_ostringstream<charT, char_traits<charT>>
basic_stringstream<charT, char_traits<charT>>
These are the concrete classes which must hold a data member to the underlying stream buffer class. These classes must only implement functions and data member which are specifc to the external device. like open() and close() for file streams and str() for stringstreams (memory I/O).

Stream buffer classes
====================
very trivial

basic_streambuf<charT, char_traits<charT>>;
basic_filebuf<charT, char_traits<charT>> : basic_streambuf<charT, char_traits<charT>> {}
basic_stringbuf<charT, char_traits<charT>> : basic_streambuf<charT, char_traits<charT>> {}
These are the classes responsible for buffering, code-conversion and transport to the physical device. stream classes on the otherhand rely mostly on formatting and parsing. 

Stream and Stream Buffer Initialization
========================================
As you already know that basic_ios<> contains stream buffer pointer. but it doesnt use it at all. the stream buffer pointer can be initialized in 3 ways:

basic_ios(basic_streambuf<charT, Traits>* ptr); // using ctor

basic_ios(); // default ctor followed by call to protected member function init()
void init(basic_streambuf<charT, Traits>* ptr);

basic_streambuf<charT, Traits>* rdbuf(basic_streambuf<charT, Traits>* ptr); using rdbuf() setter function. return value is old stream buffer pointer.
basic_streambuf<charT, Traits>* rdbuf() const; // just a getter.

the basic_istream/basic_ostream/basic_iostream classes have a ctor which take a stream buffer pointer and call the base class ctor or the base class init() function to initialize the stream buffer pointer in basic_ios<> class.

the concrete classes like basic_ifstream<> and basic_istringstream hold a member object of basic_filebuf<> or basic_stringbuf<> respectively. Their ctors pass a pointer to this buffer to the basic_istream<> and to basic_ios<> to initialize the stream buffer.

The concrete classes also provide a rdbuf() function which has a slightly different return type. As a result the rdbuf() functions in basic_ios<> (both the 2 overloads in basic_ios<>) get hidden.

basic_filebuf<charT, Traits>* rdbuf() const; // return the concrete stream buffer class pointer
basic_stringbuf<charT, Traits>* rdbuf() const; // return the concrete stream buffer class pointer

This hiding of base class rdbuf() has interesting side effect. Remember that the general stream classes basic_istream/basic_ostream/basic_iostream work with the stream buffer pointer which is in the basic_ios<> class. So when someone calls rdbuf() setter function, the stream buffer pointer in basic_ios<> and in concrete stream classes like basic_ifstream/basic_stringstream differ. Concrete base classes will always refer to the stream buffer object which they hold (via their own rdbuf() function).
So when you call open() or close() or str() functions, they all refer to basic_filebuf<> or basic_streambuf<>
Example:

basic_filebuf<char> buf;
buf.open("in.txt");

basic_ifstream<char> ifstr;
ifstr.basic_ios<char>::rdbuf(&buf); //because rdbuf() setter is hidden, we have to use this syntax to be explicit.

Locales
======
locales are objects that handle the culture-dependant aspects of formatting and parsing. a locale object is composed of one or more facets. each facet handles a particular aspect of the cultural differences. like numeric facets handle how numeric values should be formatted and parsed, ctype (character type) factes handle things like which is the space character in that locale. codecvt facets handle code conversion between internal and external character encodings etc.

In IOStreams, we have two locale objects. One locale object is data member of of ios_base class. and another is data member of stream buffer class basic_streambuf<>. The locale object in stream class is used to handle numeric factes and character type facets. the locale object in stream buffer class is used to handle code conversion as stream buffer classes interact with the external devices.

Both ios_base and basic_streambuf<> provide functioins that take a locale object as argument to set their locale objects. By default when a stream object is created, both locale objects are same and initialized to the global c++ locale which is set for the system. However these can be different locale objects.

1) ios_base::imbue(locale("en_US.utf8"));
2) basic_streambuf<>::pubimbue(locale("en_US.utf8"));

If you want to set both the locales consistenly to the same locale object, basic_ios<> also provides an imbue() method which sets both the locales in a single call.
Also the ios_base and basic_streambuf<> provide a function getloc() which return the std::locale object.

stream classes also provide a way to register callback functions when certain events happen. One such event is an imbue_event. You can register interest in this event via the register_callback() function. Lets see how the locale and facet objects are used by the insertors and extractor operators for an intergral value.

inserter
--------
basic_istream<charT, Traits>& operator >> (int& n)
{
    ios_base::iostate err = 0;
    use_facet<num_get<charT, istreambuf_iterator<charT, Traits>>(this.getloc()).get(*this, istreambuf_iterator<charT, Traits>(), *this, err, n);
    return *this;
}

extractor
--------
basic_ostream<charT, Traits>& operator << (int n)
{
  use_facet<num_put<charT, ostream_iterator<charT, Traits>>(this.getloc()).put(*this, *this, basic_ios<charT, Traits>::fill(), n);
  return *this;
}

let's look at the num_get<>::get() and num_put<>::put() function declarations.

iter_type put(iter_type out, ios_base& fmt, char_type fill_character, long value) const;
iter_type get(iter_type start, iter_type end, ios_base& fmt, iostate& err, long& val) const;

the put() function expects an iterator pointing to the output sequence where the characters should be written. this will be a ostreambuf_iterator<> pointing to a location in the stream buffer class.
We pass *this to it (i.e. a stream object) because the streambuf_iterators<> has a converting ctor that takes a stream object.

ostreambuf_iterator( ostream_type& stream ) noexcept;
istreambuf_iterator( istream_type& stream ) noexcept;

the fmt parameter is for accessing the fmtflags required in formatting. the fill character is also obvious and the value is the integer value to be printed out. If any error in put(), it is reported through the return iter_type.

similarly for get() function, we need two iterators, the begin and end of the sequence. if any error, it is set in the err parameter.

Continue on page 82 of chapter 2 of standard C++ iostreams and locales
