Please read 7_README.txt first. Let's try to understand the docker-stack.yml file in example-voting-app

Let's first understand what is this "networks". A service in a compose can have one or more networks. Here for example
we have two networks: frontend and backend. Services which are on the same network can access other services on the same network
by using their service name. Services can also discover other services if they are on the same network.

When you deploy a docker stack, each service actually runs in its own container. But these services might need to talk/interact with
each other for several purposes
1) load balancing
2) scalability
3) failover
4) service discovery
 
I'll quicky revise what a docker swarm is:
A docker swarm is a cluster of docker nodes. A node can be a manager or a worker or both. A docker-compose.yml file is used to list 
the various services you want to run on the cluster. For each service, you can specify things like
1) the image to run
2) the number of replica's
3) storage requirements
4) ports it exposes
5) CPU and RAM utilization and many other things

docker swarm managers are responsible for maintaining sure that services are run based on the criteria mentioned in the docker-compose.
When a service is run in a swarm, it is called a task. A task is nothing but a running container managed by the swarm managers.
You can also change the configuration (docker-compose.yml) and do a hot re-deploy. Means you dont need to stop and restart all services.
docker will see for you which services need a restart due to configuration changes. 

Stand-alone containers do not get this advantage.

We'll come back to understanding the rest of docker-stack.yml file later.
