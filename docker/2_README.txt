Please read friendlyhello_/Dockerfile.

Go inside friendlyhello_1 and do
docker build --tag=friendlyhello .

1) docker build is used to create an image from a Dockerfile.
2) an image must contain a tag used to identify it.
3) Once an image is built, it is stored by default to your local docker repository. "docker image ls" should show it.
4) You can push the image to a registry. dockers default registry is DockerHub (hub.docker.com). You can also have your own public or private registry.
5) Inside a registry you can create a respository where you can push your images.
6) Every image must be tagged so others can download the image based on the tag.
7) You must create an account on the registry website. For example, i created an account on DockerHub as rajatgirotra and my usual password. To push to a registry, you must first be logged in. Use "docker login" to login to DockerHub
8) Tagging and pushing and pulling is very trivial.

docker tag image username/repository:tag
docker push username/repository:tag
docker run <options> username/repository:tag --> this will also pull the image and run in a container.
Example: docker run -p 4000:80 rajatgirotra/get-started:part2
