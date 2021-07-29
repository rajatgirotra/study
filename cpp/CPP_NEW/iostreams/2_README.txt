Stream Storage
==============
IOStreams provide data fields which can be used to store data dynamically i.e. at runtime. This is an alternate approach to derivation where you can just statically derive from a stream class and add your data members. This approach is dynamic. The way it works is that the ios_base class provides two dynamic array's, one array of long and one array of void* pointers.

long& iword(int index);
void*& pword(int index);

iword() and pword() return references, so the same api is used to both read and write to the arrays. But what about index? how to get index.
ios_base::xalloc() is a static function which is guaranteed to provide a unique index (program wide) each time it is called. this function is thread safe. Also there is no API to return an index back to the stream. Think of xalloc() is atomically incrementing a static integer index. something like static std::atomic<int> index {}; ++index;

Stream Callbacks
================
streams also provide a way to register function callbacks which are called when certain events occur. the callback function prototype is:

typedef void (*event_callback) (ios_base::event, ios_base& stream_object, int user_data) noexcept; where ios_base::event is:
enum event { erase_event, imbue_event, copyfmt_event };

erase_event: issued when a stream is about to be destroyed or when the copyfmt() function of the stream is called. When copyfmt() is called, the erase_event callback is called before any copy has taken place. erase_events are used mostly to delete/free pwords that may be allocated dynamically and must be free'd before the stream is destroyed to avoid memory leaks.

imbue_event: issued when a new locale is imbued to the stream. called after imbue is called, so calling getloc() in the callback will give you the new locale object. If you cache any information from the stream locale, you will be interested in this event so that you can update your cache with the new information from the new locale.

copyfmt_event: this is called when the copyfmt() function of the stream is called. the copyfmt_event callback is called after allmost all data members are copied except the exceptions mask. How this event is used? When this callback is called, the src pword pointers are copied to this stream object's pword. But may be the src stream object pwords() are not meant to be shared. So this callback can be used to make copies of the pwords() and also update its own pwords().

the function used to register a callback is:

ios_base::register_callback(ios_base::event_callback callable, int user_data);
// user_data can be an index of the iword()/pword() which is returned as the third argument of the callback handler (event_callback)


Lifetime of references returned by iword() and pword()
======================================================
you have already seen that iword() and pword() return references to long and void*. These might get invalidated under certain scenarios so i would say best is to not store references to these and rather call iword() and pword() whenever you need to read a long or void* value.
When do these get invalidated?

1) trivial. when stream object is getting destroyed. the iword()/pword() will also get destroyed. so references will dangle.
2) when someone calls iword()/pword(). This is because these functions might need to reallocate more memory and move all data in new memory so old references will dangle.
3) when someone calls copyfmt(), as iword()/pword() arrays are overwritten. so older references are not reliable.
