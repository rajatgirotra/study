Using docker containers as a service
====================================
How to installing docker compose
-------------------------------
sudo curl -L https://github.com/docker/compose/releases/download/1.24.0/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose

Why we need docker-compose
---------------------------
In any distributed application, you have many components running. Each component running is called a service and does one task. Each service is nothing but an executable. Think of a service as a "docker container running in production." any big application will have more than one services like Broker, ExecutionService, TickServer, Gunner, UIServer etc
All these can be thought of as docker containers. But we may want to run one or more instances of these services for various reasons like load-balancing, failover from primary to secondary etc. This is called scaling a service. With docker scaling becomes very easy by using docker-compose. We need to write a docker-compose.yml file.

A docker-compose.yml file defines how docker containers should behave in production. Lets create a simple docker-compose.yml file.

See files in friendlyhello_compose and then return to 4_README.txt
