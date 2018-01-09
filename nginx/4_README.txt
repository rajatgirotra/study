You have already seen that nginx can be controlled by sending signals to it. 

nginx -s reload
nginx -s stop
nginx -s quit etc

You can also send signals to nginx using the "kill" command. The following signals are supported, that can be sent to the master process.

kill -s TERM
kill -s INT
Will fast shutdown nginx

kill -s QUIT 
will gracefully shutdown

kill -s HUP
will reload the config

kill -s USR1
will re-open log files

kill -s USR2
will upgrade the nginx executable

kill -s WINCH
will gracefully shutdown the worker processes.

use "kill -l" to list the signals

