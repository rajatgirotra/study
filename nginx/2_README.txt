// Serving static content. The most basic use of a web server is to serve static content, ie images, files, static we pages etc. Lets setup nginx.conf to serve static content. We will need the following directives

http {
   server {
      location {
      }
   }
}

https, server, location are all directives.

nginx.conf can have several server directives based on the port on which they listen to and also the server names. When an HTTP request is received, nginx determines which is the correct server and uses the parameters from that server block directive.

So lets go and comment all server directives and add one for serving static content.
http {
    server {
        location / {  # / is called location prefix
            root /data/www;
        }
        location /images/ { # /images/ is called location prefix
            root /data;
        }
    }
}

Let say the HTTP request URI is http://example.com/images/sample.png. Then the URI "/images/sample.png" is supposed to be resolved. nginx looks at location prefix of each location directive and matches it to the URI. So in our case where URI is /images/sample.png
1) location prefix / matches /images/sample.png (the leading /)
2) location prefix /images/ matches /images/sample.png (the leading /images/)
When there is a match, or when there are multiple matches, nginx chooses the longest prefix, so in our case /images/ will win. Now whatever is in the root parameter of that location directive will be prepended to the URI to get the location on the filesystem. So the filesystem location becomes.
/data followed by the URI ie --> /data/images/sample.png. So now we will need to create /data/images/sample.png

When I tried this it failed for me, because "nginx -T" already showed a server directive in the main context with "root /var/www/html". By default nginx had this config in /etc/nginx/sites-enabled. So i need to disable sites-enabled, and then this example worked.

DISABLING sites-enabled
-----------------------

you will have two directories in /etc/nginx

/etc/nginx/sites-enabled and /etc/nginx/sites-available.

/etc/nginx/sites-available defines conf files for all virtual hosts. and
/etc/nginx/sites-enabled/ just have soft links to conf files in /etc/nginx/sites-available

In the main nginx configuration, /etc/nginx/nginx.conf, you have the following line:

include /etc/nginx/sites-enabled/*;
disable this line and then retry the above.

So basically to list all available virtualhosts, you can run the following command:

ls /etc/nginx/sites-available
To activate one of them, run the following command:

ln -s /etc/nginx/sites-available/www.example.org.conf /etc/nginx/sites-enabled/

