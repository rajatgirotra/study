Structure of Sys V objects in Kernel.
Each of the structures of msg q, semaphore and shared memory are different in kernel (msgid_ds, semid_ds and shmid_ds).
However, all these 3 have a common substructure "ipc_perm"
structure ipc_perm {
    key_t __key;  // key associated with the IPC object
    uid_t uid;   // owner of this IPC object. Can be used via call to msgctl(), semctl() or shmctl()
    gid_t gid;   // group owner of this IPC object. Can be used via call to msgctl(), semctl() or shmctl()
    uid_t cuid;  // owner of the process who created this IPC object. IMMUTABLE.
    gid_t cgid;  // group owner of the process who created this IPC object. IMMUTABLE.
    unsigned short mode; // permissions
    unsigned short __seq;  // Dont know yet.
    }

struct shmid_ds shmds;
if (shmctl(id, IPC_STAT, &shmds) == -1) /* Fetch from kernel */
    errExit("shmctl");
shmds.shm_perm.uid = newuid;  /* Change owner UID */
if (shmctl(id, IPC_SET, &shmds) == -1) /* Update kernel copy */
    errExit("shmctl");



