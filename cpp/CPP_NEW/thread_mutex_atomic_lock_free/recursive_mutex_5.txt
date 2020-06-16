/*
same as std::mutex, except that the std::recursive_mutex can be locked multiple times over. Every call to lock should be followed by an unlock() call for the thread to release the mutex.
*/
