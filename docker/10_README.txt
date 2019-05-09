About docker-compose

A docker compose yaml file starts with a "version" key and can have three high level keys
1) services --> used to configure one or more services to be run. services are run inside containers. So you can think
about all configuration here as similar to the command line arguments you pass to the "docker container create" command.

2) networks --> used to create a named network which services can be part of. services within the same network can access
each other. configuration is similar to the "docker network create" command.

3) volumes --> used to mount a path in the container to a path on the docker host. configuration is similar to 
"docker volume create" command.

Let's see the configuration options for the service key first.

1) build
build can have the following keys
   context
   dockerfile
   args
   cache_from
   labels
   shm_size

services:
    webapp:
        build: ./dir

OR

services:
    webapp:
        build:
	    context: ./dir
	    dockerfile: mydockerfile
	    args:
	        buildno: 1

the build option is used to build the image on the fly when you run "docker-compose up". in the first example, docker will search
./dir for a Dockerfile and in the second example it will search for a mydockerfile in the ./dir folder.
The context can be either a relative path (relative to the location of the docker-compose file) or an absolute path or url to a github repository.
The args are arguments passed to dockerfile during the build phase. To pass args, the corresponding Dockerfile should also define arguments
example Dockerfile:

ARG buildno
ARG commithash

RUN echo "Build Number: $buildno"
RUN echo "Based on commit: $commithash"

We can also ommit the argument value in the docker compose in which the argument value is taken from the environment settings where 
compose is running.

Note that "build" flag is ignored when using docker in swarm mode (ie when using docker stack deploy). as docker in swarm mode
only accepts pre-built images. 

build:
  context: .
  cache_from:  # a list of images that engine uses for cache resolution. We'll come back to it in a bit
    - alpine:latest
    - corp/web_app:3.14

Labels are used to add meta data to your images which can be queried later.
build:
  context: .
  labels:
    com.example.description: "Accounting webapp"
    com.example.department: "Finance"
    com.example.label-with-empty-value: ""

 build:
  context: .
  shm_size: '2gb' or an integer specifying the value in bytes. Used to tell how much space under /dev/shm can be used by the build.

 Its a very long tutorial, so better learn by example. Let's get on to the next thing.
