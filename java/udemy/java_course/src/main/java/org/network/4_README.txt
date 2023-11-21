SocketAddress is a very trivial class to hold an IP and Port. The only subclasses of SocketAddress are InetSocketAddress and UnixDomainSocketAddress.
Usage:

Usage 1
-------
Socket socket = new Socket();
SocketAddress address = new InetSocketAddress(SERVER, PORT);
socket.connect(address);

Usage 2
-------
var remoteEndpoint = socket.getRemoteSocketAddress();
var localEndpoint = socket.getLocalSocketAddress();

Usage 3
-------
Socket socket = new Socket("www.yahoo.com", 80);
SocketAddress yahoo = socket.getRemoteSocketAddress();
socket.close();
Socket socket2 = new Socket();
socket2.connect(yahoo);

// 5_README.txt next