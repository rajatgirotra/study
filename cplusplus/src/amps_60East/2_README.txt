AMPS Server
===========
To try out AMPS, just download the package from their website and extract it anywhere on your linux system. There will a bin, lib, docs, sdk folder. For starting the AMPS server, you need only the configuration file. You can generate that using the "ampServer --sample-config". this will be a very simple config. You could also choose to use sample config files bundled with the examples written for a specific client library of AMPS (like for C++ client).

just run ./ampServer --help to see more.

Any AMPS message will have a header (in Json format), followed by a message (in any format like Json, XML, binary etc). As a client library, you will never need to parse or serialize the AMPS header directly. Just use the "Message" and "Command" interfaces to work with the headers.

spark command line client
==========================
AMPS provides a java based client called "spark" used for sending commands to AMPS server and to perform some be-spoke testing. Don't use it in production envs and rather use a proper client. Example:

$AMPSDIR/bin/spark ping -server localhost:9007 -type json --> to test if AMPS server is running on port 9007 and it can accept json.

Monitoring and Observability
=============================
You already read AMPS provides this via a RESTful interface. to enable this you will need to enable the "admin" interface in the config file. The rest endpoint is "https://<host>:<port>/amps/". The REST api's actually fetches the AMPS metrics from a statistics database that AMPS maintains.

There is another tool called "Galvanometer" which is a javascript library which run's in your web browser. It uses web sockets and the REST interface behind the scenes, to provide a visualization of the AMPS metrics. The Galvanometer endpoint is "https://<host>:<port>/"
