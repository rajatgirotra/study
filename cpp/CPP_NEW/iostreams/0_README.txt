IOStreams library
=================

IOStream library is used for input and output of data from your program to an external device. the external device could be a file on the filesystem, a network socket, a communication channel such as message queue or a pipe, a screen window etc. This transfer of data can be categorized in two ways:

1) stream I/O --> unstructured transfer of a sequence of bytes, or characters or some other unit of small size between your program and the external device.
that's why it's called stream I/O as it is just a continuous sequence of data bytes/characters.

2) Record or Block I/O --> structured transfer of bytes as a block or a record. i.e. larger chunks of data (records/block/messages) are transported.

IOStreams library facilitate stream I/O. This does not mean that the external device cannot have a structure. It can, just that the details of the external device are hidden behind the IOStreams interface. The IOStream API itself allows for stream input and output of text. So IOStreams are streams of characters as opposed to stream of bits and bytes.  IOStreams was designed for Input and Output of text IO.

The internal representation of data is in a format which is easier for the program to process. Example, ints are stored as binary values, doubles are stored in IEEE 754 format, strings are stored as contiguous characters in memory etc.

Another categorization is based on the external representation supported by the device. example:
1) If the external device is a screen window, the internal representation needs to be converted to human readable characters. Example:
0x0000009e --> needs to be represented as 158 on the screen. So the external representation is that of human readable set of chars.

2) If external device is a socket connection, external representation can be binary format.

3) If external device is filesystem and compression is also needed, again external representation is binary format.

IOStream support textIO by default. Binary IO is not directly supported.

The stages of IOStreams TEXT I/O
-------------------------------
1) formatting/parsing --> deals with formatting from internal representation to external representation.
2) Buffering --> mostly done for performance. can be disabled. you need to call the stream's flush() function to empty the buffer.
3) Code Conversion
4) Transport.

Code conversion
--------------
Is only required when the character representation resulting from formatting is different from the external character representation of the external device or when the external representation differs from the representation that can be parsed by IOStreams. Example, let say you have a multibyte character file. i.e some characters are one byte, some 2 bytes, some 4 bytes, etc. This kind of representation cannot be parsed by IOStreams. So it will convert all characters to wide characters i.e. wchar_t which IOStream understands.  Similarly for output.

You can think of IOStream as a layered architecture with two layers
1) Formatting Layer --> responsible for formatting/buffering
2) Transport Layer --> Does buffering, code conversion and actual transport

The IOStreams library is an open and extensible framework. which means both the layers can be customized and extended. Formatting layer can be extended by adding new formatting/parsing options, new manipulators etc.

The transport layer can be extended by adding more external devices.

Also IOStream is not only an abstract framework providing abstract classes. It provides concrete implementation classes like
1) filestreams and string streams
2) narrow and wide character streams

filestreams are used for input and output from external devices which exhibit file like behavior. i.e. provide open()/close() type functions (files, sockets, pipes etc)
stringstreams are used for input and output from memory.

narror and wide character streams differ in the type of character sequence passed between the formatting and transport layers.

Also IOStreams can be extended by adding new stream classes for supporting new external devices. This is achieved by means of inheritance. Similarly, you can add support for new type of characters apart from narrow and wide character streams (like Jchar for Japanese characters). This is achieved by means of templates.
the IOStreams class hierarchy is

1) ios_base --> non template class that contains functionality common to all stream class irrespective of the type of characters handled.
2) basic_ios<charT> --> template class containing functionality common to the type of character sequence handled.
3) we have three classes derived from basic_ios. these are basic_istream<charT>, basic_ostream<charT>, and basic_iostream<charT>
4) each of these three classes contain two concrete implementations. one for file streams and one for string streams.
   basic_ifstream<charT>, basic_istringstream<charT> inherit from basic_istream<charT>
   basic_ofstream<charT>, basic_ostringstream<charT> inherit from basic_ostream<charT>
   basic_fstream<charT>, basic_stringstream<charT> inherit from basic_iostream<charT>

the following using directives are provided and also 8 stream objects.
using ifstream = basic_ifstream<char>;
using ofstream = basic_ofstream<char>;
using fstream = basic_fstream<char>;

using wifstream = basic_ifstream<wchar_t>;
using wofstream = basic_ofstream<wchar_t>;
using wfstream = basic_fstream<wchar_t>;

8 objects
--------
cout, wcout (corresponding C stream is stdout)
cin, wcin (corresponding C stream is stdin)
cerr, wcerr (corresponding C stream is stderr)
clog, wclog (corresponding C stream is stderr)

cerr and clog is same except that clog is buffered and cerr is not buffered by default.

Also cin and cout are tied i.e. they are synchronized. If you read anything from cin, then first cout is flushed().

The reason to choose shift operators for streams (<< and >>) is because it has lower precedence than other operators so it is easy to write code like cout << a+b*c, and the expression a+b*c is evaluated first, otherwise we would need to parenthesize everything.

Format Parameters
-----------------
the formatting functions are part of either ios_base class or basic_ios class. The formatting functions are:
streamsize width() const; --> return the stream width setting
void width(streamsize value); --> set stream width. This is the minimum width for the field. any extra space will be padded using the fill character.

basic_ios<charT>::char_type fill() const; --> get the fill character
void fill(basic_ios<charT>::char_type fillCharacter);

streamsize precision() const; --> return the decimal pts to print for floating point values
void precision(streamsize value); --> set stream precision. 

Then there is a formatting function called setf() and unsetf() and flags() to set, unset, and fetch the various formatting options defined in ios_base::fmtflags (which is a bitfield).
example:

ios_base::fmtflags original_flags = cout.flags();
cout.setf(ios_base::fmtflags::left, ios_base::fmtflags::adjustfield); // adjustfield is a bit group.
cout.unsetf(ios_base::fmtflags::adjustfield);
cout.setf(ios_base::fmtflags::uppercase | ios_base::fmtflags::scientific);

Strange behavior of Field Width
-------------------------------
stream width() can be specified for both Input and Output streams. for Output streams, the width() will reset automatically to 0 as soon as it is used. i.e.
cout.width(10);
cout << "812" << "|" << "813"; // will give "       812|813"  (because default adjustment is right). The pipe character and 813 will see width setting as 0.

for Input streams also, only the input of strings will use the width() setting and reset it after use. inputting double, integer, bool etc dont use field width setting. i.e.
int i; string s;
cin.width(10);
cin >> i >> s; // input is 12345 abcdefghijklmnopqrstuvwxyz, so i = 12345, s = "abcdefghij"

Manipulators
-----------
You can also use manipulators instead of formatting function as they can be used in the cout/cin expression itself so it appears more natural. example:
cout.setf(ios_base::fmtflags::left, ios_base::fmtflags::adjustfield);
cout << 813;
AND
cout << left << 813; // seems so compact

Also cout << setw(10); is same as cout.width(10);

Some manipulators effect input streams, some output streams and some both. Generally the manipulators do not have any effect if the stream state is bad. but there are a few exceptions to that rule.
You can also write your own manipulators. See the gcc implementation of endl, skipws, boolalpha, width, precision to see how you can write your own manipulators.

Stream Locale
-------------
now there are a number of cultural differences in the way numbers are text and characters are represented. For example, in US the decimal point is a dot and a thousand separator is a comma.
However in Europe it is opposite. Infact in India we use thousand separator after every two places. So 1,000,000.50 in US is 1.000.000,50 in Germany abd 10,00,000.50 in India. 
So to make sure all formatting respects these cultural differences, every stream has a locale. the locale is an object that handles all aspect of cultural differences. A locale has a set of facets like numerical facet, money facet, etc etc which actually do the formatting. You can attach a locale to a stream using the imbue method.

cout.imbue(std::locale("de_AT.utf8"));
cout << 19.99 << '\t' << fixed << 10000000 << endl;

locale also apply to input streams. If locale is  de_AT.utf8, and you set std::boolalpha on input stream, then you need to enter "falsch" as that is the german for "false".

Extraction 
----------
extraction process is different for C/C++ strings and for other types. For example, when you are extracting an integer the extractor will stop as soon as it finds a character which is not the correct character for parsing integers. Example: "   \t+346abc", the "   \t" will be discarded as input streams by default extract leading whitespaces (use noskipws manipulator to disable this behavior), and +346 is parsed as 346 and the character "a" remains in the buffer as the next character to pe parsed. Similarly for floating pointer number, "\t\t 3.456E+2qwerty" will be parsed correctly as 345.6

but for C/C++ strings the behavior is different. for string the whitespace character is the delimiter. otherwise all other characters are considered legit for strings". Also 

string s;
cin >> s; // you dont need to worry about size of input as string can dynamically grow.
however for c style strings i.e.

char buf[10];
cin >> buf; // if input string is greater than 10 characters, it can overflow in the buf array. So always use "cin >> setw(10) >> buf", in the case for C strings, 10-1 = 9 characters are extracted and buf is null terminated.

string s;
cin >> setw(10) >> s; // this will extract 10 characters and not 9. as string can dynamically grow. this is a subtle difference between C/C++ string extraction. Also string extraction stop when
1) a whitespace character is found
2) a EOF string character is found ('\0')
3) an EOF stream is encountered.
4) a width() limit is reached.

Stream State
------------
IOStreams defines an bitmask iostate which has the following masks/bits to describe the state of a stream.
1) goodbit --> set to TRUE when everything is OK
2) eofbit  --> set to TRUE when an input operation reached end-of-input sequence.
3) failbit --> set to TRUE when an extraction operation fails to extract characters, when an inserter operation fails to produce the required results or some other stream operation fails. this error may be recovervable.
4) badbit  --> set to TRUE when an un-recoverable error occurs on the stream. Maybe the stream has lost its integrity.

the following functions are also available to test the stream state.
bool good() --> returns true if NONE OF eofbit, failbit, badbit is set. AS A RULE OF THUMB, for input streams, use this function to test the stream state.
bool eofbit() --> returns true if eof bit is set on the input stream. output stream operations do not set eof bit so its irrelevant for output streams
bool fail() --> returns true if failbit  or badbit is set. AS A RULE OF THUMB, use this function to test the output stream state.
bool operator !() const --> same as fail().
operator void* () --> returns nullptr is fail() else returns non nullptr.

normally, if stream is in a error state, stream operations do not have any effect. So for a iostream, if a input operation caused the eofbit to be set, then the subsequent output operation on the same stream will also fail. So you will need to clear the state using clear() and setstate() functions.

when if EOF and fail bit set for input operations
-------------------------------------------------
1) Let say you are extracting character by character. You extracted the last character and good() returns true. the next extraction will cause both eofbit and failbit to be set as the end of input is reached and also because the extraction could not extract anything.

2) If you are extracting an integer and the input is "234<EOF>", then eofbit is set as you reach end of input. but failbit is not set as you extracted a value 234.

Stream Exceptions
-----------------
To find out if an stream operation has resulted in an error, you can either
1) perform a state check after every operation. This is trivial and done using the functions, good(), eof(), fail(), etc.
2) tell the stream to throw an exception when an state bit is set and take action. for this you need to call the exceptions() function on the stream object which takes the iostate mask on which states should throw an exception. Also the exception thrown could be either ios_base::failure or any other exception. So you should catch it using catch(...)

try {
    cout.exceptions(ios_base::failbit | ios_base::badbit); // register interest that an exception should be thrown when output stream operations fails.
    cout << x;
    ... // many stream operations which could thrown an exception
} catch(...) {
   if(cout.bad()) {
      // error is unrecoverable. you need to throw. and may be exit with failure
      throw;
   }
   if(cout.fail()) {
      cout.clear(ios_base::goodbit);
      // retry the failed operation.
      return;
   }
}

to clear all the exceptions just call "cout.exceptions(ios_base::goodbit);"

clear(iostate state = ios_base::goodbit) --> clear sets the state to whatever argument you pass. default is goodbit.
setstate(iostate addstate) --> setstate() on the other hand will just OR the current state with the argument you pass.

File Input and Output Streams
-----------------------------
filestreams (i.e ifstream, ofstream, fstream) constructors take two arguments. first is the name of the file. second is the open mode.
1) ifstream. default open mode is ios_base::in. If you specify open mode explicitly, it will be OR'ed internally. so if you say
   ifstream f("tmp.txt", ios_base::ate) // it implies ios_base::in | ios_base::ate
   
2) ofstream. default open mode is ios_base::out. If you specify open mode explicitly, it will be OR'ed internally. so if you say ofstream f("tmp.txt", ios_base::ate) // it implies ios_base::out | ios_base::ate

3) fstream. default open mode is ios_base::in|ios_base::out.

other open modes
----------------
ios_base::ate --> the default file position. file streams have a file position which is by default at beginning of file. however you can specify a different file position by specifying ios_base::ate. ate means At The End. So when a file is open, reading and writing will take place at the end of the file.

ios_base::app --> very similar to ate. Just that everytime you write to the stream. it will write at the end of the file. You can adjust the file position using seekg() etc, but writing will happen at end of file.

ios_base::binary --> this is used to tell the operating system to stop doing any OS specific changes to file. like handling end of line using Ctrl+Linefeed(Windows) or just LineFeed(Unix). It doesnt stop IOStreams from doing its formatting/parsing and code-conversion etc.
Just that the OS will not make any of its specific changes when writing to the file.

Also remember if you have a Bidirectional stream (i.e. fstream object), whenever you switch between input and output, you should always either:
1) flush the current stream
2) set the file position.
otherwise the result is UNDEFINED.

is_open() returns true if stream object is connected to a file.


Memory Input/Output
-------------------
stringstreams provide a way to format/parse stream where external device is a memory buffer. The open modes ios_base::trunc, ios_base::binary are irrelevant for stringstreams.

stringstreams can be initialized using a string argument. also you can get the contents of the buffer using the str() function.
str() is overloaded and can also be used to reset the memory buffer.

int main()
{
    int n;
 
    std::istringstream in;  // could also use in("1 2")
    in.str("1 2");
    in >> n; // n = 1
 
    std::ostringstream out("1 2");
    out << 3; // out = "3 2"
 
    std::ostringstream ate("1 2", std::ios_base::ate);
    ate << 3; // ate = "1 23"
}
The copy of the underlying string returned by str is a temporary object that will be destructed at the end of the expression, so directly calling c_str() on the result of str() (for example in auto *ptr = out.str().c_str();) results in a dangling pointer.

Unlike File Streams, stringstreams have independent read and write position, so you can switch between input and output without any restriction.
-------------------
   
Unformatted Input and Output

If you want to do unformatted input and output, iostreams provide a separate set of functions for that. The normal extractor and inserter operators (<< and >>) always perform formatting and parsing. For input we have the following set of functions.
Just like most insertion and extraction functions for formatted i/o return the stream reference, the unformatted versions also return the stream reference with a few exceptions.
1) get()
2) getline()
3) read()
Multiple overloaded versions are available for each of them. Example for get() we have

int_type get() -> extract and return a single character
istream& get(char_type& ch) --> extract and return a single character in output parameter "ch"
istream& get(char_type*, streamsize); --> same as get(s, count, widen('\n')) below.
istream& get(char_type* s, streamsize count, char_type delim); --> extract at-most (count-1) characters and store in character array pointed by s. Also null terminate the character array. if delim is found, only extract characters before the delim and do not extract the delim. This means the next character you read will be the delimiter. if eof is reached before count-1 characters, also set eof bit. and if cannot extract anything, also set failbit.
istream& get(basic_readbuf& buf); --> same as get(buf, '\n')
istream& get(basic_readbuf& buf, char_type delim); --> read characters till delim and keep inserting in buf until '\n' is found or eof encountered or inserting into buf fails.

std::streamsize gcount() --> very trivial function which returns the number of characters extracted by the last unformatted input operation.

istream& getline(char_type*, streamsize); --> same as getline(s, count, widen('\n')) below.
istream& getline(char_type* s, streamsize count, char_type delim); --> extract at-most (count-1) characters and store in character array pointed by s.

get() and getline() have exact same signature. the difference is:
1) that get() doesnt extract the delimiter, whereas getline() extracts the delimiter but it is just discarded and not stored in the array. 
2) gcount() will count the delimiter when getline() is called but will not count when get() is called.
3) getline() sets failbit if count-1 characters are extracted. get() doesnt set failbit on this condition.
4) Because the terminating character('\n') is counted as an extracted character in getline(), an empty input line does not set failbit.
5) if input is "Rajat$", and you call getline(s, 6, '$'), then count-1 ie 5 characters will be extracted. Since the next character is the delim, this is a special case when getline() does not set failbit although it extracts count-1 characters. that is because it checks first if the next character is the delimiter before it checks that count-1 is extracted. Therefore the input line that exactly fits the buffer does not trigger failbit.
6) istringstream is("rajat"); and you call in is.get(buf, 6); or is.getline(buf, 6). Both will set eofbit. That is because although 6-1=5 characters are getting extracted. both get() and getline() do check for 6th character to see if it is a delimiter. and that will trigger eofbit to be set. However gcount() will return 5 in both cases

istream& read(char_type*s, streamsize count);
Again prototype is same as get() and getline(). But read() reads count characters (get() and getline() read count-1 and null terminate also). read() doesnt null terminate.

----------------------------------------------------------------------------------------------

Some other istream unformatted functions which are available are:

int_type peek() --> get the next character in the stream without consuming it.
istream& unget() --> write the last read character back to the stream, so that it can be read again using get().
istream& putback(char_type ch) --> same as above but you can putback any character you like
istream& ignore(streamsize count, char_type delim) --> keep ignoring the next count characters or until you find delim.
   cin.ignore(numeric_limits<streamsize>::max(), '\n') --> is a very good way of ignoring the current line.

----------------------------------------------------------------------------------------------

Unformatted Output is trivial Just two functions available.

ostream& put(char_type ch) --> insert single character to stream
ostream& write(char_type* s, streamsize count) --> write count characters from buffer "s" to output stream.
----------------------------------------------------------------------------------------------

Stream positions --> streams maintain a write position and read position. istream will only have a read position. similarly ostream will only maintain a write position. Bidirectional file streams maintain a combined/join stream position for both input and output. Bidirectional string streams on the other hand maintain separate read and write positions.

functions to get stream positions

pos_type tellg() --> for input streams (g means get, so input)
pos_type tellp() --> for output streams (p means put, so output)

function to set stream position
istream& seekg(pos_type); --> absolute position fetched from tellg()
istream& seekg(off_type, seekdir); --> relative position from seekdir where seekdir can be ios_base::beg/end/cur 

for bidirectional file streams, seekg/seekp change the joint stream position.
----------------------------------------------------------------------------------------------

Synchronization between streams

The stream classes do no directly access the external devices to read or write character sequences. They do it via the internal buffers they implement. These buffers are managed by classes called stream buffer classes. Stream synchronization is all about synchronizing the stream buffers with the external devices. 

Normally you will not need to worry about stream synchronization as it is managed automatically by the stream buffer classes when the buffers need to be emptied or filled. Output stream buffers implement a function overflow() which triggers synchronization. similarly input streams implement a function underflow(). Also you dont directly call these functions. Read on..

For output streams, the stream class provides a function flush().
For output streams, the stream class provides a function sync().
Both these functions call a function called pubsync() of the underlying stream buffer class. the pubsync() function calls a protected virtual function sync(). When you write your own stream buffer class, you will need to override the sync() function to trigger stream synchronization.

Output file stream buffer classes implement sync() and call overflow() to trigger synchronization.
Input file stream buffer classes implement sync() and call underflow() to trigger synchronization. However note that stream synchronization is not really defined for input streams as you cant say how much you need to read from external device into the buffer.

For input and output string streams, sync() is left unimplemented as there is no external device. The memory buffer itself is the external device hence there is no sync() function.

Other ways of synchronization
----------------------------
1) call flush() or sync().
2) use ios_base::unitbuf format flag. This enables immediate synchronization.
3) Tie an input or output stream to an output stream. Whenever an input or output stream operation is called, the stream will check if it is tied to any output stream. If yes will call flush() on that output stream. example:

  ifstream ifs{"temp.txt"};
  ofstream ofs{"temp.txt"};
  ofs << "Hello World\n";
  ifs.tie(ofs);
  string s;
  cin >> s; // implies ofs.flush() followed by cin >> s;
Note that cin is tied to cout. cerr stream has unitbuf flag set.
----------------------------------
Also remember that according to standard, cout is also synchronized with C stdout. That's the reason output is not garbled when using cout and stdout from separate threads without any explicit synchronization. However you can disable this and achieve performance gain if you promise to use only cout and not stdout.
ios_base::sync_with_stdio(false);
----------------------------------