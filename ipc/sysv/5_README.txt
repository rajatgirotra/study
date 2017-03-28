Key to Identifier Algorithm
===========================

The kernel maintains an internal data structure ipc_ids (one each for MsgQ, Sem, and SHM) which has
struct ipc_ids {
    int size;    // maximum number of IPC objects of this type
    int in_use;  // number of IPC objects currently in use
    int max_use; // the maximum index in the entries array currently in use. There may be many free spots in between as IPC objects get deleted.
    int seqid;   // a unique incremental sequence number assigned to each IPC object and part of the shmid_ds structure. Max is 65535.
    shmid_ds* entries;  // an array of atleast size entries. Each shmid_ds has details of one IPC object.
};

Algo is very straight forward

1) msgget(key, ch) -- Iterate over entries array and find if any IPC object has key. If no and IPC_CREAT was not specified, then return ENOENT.
2) If key is found, and IPC_CREAT and IPC_EXCL both are specified then return EEXIST.
3) If no match was specified, and IPC_CREAT was specified, then a new data structure of shmid_ds is allocated, and an entry is put into the entries array at the first free slot. The key specified is put in the "key" field of shmid_ds. The seq number from ipc_ids is copied to shmid_ds and then seq no in ipc_ids is incremented. A unique identifer is generated:
    unique identifier = index in Entries array + (seq * SEQ_MULTIPLIER) ;  // SEQ_MULTIPLIER is const
 This way even get() calls with the same key do not get the same identifier because it depends on the index in the entries array also.

Dont know what would happen if Key is found and IPC_CREAT is specified but not IPC_EXCL.
Run and check.

IPCS and IPCRM
==============
These are like ls and rm on Unix but for shared memory. ipcs will display information on IPC
objects in the system. ipcrm is used to delete IPC objects. Many flags/switches are available to format out of ipcs.
Otherwise the non-portable way of getting this information is via the /proc filesystem.
cat /proc/sysvipc/shm
cat /proc/sysvipc/sem
cat /proc/sysvipc/msg

Lets get to creating some sysv IPC objects now.
