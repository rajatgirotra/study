Very simple.
1) Nginx runs one master processes. It is responsible for reading, parsing the configuration file and dynamically applying the config changes on the fly.
2) Several worker processes (as specified in the config), and managing those worker processes. The worker processes are the actual processes which handle user requests.

Nginx is configured via a config file nginx.conf in either
1) /usr/local/nginx/conf
2) /etc/nginx/
3) /usr/local/etc/nginx/
In my case "/etc/nginx/" is the location where nginx.conf and also other configurations are available.

You can play with nginx by sending signals to it.

1) nginx -s stop --> send the immediate shutdown signal
2) nginx -s reload --> reload the config and apply changes
3) nginx -s quit --> gracefully shutdown nginx. Ie dont accept new requests and wait for worker processes to finish their tasks.

Log files
---------
log files are created either in /usr/local/nginx/logs or /var/log/nginx
1) error.log and access.log are the two important log files.

You can either find the pid of nginx master process by ps -eaf | grep nginx or 
by looking in /var/run/nginx.pid file.

starting nginx
--------------
By default nginx starts up automatically on my system. Simply running the "nginx" binary start the server again. You can run "ps" to see the arguments passed to nginx to start it. On my system it shows:
/usr/sbin/nginx -g daemon on; master_process on;
The "-g" option is used to pass directives on the command line. See below for what directives are.
run "nginx -h" for other allowed options. So you can start the nginx server automatically using the command:
"sudo /usr/sbin/nginx -g daemon on; master_process on;"

Directives
----------
directives are nothing but config options. You can have simple directives of the form:
directive_name directive_parameters; OR
directive_name directive_parameters {  --> ie followed by curly braces. This is a block directive
    directive_name directive_parameters; OR
    other block directives;
}
Inside the block we can have parameters for that directive or nested directives.
The directives at the top level are said to be in the main context, and the nested directives are said to be in the context of the directive enclosing it.


Finding config file and log files and pid file
-----------------------------------------------
If you need to find the log file, pid file or config file used on your system, and you only know the location of the nginx executable, it is easy. Just run, 
"sudo nginx -T"  --> This command checks the nginx config syntax and also dumps it along with the location. This config file also has the location of the log files and the pid file location. Very easy.
