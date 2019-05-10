Docker multi stage builds --> Why we need it
-------------------------
Build and run time dependencies are always different. Run time dependencies will almost always be a stripped down
version of the build time dependencies. For example, you wont need the full gcc compiler at runtime, you wont need any boost header files
etc etc. You wont need google test libraries.

So basically before multi stage builds were introduced, people had to write two docker files to create two images.
one for build and another stripped down image for production. They also had to write a script to extract the actual artifacts
needed from the build container and then put it into the production container. Example

Dockerfile.build --> build Dockerfile
----------------

# from golong base image
FROM golang:1.7.3

WORKDIR /go/src/github.com/alexellis/href-counter/

COPY app.go .

RUN go get -d -v golang.org/x/net/html \
  && CGO_ENABLED=0 GOOS=linux go build -a -installsuffix cgo -o app .

Production Dockerfile
----------------------
FROM alpine:latest
RUN apk --no-cache add ca-certificates
WORKDIR /root/
COPY app .
CMD ["./app"]

script (build.sh)
------------------
#!/bin/sh
echo Building alexellis2/href-counter:build

# will use Dockerfile.build to build a google go application. image name will be href-counter:build
docker build --build-arg https_proxy=$https_proxy --build-arg http_proxy=$http_proxy \
    -t alexellis2/href-counter:build . -f Dockerfile.build

# create a container out of the build image
docker container create --name extract alexellis2/href-counter:build

# just extract the "app" go executable. The executable is extracted out of the container (ie on the host where the script is run)
docker container cp extract:/go/src/github.com/alexellis/href-counter/app ./app

# remove the container
docker container rm -f extract

echo Building alexellis2/href-counter:latest

# create a new docker image for production (using Dockerfile) which copies the "app" executable in it.
docker build --no-cache -t alexellis2/href-counter:latest .

# finally remove the "app" executable from the docker host
rm ./app


As you can see this was very cumbersome.

So multistage builds were introduced. In a multi stage build a Dockerfile can have more than one "FROM" directives.
Each from directive starts a new build stage. By default build stage's are numbered starting from 0. You can also give a name
to your build stage using the "FROM rajatgirotra/hello:latest AS STAGE1" syntax and refer to artifacts of this stage using the name
"STAGE1". This way you dont have to write separate bash scripts and the Dockerfile also becomes very easy and maintainable. 
Earlier you had to maintain multiple Dockerfiles for build and production. You can also decide to execute instructions only till a given
build stage if you want. Example of multistage build file is:

--------------------------------------------------------------------------------------------------------
FROM golang:1.7.3
WORKDIR /go/src/github.com/alexellis/href-counter/
RUN go get -d -v golang.org/x/net/html
COPY app.go .
RUN CGO_ENABLED=0 GOOS=linux go build -a -installsuffix cgo -o app .

FROM alpine:latest
RUN apk --no-cache add ca-certificates
WORKDIR /root/
COPY --from=0 /go/src/github.com/alexellis/href-counter/app .
CMD ["./app"]
--------------------------------------------------------------------------------------------------------


So now to setup a build environment, we would need to do the following
1) create a dockerfile to build the following
  a) latest gcc
  b) git
  c) cmake
  d) python
  e) gdb + gdbserver (gdb needs python)
  f) valgrind
  g) doxygen
  h) vim
  i) google test
  j) google benchmark
  And any other basic dependencies you can think of for build.

2) Then we need to create multiple Dockerfiles (one for each of the following dependencies)
    a) boost
    b) json parser
    c) python packages like  numpy, pandas, etc
    d) libevent
    e) nodejs
    f) postgresql and libpqxx
    g) spdlog (open source logger)
    h) google protobuf

 3) Then have a Dockerfile for your project (which depends on above)

 4) A dockerfile which depends on all of the above, fires a build on its own and prepares a production package


 Lets try to do all this in CentOS docker image as base
