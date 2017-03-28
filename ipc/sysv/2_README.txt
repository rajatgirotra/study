Lets say two unrelated processes want to create and IPC object each. How do they make sure that they specify unique key so that unique IPC objects are created.
Two ways:
1) Use IPC_PRIVATE as the key argument to msgget()
int id = msgget(IPC_PRIVATE, S_IRUSR|S_IWUSR); will always generate a unique key and create a new shared object. Infact no need to specify IPC_CREAT in this case. This technique is mostly used when a process needs to fork a child and both parent and child can then share the same id and work on the same IPC object.

2) use ftok(char* filename, int proj) - This call returns a unique key based on the inode number of the path specified by the filename and the "proj" argument. Make sure that filename already exists before calling ftok.
   auto fd = open('/path/to/file', ...);
   int key = ftok('/path/to/file', 'A'); // proj should be a char for portability. Combination of filename and proj give a unique key. Used in cases when processes are unrelated (ie no parent child relationship)
