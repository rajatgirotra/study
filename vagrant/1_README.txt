What it is??

Basically it provides a wrapper over different virtualization softwares like VirtualBox, VMWare, AWS etc.
You can use vagrant with any of the above as a backend.

Vagrant provides a host of guest operating system images, which you can download. Then you can work in any
of the environments you like.

When you download an OS image, vagrant saves it as a base image in ~/.vagrant/
Then you can create multiple guest OS environments and install whatever dependencies you would like to install in those guest OS'es for you vagrant project.
You can create multiple such vagrant projects, and these project environments always remain separate in their own project folders
and do not modify the base image.

Each project has a Vagrantfile which tells what guest environments to start and other configuration and dependency settings.

Very trivial to install, just download vagrant debian package and install on ubuntu like.:
dpkg -i <vagrant.deb>

Also install virtualbox in the same way as vagrant as we'll use that as a backend.


Commands
========

vagrant box add hashicorp/trusty64 - To download a base image from Vagrant store Image name is hashicorp/trusty64
vagrant box remove hashicorp/trusty64 - To remove a base image from ~/.vagrant
vagrant up --> to bring up a Vagrant guest OS.
vagrant halt --> to shutdown
vagrant destroy - to destroy the virtual image
vagrant ssh <machine-name> -- to ssh into the guest OS.
vagrant reload --provision
vagrant suspend -- Similar to sleep
vagrant up --provider=vmware_fusion
vargrant resume - To restart after vagrant suspend

To create a new Vagrant Project, create a folder and run in that folder:
vagrant init --> this will create a default Vagrant file which you can edit. Many of the options in the vagrantfile are relative to this project directory.
Then change the config.vm.box = "hashicorp/trusty64" in the Vagrantfile and do
"vagrant up"
and "vagrant ssh" to ssh into it.
Note that /vagrant in the guest OS is a soft link to your project directory on your host system. So dont do rm -rf / accidently.


Provisioning
============

config.vm.provision "shell", inline: "echo Hello"

sudo /etc/init.d/vboxdrv setup
