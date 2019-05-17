FROM centos:7

# install man pages and other essentials
RUN set -ex; \
    \
    yum -y update; \
    yum -y install man man-db man-pages; \
    yum -y install vim which iproute iputils openssh-server openssh-clients wget sudo autoconf automake \
    gcc-c++ tree bzip2-devel sqlite-devel ncurses-devel tkinter readline-devel gdbm-devel libffi-devel \
    xz-devel tk-devel cyrus-sasl-devel openssl-devel; \
    yum -y group install "Development Tools"; \
    yum -y install centos-release-scl; \
    yum -y install devtoolset-8; \
    yum -y install make;

RUN set -ex; \
    yum -y install scl-utils;

# enable ssh
# RUN systemctl enable sshd

# change password for root
RUN echo 'root:root' | chpasswd

# create /app directory
RUN mkdir -p /app

# create user devtools where all thirdparty tools will be installed.
RUN useradd --home-dir /app/devtools --create-home --shell /bin/bash devtools

# add user devtools to wheel group. users in this group have sudo priviledge
RUN usermod -aG wheel devtools

# change password for devtools
RUN echo 'devtools:devtools' | chpasswd

# create user rajatgirotra for development
RUN useradd --create-home --shell /bin/bash rajatgirotra

# add user devtools to wheel group. users in this group have sudo priviledge
RUN usermod -aG devtools rajatgirotra

# change password for devtools
RUN echo 'rajatgirotra:santro2243' | chpasswd

# change default umask
RUN umask 022

# create a thirdparty folder
USER devtools
WORKDIR /app/devtools
RUN mkdir thirdparty
RUN chmod 755 /app/devtools
# RUN scl enable devtoolset-8 bash

# install patchelf
RUN set -ex; \
	\
	wget https://github.com/NixOS/patchelf/archive/0.10.tar.gz -O patchelf.tar.gz; \
      	tar xvf patchelf.tar.gz; \
	cd patchelf-0.10; \
       	./bootstrap.sh; \
      	./configure --prefix=/app/devtools/thirdparty; \
        make; \
        make install

# install python 3.7
RUN set -ex; \
	\
	wget https://www.python.org/ftp/python/3.7.3/Python-3.7.3.tar.xz; \
       	tar xvf Python-3.7.3.tar.xz && cd Python-3.7.3; \
	./configure --prefix=/app/devtools/thirdparty --with-ensurepip=upgrade --enable-optimizations; \
        make; \
	make install; \
	cd /app/devtools/thirdparty/bin; \
       	./pip3 install --upgrade pip; \
       	./pip3 install virtualenv pipenv

USER rajatgirotra
WORKDIR /home/rajatgirotra

CMD scl enable devtoolset-8 bash
