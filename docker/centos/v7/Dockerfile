FROM centos:7

# install man pages and other essentials
RUN set -ex; \
    \
    yum -y update; \
    yum -y install man man-db man-pages; \
    yum -y install vim which iproute iputils openssh-server passwd openssh-clients wget sudo autoconf automake \
    gcc-c++ tree bzip2-devel sqlite-devel ncurses-devel tkinter readline-devel gdbm-devel libffi-devel \
    xz-devel tk-devel cyrus-sasl-devel openssl-devel; \
    yum -y group install "Development Tools"; \
    yum -y install centos-release-scl; \
    yum -y install devtoolset-9; \
    yum -y install make;

# for centos devtoolset
RUN set -ex; \
    yum -y install scl-utils;

# for vim installation
RUN set -ex; \
    \
    yum -y install ruby ruby-devel lua lua-devel perl perl-devel python python-devel tcl-devel;

RUN set -ex; \
	\
	yum -y install perl-ExtUtils-ParseXS perl-ExtUtils-XSpp perl-ExtUtils-CBuilder perl-ExtUtils-Embed;

# for vim ycm completer.
RUN set -ex; \
	\
	yum makecache; \
	yum -y install cmake clang;

# enable ssh
RUN set -ex; \
	\
	mkdir -p /var/run/sshd; \
	ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N '';

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

# add user rajatgirotra to wheel and devtools group. users in this group have sudo priviledge
RUN usermod -aG devtools rajatgirotra
RUN usermod -aG wheel rajatgirotra

# change password for devtools
RUN echo 'rajatgirotra:rajatgirotra' | chpasswd

# change default umask
RUN umask 022

# create a thirdparty folder
USER devtools
WORKDIR /app/devtools
RUN mkdir thirdparty
RUN chmod 755 /app/devtools
# RUN scl enable devtoolset-9 bash

# install patchelf, just a C library
RUN set -ex; \
	\
	wget https://github.com/NixOS/patchelf/archive/0.10.tar.gz -O patchelf.tar.gz; \
      	tar xvf patchelf.tar.gz; \
	cd patchelf-0.10; \
       	./bootstrap.sh; \
        ./configure --prefix=/app/devtools/thirdparty; \
        make; \
        make install

# install sqlite3, just a C library
RUN set -ex; \
	\
	wget https://www.sqlite.org/2020/sqlite-autoconf-3310100.tar.gz; \
      	tar xvf sqlite-autoconf-3310100.tar.gz; \
	cd sqlite-autoconf-3310100; \
       	./configure --prefix=/app/devtools/thirdparty --enable-readline; \
        make; \
        make install

## install python 3.8, just a C library
RUN set -ex; \
	\
	wget https://www.python.org/ftp/python/3.8.2/Python-3.8.2.tar.xz; \
       	tar xvf Python-3.8.2.tar.xz && cd Python-3.8.2; \
        PATH=/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib ./configure --prefix=/app/devtools/thirdparty --enable-shared --with-ensurepip=upgrade --enable-optimizations; \
        make; \
	make install; \
	cd /app/devtools/thirdparty/include; \
	ln -s python3.8m python3.8;

RUN set -ex; \
       LD_LIBRARY_PATH=/app/devtools/thirdparty/lib /app/devtools/thirdparty/bin/pip3 install virtualenvwrapper;

WORKDIR /app/devtools

# install latest vim
RUN set -ex; \
	\
    git clone https://github.com/vim/vim.git; \
    cd vim; \
    PATH=/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib ./configure --with-features=huge \
    --enable-multibyte \
    --enable-rubyinterp=yes \
    --enable-pythoninterp=yes \
    --enable-python3interp=yes \
    --with-python-command=python \
    --with-python3-command=python3 \
    --enable-perlinterp=yes \
    --enable-luainterp=yes \
    --enable-fail-if-missing \
    --enable-terminal \
    --enable-gui=no --enable-cscope --prefix=/app/devtools/thirdparty; \
    PATH=/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib make && make install;

# install cmake
WORKDIR /app/devtools
RUN set -ex; \
    \
    wget https://github.com/Kitware/CMake/releases/download/v3.16.6/cmake-3.16.6.tar.gz; \
    tar -xvf cmake-3.16.6.tar.gz; \
    cd cmake-3.16.6; \
    ./bootstrap --prefix=/app/devtools/thirdparty -- -DCMAKE_BUILD_TYPE:STRING=Release; \
    make; \
    make install;

# build boost
WORKDIR /app/devtools
RUN set -ex;\
	\
    wget https://dl.bintray.com/boostorg/release/1.72.0/source/boost_1_72_0.tar.gz; \
    tar -xvf boost_1_72_0.tar.gz; \
    cd boost_1_72_0; \
    PATH=/opt/rh/devtoolset-9/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-9/root/usr/lib:/opt/rh/devtoolset-9/root/usr/lib64 ./bootstrap.sh --prefix=/app/devtools/thirdparty --with-python=python3.8; \
    PATH=/opt/rh/devtoolset-9/root/usr/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-9/root/usr/lib:/opt/rh/devtoolset-9/root/usr/lib64 g++ --version; \
    PATH=/opt/rh/devtoolset-9/root/usr/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-9/root/usr/lib:/opt/rh/devtoolset-9/root/usr/lib64 ./b2 -q \
    variant=release \
    architecture=x86 \
    debug-symbols=off \
    threading=multi \
    runtime-link=shared \
    link=shared \
    toolset=gcc \
    --layout=system \
    -d+2 \
    install;

# build protobuf
WORKDIR /app/devtools
RUN set -ex; \
	\
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.11.4/protobuf-all-3.11.4.tar.gz; \
    tar -xvf protobuf-all-3.11.4.tar.gz; \
    cd protobuf-3.11.4; \
    PATH=/opt/rh/devtoolset-9/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-9/root/usr/lib:/opt/rh/devtoolset-9/root/usr/lib64 ./configure --prefix=/app/devtools/thirdparty; \
    make -j2; \
    make check; \
    make install;

USER rajatgirotra
WORKDIR /home/rajatgirotra
RUN /bin/bash -c 'echo "export WORKON_HOME=${HOME}/.virtualenvs" >> ~/.bashrc'
RUN /bin/bash -c 'echo "export PROJECT_HOME=${HOME}/.projects" >> ~/.bashrc'
RUN /bin/bash -c 'echo "export PATH=/app/devtools/thirdparty/bin:\${PATH}" >> ~/.bashrc'
RUN /bin/bash -c 'echo "export LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:\${LD_LIBRARY_PATH}" >> ~/.bashrc'
RUN /bin/bash -c 'echo "export VIRTUALENVWRAPPER_PYTHON=/app/devtools/thirdparty/bin/python3" >> ~/.bashrc'
RUN /bin/bash -c 'echo "source /app/devtools/thirdparty/bin/virtualenvwrapper.sh" >> ~/.bashrc'
RUN /bin/bash -c 'echo "export TERM=xterm-256color" >> ~/.bashrc'
RUN mkdir -p .vim/bundle/

# Add vim plugins
RUN set -ex; \
	\
	cd .vim; \
        git clone https://github.com/kien/ctrlp.vim.git bundle/ctrlp.vim; \
	git clone https://github.com/scrooloose/nerdtree.git bundle/nerdtree.vim; \
        git clone https://github.com/w0rp/ale.git bundle/ale.vim; \
	git clone https://github.com/itchyny/lightline.vim bundle/lightline.vim; \
	git clone https://github.com/tpope/vim-fugitive.git bundle/fugitive.vim;

RUN set -ex;\
	\
	cd /home/rajatgirotra/.vim; \
        git clone https://github.com/Valloric/YouCompleteMe.git bundle/YouCompleteMe.vim; \
	cd bundle/YouCompleteMe.vim; \
        git submodule update --init --recursive; \
	PATH=/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib python3 ./install.py --clang-completer;


WORKDIR /home/rajatgirotra
COPY --chown=rajatgirotra:rajatgirotra requirements.txt requirements.txt

# create virtual environments
RUN set -ex;\
	\
        export PATH=/app/devtools/thirdparty/bin:$PATH; \
        export LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:$LD_LIBRARY_PATH; \
	which python3; \
        which pip3; \
	python3 -m venv $HOME/.virtualenvs/superset; \
	source $HOME/.virtualenvs/superset/bin/activate; \
	pip3 install superset;

RUN set -ex;\
	\
	export PATH=/app/devtools/thirdparty/bin:$PATH; \
        export LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:$LD_LIBRARY_PATH; \
	which python3; \
	which pip3; \
	python3 -m venv $HOME/.virtualenvs/generic; \
	source $HOME/.virtualenvs/generic/bin/activate; \
	pip3 install -r $HOME/requirements.txt;

# install cmake-format
USER devtools
WORKDIR /app/devtools
RUN set -ex;\
	\
        LD_LIBRARY_PATH=/app/devtools/thirdparty/lib /app/devtools/thirdparty/bin/pip3 install cmake-format;

#install ccache
RUN set -ex;\
	\
    wget https://github.com/ccache/ccache/releases/download/v3.7.9/ccache-3.7.9.tar.gz; \
    tar -xvf ccache-3.7.9.tar.gz; \
    cd ccache-3.7.9; \
    ./configure --prefix=/app/devtools/thirdparty && make && make install;

RUN set -ex;\
	\
        LD_LIBRARY_PATH=/app/devtools/thirdparty/lib /app/devtools/thirdparty/bin/pip3 install --upgrade pip  graphviz;

RUN set -ex;\
	\
	wget https://github.com/danmar/cppcheck/archive/1.90.tar.gz; \
        tar -xvf 1.90.tar.gz; \
        cd cppcheck-1.90; \
        g++ -o /app/devtools/thirdparty/bin/cppcheck -std=c++11 -lpcre -DHAVE_RULES -Ilib -Iexternals -Iexternals/simplecpp -Iexternals/tinyxml cli/*.cpp lib/*.cpp externals/simplecpp/simplecpp.cpp externals/tinyxml/*.cpp;

USER rajatgirotra
WORKDIR /home/rajatgirotra
COPY --chown=rajatgirotra:rajatgirotra ycm_extra_conf.py .vim/.ycm_extra_conf.py
COPY --chown=rajatgirotra:rajatgirotra vimrc .vimrc

RUN set -ex;\
	\
	cd; \
	mkdir -p tools; \
	cd tools; \
       curl -o waf https://waf.io/waf-2.0.20; \
	chmod 755 waf; \
        echo "export PATH=/home/rajatgirotra/tools:\${PATH}" >> ~/.bashrc

USER root
RUN set -ex;\
	\
	cp /etc/sudoers /root/sudoers.bak; \
	echo "rajatgirotra ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers;

EXPOSE 22

USER rajatgirotra
WORKDIR /home/rajatgirotra
RUN set -ex;\
     \
     sudo yum -y install devtoolset-9-libtsan-devel devtoolset-9-libasan-devel devtoolset-9-liblsan-devel devtoolset-9-libubsan-devel;

COPY --chown=rajatgirotra:rajatgirotra run_sshd.sh run_sshd.sh
CMD scl enable devtoolset-9 bash;
