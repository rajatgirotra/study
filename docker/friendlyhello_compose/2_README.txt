To run docker-compose.yml, we need to run 
"docker stack deploy -c rajatgirotra/get-started:part2"

Before you run "docker stack deploy", you need to create a node with docker which you will think of as a swarm manager.

docker swarm init  --> does that, lets see in action
docker stack deploy -c docker-compose.yml getstartedlab --> getstartedlab is the name of the app or service
