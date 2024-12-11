Boost asio has a number of type requirements. To understand the various classes in asio nd their relationships, we need to understand some of these type requirements.

There are 3 type requirements for a protocol class and each of these adds to the requirement of the previous type. These are:
1. Protocol: A type X satisfies Protocol if
    - X::endpoint is a type that satisfies Endpoint Type Requirement.
    - a.family(), a.type(), a.protocol() are valid functions all returning "int" for any object "a" of type X.
    Any class
2. AcceptableProtocol: A type X satisfies AcceptableProtocol if
    - X satisfies Protocol.
    - X::socket is a type that derives from basic_socket<X>. basic_socket<X> is a class that provides basic socket functionality.
3. InternetProtocol: A type X satisfies InternetProtocol if
    - X satisfies AcceptableProtocol.
    - X::resolver is of type ip::basic_resolver<X>.
    - X::v4() returns a value of type X representing the IP v4 protocol.
    - X::v6() returns a value of type X representing the IP v6 protocol.
    - a == b is true if a and b represent the same IP protocol version for any two objects a and b of type X.
    - a != b return !(a==b)

If you look at the "ip::tcp" or "ip::udp" or "ip::icmp" classes, they implement this InternetProtocol type requirement.
So these classes will have the following embedded types:
ip::tcp/udp/icmp::endpoint
ip::tcp/udp/icmp::socket
ip::tcp/udp/icmp::resolver
ip::tcp/udp/icmp::v4()
ip::tcp/udp/icmp::v6()
ip::tcp/udp/icmp::family()
ip::tcp/udp/icmp::type()
ip::tcp/udp/icmp::protocol()

There is Endpoint type requirement also, but for now let's not discuss it now and make it overly complicated. We will only focus on ip::basic_endpoint<Protocol> for now.
think of ip::basic_endpoint<Protocol> as a class encapsulating an address and a port number. i.e. it represents an endpoint for an IP socket.

ip::address: implements version-independent IP addresses, i.e. both IPv4 and IPV6 addresses.
ip::address_v4: IPv4 specific address and APIs
ip::address_v6: IPv6 specific address and APIs

string boost::asio::ip::host_name(boost::system::error_code& ec); // returns the host name of the current system.



