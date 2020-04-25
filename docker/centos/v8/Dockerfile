# escape=\
# syntax=docker/dockerfile

ARG centos_version
FROM centos:${centos_version:-8} AS centos

# the centos_version ARG declared above is before the FROM directive, so it is not available inside the build stage
# to make it visible inside the build stage, we declare it here again.
ARG centos_version 

# install man pages and other essentials
ARG devtoolset_version
ARG yum_dnf=dnf
RUN set -ex; \
    \
    ${yum_dnf} -y update; \
    ${yum_dnf} -y install man man-db man-pages; \
    ${yum_dnf} -y install vim which iproute iputils openssh-server openssh-clients wget sudo autoconf automake \
    gcc-c++ tree bzip2-devel sqlite-devel ncurses-devel python2-tkinter python3-tkinter readline-devel gdbm-devel libffi-devel \
    xz-devel tk-devel cyrus-sasl-devel openssl-devel; \
    ${yum_dnf} -y group install "Development Tools"; \
    ${yum_dnf} -y install centos-release-scl; \
    ${yum_dnf} -y install devtoolset-${devtoolset_version:-9}; \
    ${yum_dnf} -y install make;

# for centos devtoolset
RUN set -ex; \
    ${yum_dnf} -y install scl-utils;

# for vim installation
RUN set -ex; \
    \
    ${yum_dnf} -y install ruby ruby-devel lua lua-devel perl perl-devel python python-devel tcl-devel;

RUN set -ex; \
	\
	${yum_dnf} -y install perl-ExtUtils-ParseXS perl-ExtUtils-XSpp perl-ExtUtils-CBuilder perl-ExtUtils-Embed;

# for vim ycm completer.
RUN set -ex; \
	\
	${yum_dnf} makecache; \
	${yum_dnf} -y install cmake clang;

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
# RUN umask 022

