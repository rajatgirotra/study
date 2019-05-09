Please read 9_README.txt first

commands
--------
Create Dockerfile, app.py, requirements.txt, docker-compose.yml

docker-compose up

this command will see that to run the "web" image, it needs to build an image from the local directory. So it will do that.
Then it will run both the "web" and "redis" services

docker image ls  --> will show composetest_web and redis both

bring the services down with

docker-compose down

Now add the volumes key to point the compostest host directoy to /code in the image

docker-compose up --> to restart the services again. But this time note that the current directory is actually a mount
point for /code in the image. This means you can straightaway modify the app.py now and then see the result in the browser.
That's because flask can track changes and then redeploy.

docker-compose down --volumes --> stops services and also unmounts
