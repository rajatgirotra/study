We will create and deploy one more docker stack with multiple services and a more complex docker-compose file.
This will give you better understanding of docker stack deployment in swarm.

For this application we will use the Docker Example Voting App. This app consists of five components:

Python webapp which lets you vote between two options
Redis queue which collects new votes
.NET worker which consumes votes and stores them in…
Postgres database backed by a Docker volume
Node.js webapp which shows the results of the voting in real time
Clone the repository onto your machine and cd into the directory:

Do
---

git clone https://github.com/docker/example-voting-app.git
cd example-voting-app

Start your docker vm's myvm1 and myvm2. Make myvm1 as manager and myvm2 as worker
---------------------------------------------------------------------------------

docker-machine ls
docker-machine start myvm1
docker-machine start myvm2
docker-machine ssh myvm1 "docker swarm init --advertise-addr <myvm1 IP>
<some command to add myvm2 as worker>

Attach to myvm1
---------------
docker-machine env myvm1
eval $(....)

deploy your app 
----------------
docker stack deploy --compose-file docker-stack.yml vote

confirm services are up
------------------------
docker stack services vote

open in browser
--------------
http://myvm1IP:5000

Re-deploy
---------
Now change the vote and result services (just change the image tag from before to after), and re-deploy.
Redeploying is the same command.
docker stack deploy --compose-file docker-stack.yml vote

open in browser
--------------
http://myvm1IP:5000 --> note that Cats and Dogs is replaced by Java and .NET

Shutdown everything
--------------------
docker stack rm vote

You already know how to remove nodes from swarm and how to shutdown the vm's.

Please read 8_README.txt to understand the docker-stack.yml file.

