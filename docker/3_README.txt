Using docker containers as a service
====================================
In any distributed application, you have many components running. Each component running is called a service and does one task. Each service is nothing but an executable. Think of a service as a "docker container running in production." If you want to scale up your application, all you need to do is increase the number of containers running that service. This is possible by using docker-compose command. docker-compose command needs an additional yaml file called docker-compose.yml

A docker-compose.yml file defines how docker containers should behave in production. Lets create a simple docker-compose.yml file.
