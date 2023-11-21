Socket Options
--------------
Java supports nine options for client-side sockets:
• TCP_NODELAY --> setTcpNoDelay(boolean) to enable/disable nagle's algorithm.
• SO_REUSEADDR -->
• SO_TIMEOUT --> setSoTimeout(), how long to block on a read call.
• SO_LINGER --> setSoLinger(boolean) to make the close() call blocking or non-blocking. If this option is set, any unsent messages are thrown away and discarded.
• SO_SNDBUF --> set size of the TCP send buffer
• SO_RCVBUF --> set size of the TCP receive buffer
• SO_KEEPALIVE --> keep alive the session even if no data is sent on the connection. client will send a packet and expect a response from the server. If no response, the connection will be closed.
• OOBINLINE --> see below
• IP_TOS --> see below

OOBLINE
-------
TCP includes a feature that sends a single byte of “urgent” data out of band. This data is sent immediately. Furthermore, the receiver is notified when the urgent data is received
and may elect to process the urgent data before it processes any other data that has already been received. Java supports both sending and receiving such urgent data.
The sending method is named, obviously enough, sendUrgentData():
public void sendUrgentData(int data) throws IOException
This method sends the lowest-order byte of its argument almost immediately. If necessary, any currently cached data is flushed first.
Reading of urgentData() will be discussed later when there is a need.

IP_TOS
------


SO_REUSEADDR
------------
You already know about the TIMED_WAIT in TCP. The end performing the active close needs to go into this state, so that any packets on the connection which are still
in transit can expire in the network; and a new connection on the same local port will not receive packets from an older connection. However, if you want to disable this,
you can enable this option.

For this to work, setReuseAddress() must be called before the new socket binds to the port. This means the socket must be created in an unconnected state using the noargs
constructor; then setReuseAddress(true) is called, and the socket is connected using the connect() method. Both the socket that was previously connected and the new
socket reusing the old address must set SO_REUSEADDR to true for it to take effect.