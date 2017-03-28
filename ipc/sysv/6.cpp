/*
 We'll create a SysV msg Q. You already know that in MsgQ, data is written abd read in units of structured messages. In sysV, along with each message there is also an integer type available. So you can retrieve messages either in FIFO fashion, or by type (which makes it priority based). However there a many disadvantages of SysV msgQ's, so ideally you should use POSIX MsgQ's
*/
#include <sys/msg.h>
#include <unistd.h>
