the only thing to understand in docker-compose.yml is

1) deploy.placement.constraints: --> This is used t make sure if a service must run on a node manager only. Here that is needed
because the visualizer service works that way

2) volumes key: This maps a host location to a container location. Example for redis we have
/home/docker/data:/data
This means anything written to /data inside the container will be mapped to /home/docker/data on the host. If we dont have this
then all data (like logs and other persisted files by your app) will be destroyed when the container is stopped.
