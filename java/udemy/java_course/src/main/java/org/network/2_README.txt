URLEncoderDecoder.java first

Proxy && ProxySelector class
============================

Many times on your linux servers, you do not have direct access to internet and you go via a proxy. A proxy can be setup for several reasons.
1) You dont want the remote website/server to know anything about your local network configuration/browser etc.
2) You want to put some filters/restrictions on which websites can be accessed.
3) You want to improve performance, so that websites cached locally can be used by all users.

to have your JVM use proxy servers. you will need to set the java properties "http.proxyHost" and "http.proxyPort" either in code or on the command line.
So can also set the "http.nonProxyHosts" which is a pipe separated list of websites which should be accessed directly without a proxy.

java -Dhttp.proxyHost=192.168.254.254 -Dhttp.proxyPort=9000 -Dhttp.nonProxyHosts="*.oreilly.com|*.cs.intra.net" <Other Args> <Program>

OR
System.setProperty("http.proxyHost", "192.168.254.254");
System.setProperty("http.proxyPort", "9000");
System.setProperty("http.nonProxyHosts", "*.oreilly.com|*.cs.intra.net");

For more fine-grained control, you can use the Proxy and ProxySelector class. There is a ProxySelector class which you can extend and override two abstract method in that class:
1) List<Proxy> select(URI uri) --> For each URI, you can choose a list of Proxy objects to try to reach that website.
2) void connectFailed(URI uri, SocketAddress sa, IOException ioe) --> Handle what to do if a request fails, like use a special Proxy object PROXY.Type.DIRECT (i.e. use direct connection
next time instead of using a Proxy)

// how to use your new ProxySelector class. Only one proxy selector can be chosen across the JVM.
ProxySelector selector = new LocalProxySelector():
ProxySelector.setDefault(selector);

Creating a new Proxy object is very trivial if you know the proxy host and port.
SocketAddress sa = new InetSocketAddress("proxy.cs.intra.net", 80);
Proxy proxy = new Proxy(Proxy.Type.HTTP, sa);

Proxy types are Proxy.Type.HTTP, Proxy.Type.DIRECT and Proxy.Type.SOCKS (i.e. TCP)