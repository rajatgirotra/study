To run docker-compose.yml, we need to run 
"docker stack deploy -c docker-compose.yml getstartedlab"

getstartedlab is the name which we give to our app.

Before you run "docker stack deploy", you need to create a node with docker which you will think of as a swarm manager.

docker swarm init  --> does that, lets see in action
docker stack deploy -c docker-compose.yml getstartedlab --> getstartedlab is the name of the app.

"docker container ls" will now show 5 containers running in a load balancer mode.

"docker service ls" will show how many services are running and their details. Our docker-compose.yml has a single service "web". We say our stack has a single service.
the output of the command above shows the app name suffixed with the name of the service you defined in the docker-compose.yml. 
It shows "getstartedlab_web"

How do you find which all containers running are associated with the stack service. you use "docker service ps getstartedlab_web" or "docker stack ps getstartedlab"
Note the difference: when you use "docker service ps" you need to give the stack name and the service name both
and when u use "docker stack ps" only stack name is sufficient.
Each container running as part of this service is called a "TASK" in docker. Tasks are given a numerically incrementing number based on the number of replicas you have configured.

To shut down all services, use "docker stack rm getstartedlab"

and finally take the swarm down with "docker swarm leave --force"
