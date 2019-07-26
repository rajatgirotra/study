A very common use of nginx is to use it as a proxy server. Ie it will forward the HTTP requests to another server and will retrieve responses from the server and send it back to client. Let's create another server block to create a proxy server

server {
    listen 8080; # by default if listen parameter is not provided, it means port 80.
    # if you note we did not provide listen parameter when creating a server block for serving static content.
    root /data/up1;

    # root directive at the server level means that whenever a location directive will not have a root parameter, the server root directive will be used.

    location / {
        # no root directive, so all requests will be mapped to /data/up1 on the filesystem.
        # you can try by putting an index.html there. 
    }

    # ~ means a regular expression match. The regular expression is anyfile ending with .jpg, .png or .gif will be mapped to /data/images/
    location ~ \.(jpg|png|gif)$ {
        root /data/images;
    }
}

if you now go to: http://localhost:8080/index.html or just http://localhost:8080, it will map to /data/up1/index.html
 AND
http://localhost:8080/sample.png will be mapped to /data/images/sample.png


We can now change the empty location directive again to forward all HTTP requests on port 80 using:
server {
    # Forward everything on port 80 to port 8080
    location / {
        proxy_pass http://localhost:8080/;
    }

    # Map all image files to /data/images/ on the filesystem
    location ~ \.(jpg|png|gif)$ {
        root /data/images;
    }
}
