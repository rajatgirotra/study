Lists the docker-machines first
-------------------------------
docker-machine ls

Start the two docker machines you created in 4_README.txt
---------------------------------------------------------
docker-machine start myvm1
docker-machine start myvm2

Make a docker cluster and add manager's and workers
---------------------------------------------------
docker-machine ssh myvm1 "docker swarm init --advertise-addr IP"
and follow instructions to add worker also.

Confirm cluster is well formed
--------------------------------
docker-machine ssh myvm1 "docker node ls"

Create a data directory needed for redis
----------------------------------------
docker-machine ssh myvm1 "mkdir ./data"

Connect to myvm1
-----------------
docker-machine env myvm1
and run the "eval" command

Run your stack
---------------
docker stack deploy -c docker-compose.yml getstartedlab

Check your stack
-----------------
docker stack ps getstartedlab

Check the services in your stack
--------------------------------
docker service ls

Note how the redis and visualizer will always run on a node manager (ie myvm1 here).

Go to web browser and use myvm1 ip and port 8080 to see the status of services in the visualizer.

Then go to web browser and use myvm1 or myvm2 ip and port 80 to see a welcome message with the number of visits (if you dont see the number of visits something is wrong with redis server).
