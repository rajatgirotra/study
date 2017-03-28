Client Server Interaction with SysV SHM.

Assume a client server application where the server has created the SHM and then both client and server have attached to it and accessing it under synchronization using a SysV semaphore.

What would happen if the server suddenly crashes? or restarts?

Crashes
======
The client would never know that the server crashed and would continue using the SHM.

Restarts
=======
The server would restart but it would have no context of the previous client server interaction.
So what does it do? The approach is that a server should try to create an SHM with IPC_EXCL flag. This way if the SHM already existed from the previous server process, this new process would get an error and would know that a stale SHM exists. It can then use shmctl(IPC_RMID) to delete the old SHM and create a new one. But Alas!!! SHM doesnt get deleted immediately as is the case with Msg Q and Semaphore (their deletion is instanst); a SHM would get destroyed only when all processes using it have called shmdt() on it. So how does the new server process create a new SHM?? Read on...

What happens to the client?
===========================
Assume the server does restart OK and creates a new SHM, the kernel guarantees that a call the shmget() with the same key, the identifier returned will be different. So a client which still tries to use the old identifier would get an error. Infact if we also delete the semaphore along with the SHM when a process restarts, the client will immediately get an error trying to use the old semaphore identifier and it can then assume that the SERVER has restarted. It can then call shmdt(). This way all clients can call shmdt() and finally the kernel old SHM object will be deleted.

So the server should actually call the function to create the SHM (with IPC_EXCL) in a continuous while loop.
