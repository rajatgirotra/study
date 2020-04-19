It turns out when you want to run applications in a true distributed fashion, you want them to run on different hosts.
to do this using docker, you need a cluster of machines all which have docker running. These cluster of nodes together form a swarm.

the machines belonging to a cluster are called nodes. There are special nodes in the cluster called swarm managers. these are the nodes which can
run your docker commands. the other nodes are just simple worker nodes that provide capacity to the cluster to run docker containers.
you can instruct the swarm managers in how they should distribute services in the swarm. There are many strategies you can use like "emptiest node" ie
(node which has the least load average) and other strategies.

When you ran "docker swarm init", docker goes into swarm mode and also the current machine becomes a swarm manager. Normally you would run 
"docker swarm init" on the manager nodes and run "docker swarm join" to add a machine to a swarm as a worker node. We'll see that.

To explore docker in swarm mode, we will create two VM's using docker-machine command, then use those machines to create a swarm.
we need virtual box also which we already have installed. Basically docker-machine command creates a guest OS with docker installed(both client and daemon),
runs the docker daemon on those machines. You can then issue commands to these guest OS's using docker-machine ssh <machine_name> "<commands>"

to install docker-machine, do
-----------------------------
base=https://github.com/docker/machine/releases/download/v0.16.2 && curl -L $base/docker-machine-$(uname -s)-$(uname -m) >/tmp/docker-machine && chmod +x /tmp/docker-machine && sudo cp /tmp/docker-machine /usr/local/bin/docker-machine

create virtual machine using
-----------------------------
docker-machine create --driver virtualbox myvm1
docker-machine create --driver virtualbox myvm2

Get ip address of the 2 vm's
------------------------------
docker-machine ls

We will make myvm1 as the swarm manager. 
----------------------------------------
For that we need to do "docker swarm init" on myvm1. We can do that using docker-machine itself.
docker-machine ssh myvm1 "command" can be used to send a command to myvm1.

lets run

docker-machine ssh myvm1 "docker swarm init --advertise-addr IP"

the output is:

Swarm initialized: current node (96aji9l295u13ljdmtxvccsii) is now a manager.

To add a worker to this swarm, run the following command:

    docker swarm join --token SWMTKN-1-3yj22f8o1z3dlsrwullhktxb0291gk3icsouulx6azl1zsyujw-denr0c57ljoqlw250vdsqaq5j 192.168.99.100:2377

    To add a manager to this swarm, run 'docker swarm join-token manager' and follow the instructions.

 Add myvm2 as worker
 -------------------
docker-machine ssh myvm2 "docker swarm join --token SWMTKN-1-3yj22f8o1z3dlsrwullhktxb0291gk3icsouulx6azl1zsyujw-denr0c57ljoqlw250vdsqaq5j 192.168.99.100:2377"

Now how do you find which all nodes are part of your cluster
-------------------------------------------------------------
run docker-machine ssh myvm1 "docker node ls"
Sample output
ID                            HOSTNAME            STATUS              AVAILABILITY        MANAGER STATUS      ENGINE VERSION
96aji9l295u13ljdmtxvccsii *   myvm1               Ready               Active              Leader              18.09.5
7cuwptybbh6jx7p0e7tpvhbmq     myvm2               Ready               Active                                  18.09.5

Note: you can run "docker swarm leave" from either VM to leave the swarm


Next step
---------
the hard part is done. What you need to do next, is to run the same "docker stack deploy -c docker-compose.yml" getstartedlab on myvm1 (the swarm manager).
But for that you need to copy or create the docker-compose.yml file into myvm1. however, docker-machine provides some magic that you can directly interact with
a shell from myvm1 from your host os and you dont need to copy any files over. You can also choose to skip this magic and use "docker-machine scp" to copy over files
and then use "docker-machine ssh" to send the "docker stack deploy" command.

lets run

docker-machine env myvm1
then run the eval command which does all the magic

then run
docker stack deploy -c docker_compose.yml getstartedlab
docker stack ps getstartedlab
curl http://192.168.99.100:6666 --> can use ip of either myvm1 or myvm2

All done, now cleanup
---------------------
docker stack rm getstartedlab --> will stop the stack
eval $(docker-machine env -u) --> will bring you back to your normal shell.
docker-machine ssh myvm2 "docker swarm leave"
docker-machine ssh myvm1 "docker swarm leave --force"


Repeat
-------
to repeat the experiment in future, you can start the vm's using
docker-machine start <machine-name>

Next read 5_README.txt
