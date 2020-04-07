What is docker?
Docker provides a set of tools and API's to develop, deploy and run applications in a portable way. When you run
an application, let say c++ or python app, you need one or more of the following:
1) tools for development like gcc compiler, or python pip for installing packages
2) dependent libraries like boost, tbb, python requests, flask, django etc
3) a runtime system, like libstdc++, libgcc_s, libpython2.7 etc
4) your own application code
5) your configuration files, data etc.

Docker provides a way to put all these into an image called as the docker image. A docker image is an executable
package which can be run by docker. this running instance of a docker image is called docker container.

you can see the docker containers running using "docker ps" command.

How is it different from a VM. a VM will start a full blown guest OS which will share much more resources with the
host OS than the applications which are running on that VM.

A docker image is lightweight because it only contains and shares with the host OS what it needs.

Why docker?
==========
it makes CI/CD possible
Your applications become portable and scaling is just a matter of spinning up new containers.

Installing
=========
best is to install docker from upstream packages instead of local distros, as docker moves really fast.
Look for docker-engine package.

Docker has 2 editions

1) Community edition (CE): download from  download.docker.com (for Ubuntu xenial : download deb file from https://download.docker.com/linux/ubuntu/dists/xenial/pool/stable/amd64/

2) Enterprise edition (EE): download from https://hub.docker.com/ (docker hub)

Uninstall all old docker versions:
----------------------------------
sudo apt-get remove docker docker-engine docker.io containerd runc

Steps to install from a local deb file:
---------------------------------------

sudo dpkg -i /path/to/package.deb

Verify installation
--------------------
sudo docker run hello-world

This command downloads a test image and runs it in a container. When the container runs, it prints an informational message and exits.

Steps to install from a repository:
-----------------------------------
sudo apt-get update
sudo apt-get install apt-transport-https ca-certificates curl gnupg2 software-properties-common

Verify that you now have the key with the fingerprint XXXXXXXXX… 0EBFCD88, by searching for the last 8 characters of the fingerprint.
-------------------------------------------------------------------------------------------------------------------------------------

sudo apt-key fingerprint 0EBFCD88

Add docker repository
----------------------
sudo add-apt-repository "deb [arch=amd64] https://download.docker.com/linux/ubuntu $(lsb_release -cs) stable"
sudo apt-get update
sudo apt-get install docker-ce

Verify installation
-------------------
sudo docker run hello-world

This command downloads a test image and runs it in a container. When the container runs, it prints an informational message and exits.

Tip:
---

You will see many commands in docker being run as “sudo docker”. This is because when you run a docker command, it connects to the docker engine running on a local Unix socket and that socket is owned by root by default. You can prevent it by creating a separate group for docker and prevent any security threats.

If you don’t want to prefix the docker command with sudo, create a Unix group called docker and add users to it. When the Docker daemon(dockerd) starts, it creates a Unix socket accessible by members of the docker group.

create the docker group.
-----------------------
sudo groupadd docker


Add your user to the docker group.
---------------------------------
sudo usermod -aG docker $USER

Log out and log back in so that your group membership is re-evaluated.
----------------------------------------------------------------------
Verify that you can run docker commands without sudo.
---------------------------------------------------
docker run hello-world

To enable/disable at system restart
-----------------------------------
sudo systemctl enable docker
sudo systemctl disable docker

Image and Containers
====================
Docker has image file. An image file is an executable package that docker can run. It contains everything needed to run your application. When the image is executed, the running instance of that image is called the container (ie when an image is in memory with a state, data etc).

Difference from VM
================
In a VM, you will typically have the Infrastructure (hardware) at the lowest level, followed by the host os; followed by a hypervisor (an app that allows virtualization which is sharing of hardware with other guest OS’es), then you have multiple VM’s running in the guest OS. On a guest OS, you have multiple binaries/libs out of which only a subset is needed to run your application.

On the other hand, in docker, you just have the infrastructure, followed by a docker engine running on it, followed by multiple containers containing only the binaries/libraries needed to run the application in your container. So its not a fully blown setup like a VM. Individual container are usually separated and run in isolation.

Commands
========
docker version (this actually connects to docker engine over a rest api and gets a response back)

docker run hello-world (will download the hello-world image and run it inside a container)

docker ps (will show the list of container running on your system)

docker image ls (will show the list of images downloaded on your host)

docker container ls --all (list the details of the containers which are running or finished).

docker run -p 4000:80 friendlyhello --> run docker image friendlyhello (use tag latest by default)
docker run -d -p 4000:80 friendlyhello --> run docker image friendlyhello in the background. this will return the container id on the terminal.
docker container stop <container_id> --> to stop the container process

docker tag <local_image_name> <tag_name>
where tag_name format is : username/repository:tag
example:
docker tag friendlyhello rajatgirotra/get-started:part2

docker push username/repository:tag --> to push an image to a docker registry.


General syntax : docker <subcommand> --help
-------------------------------------------
The whole purpose of docker is too ship your app, your app dependencies and the runtime together in a portable way. This is done using a Dockerfile. So a Dockerfile contains the details of your docker image. A Dockerfile has its own syntax. Let’s create a simple docker image which contains a basic python installation and runs your python module.

https://docs.docker.com/get-started/part2/

Build a docker image
===============

bash$> ls
Dockerfile  app.py requirements.txt

docker build --tag=friendlyhello .

A docker image will be built in your local docker repository. View it using “docker image ls”. We have exposed port 80 in our Dockerfile which is the port on which our small Flask server in the app.py is running.

     
Running an Image
===============

docker run –p 4000:80 friendlyhello   (ie run the friendlyhello image) and map the host ip 4000 to docker container port 80. You can now open http://localhost:4000/

Use “docker container ls” and “docker container stop <CONTAINER ID> to stop the container.

Use docker –d to run the container in background (as a daemon).

Namespaces
==========

docker uses a concept called namespaces to create a level of isolation of the containers. You can tailor the configuration of these namespaces
to decide what level of isolation your container has compared to other containers or your host OS. The different namespaces of a container are:

the pid namespace (process id namespace)
the net namespace (the networking namespace)
the mnt namespace (the mount namespace)
the uts namespace (the Unix Timesharing system)
the ipc namespace (the IPC resources namespace)

 Control Groups
 =============
 docker engine on linux also uses the cgroup technology. cgroups allows the docker engine to share the available hardware resources with the containers also also enforce certain limits on the resources.


