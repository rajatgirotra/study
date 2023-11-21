The first class for Java network programming we should understand is the InetAddress class. It represents an IP Address and a hostname.
There is no constructor available for this class. Only few static factory methods which manufacture the InetAddress objects for you.

getByName
---------
Very trivial. Takes a DNS name like "www.oreilly.com" and this function will actually perform a DNS lookup (your computer must be connected to internet) to resolve the IPAddress.
This function can throw exceptions on failure. If DNS entry has been cached, then DNS lookup is not performed.

You can also do reverse lookup using this function. i.e. pass a dotted decimal IPv4 address as argument to get an InetAddress back.
this doesn't yet perform a DNS lookup. When the getHostName() function is called. the DNS lookup happens.

getAllByName
------------
A DNS server with round-robin enabled can have multiple different A records, each with the same domain name but a different IP address. So getAllByName() will fetch multiple
IPAddresses. Returns an array of InetAddress.

getLocalHost
------------
returns the DNS entry of the host where you are running your program. If the DNS lookup fails, it may return the loopback address i.e. 127.0.0.1

getByAddress
------------
this function doesn't perform a DNS lookup like getByName, getAllByName, getLocalHost(). It just blindly creates a InetAddress object:1
1) from an ip address. using InetAddress.getByAddress(byte[] array) // a byte array of IPv4 dotted decimal notation.
2) from an ip address and a hostname. InetAddress.getByAddress(String hostname, byte[] array);

Caching
-------
The DNS entry gets cached at multiple places
1) in your code base.
2) on the local host
3) on the DNS server
4) on the DNS servers in other locations.
Since there are so many caches, any DNS name change can take upto several hours to be propagated across the entire internet. During this time, you can occasionally get
UnknownHostException, NoRouteToHostException, ConnectException etc.

You can actually control how long a DNS lookup result will remain cached using Java properties
"networkaddress.cache.ttl" & "networkaddress.cache.negative.ttl". Default for failed/negative lookups is 10 seconds.

Security
--------
DNS lookup is a potential unsecure operation. So many times, the Java security manager will disable DNS lookup due to security reasons (specially in applets).
You can relax this prohibition for trusted code using the SecurityManager checkConnect() function. More on that later or look at the documentation online

SimpleInetUsage.java next