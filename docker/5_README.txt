up until 4_README.txt, your docker stack had only one service (your docker-compose.yml had only the web service).
Here we will go one step further and add more services to our docker-compose.yml as a typical distribution application
has multiple services. We will add two services:

1) redis: to track how many hits we received on our web service
2) a visualizer service: which allows us to view the status of the services running on the swarm cluster.

Let's get started. Please read
