Sys V IPC can be used for three different IPC mechanisms.
1) Message Queues
2) Semaphores
3) Shared Memory

Message Queues are similar to PIPES. However message queues are used to read and write structured data as opposed to PIPES which read and write a sequence of bytes. So in message queues, data actually has boundaries. Also with Sys V message queues, you can associate an integer "type" key with each message, and the receiver can read messages based on key instead of reading them sequentially as they written into the queue.

Semaphores are used for interprocess synchronization.
SHM you already know.

On almost all linux implementations, Sys V API's are library functions, and all these functions have a common interface to talk to the kernel via the "ipc()" system call. But people sometimes errorneously call these library functions as system calls.

Also the SysV IPC API's are very simple and follow a format.

Header Files are: <sys/msg.h>, <sys/sem.h> and <sys/shm.h>
Opening/Creating a Sys V IPC object is: msgget(), semget() and shmget()[+shmat()]
Closing IPC object: None, None and shmdt()
Control operations: msgctl(), semctl(), shmctl()
Sending/receving: msgsend()/msgrcv(), semop(), None
Underlying Data strcutures are: msgid_ds, semid_ds, and shmid_ds

All Sys V IPC calls are based on an integer key, just like file operations are based on file descriptors.
You must first Create/Open a Sys V IPC object using an key. When the call is successfull, you get back and integer identifier. This identifier must be used in all future calls to other functions. So basically the input argument is also an integer key and the output is an integer identifier. This identifier is what needs to be used in all future calls on that IPC object.

For example:
Opening/creating msg q object:

    int id = msgget(key, IPC_CREAT|S_IRUSER|S_IWUSR);
The call works as follows:
the kernel checks if the specified key has been already mapped to an identifer already.
1) If no, and IPC_CREAT was specified, then it creates a new Sys V IPC object and returns an identifier for it.
2) If no, and IPC_CREAT was NOT specified, return error ENOENT (NO Entry exists).
3) If yes, then returns the identifer corresponding to the Sys V IPC object that already exists.
So this way multiple processes can use the same IPC object if they use the same key. Infact, if one process creates
and IPC object and gets an identifier, and the other process gets to know of the identifier in some way, it can actually skip the get() call alltogether.

Lets also talk about msgctl() for control operations. See the operation below:
int id = msgctl(identifier, IPC_RMID, NULL);
This call is used to delete the IPC object and remove the mapping from the key to identifier in the kernel.

1) For Message Qs and Semaphores, the deletion is instant. So any data in the msg q and any state of the semaphore will be immediately lost.
2) For SHM, the behavior is slightly different. The SHM will be destroyed when the last process detaches from the SHM using shmdt() [Somewhat similar to how file is deleted only when the last process with an open file descriptor calls close]

You should make sure you delete Sys V IPC objects and they do not get destroyed automatically when the process goes down. So they can actually cause the objects to get exhausted over a period of time of the box is not rebooted. On reboot and objects are destroyed. However a problem is that only one process should call msgctl() to destroy the object. So in a multi process environment which process should call it, it is difficult to ascertain that.


