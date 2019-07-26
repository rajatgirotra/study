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
       	PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib ./bootstrap.sh; \
        PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib ./configure --prefix=/app/devtools/thirdparty; \
        make; \
        make install

# install sqlite3
RUN set -ex; \
	\
	wget https://sqlite.org/2019/sqlite-autoconf-3280000.tar.gz; \
      	tar xvf sqlite-autoconf-3280000.tar.gz; \
	cd sqlite-autoconf-3280000; \
       	PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib ./configure --prefix=/app/devtools/thirdparty --enable-readline; \
        make; \
        make install

# install python 3.7
RUN set -ex; \
	\
	wget https://www.python.org/ftp/python/3.7.3/Python-3.7.3.tar.xz; \
       	tar xvf Python-3.7.3.tar.xz && cd Python-3.7.3; \
        PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib ./configure --prefix=/app/devtools/thirdparty --enable-shared --with-ensurepip=upgrade --enable-optimizations; \
        PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib make; \
	PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib make install; \
	cd /app/devtools/thirdparty/include; \
	ln -s python3.7m python3.7;

RUN set -ex; \
       LD_LIBRARY_PATH=/app/devtools/thirdparty/lib /app/devtools/thirdparty/bin/pip3 install virtualenvwrapper;

WORKDIR /app/devtools

# install latest vim
RUN set -ex; \
	\
    git clone https://github.com/vim/vim.git; \
    cd vim; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib ./configure --with-features=huge \
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
    PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib make && make install;

# install cmake
WORKDIR /app/devtools
RUN set -ex; \
    \
    wget https://github.com/Kitware/CMake/releases/download/v3.14.5/cmake-3.14.5.tar.gz; \
    tar -xvf cmake-3.14.5.tar.gz; \
    cd cmake-3.14.5; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib ./bootstrap --prefix=/app/devtools/thirdparty -- -DCMAKE_BUILD_TYPE:STRING=Release; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib make; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib make install;

# build boost
WORKDIR /app/devtools
RUN set -ex;\
	\
    wget https://dl.bintray.com/boostorg/release/1.68.0/source/boost_1_68_0.tar.gz; \
    tar -xvf boost_1_68_0.tar.gz; \
    cd boost_1_68_0; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64 ./bootstrap.sh --prefix=/app/devtools/thirdparty --with-python=python3.7; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64 g++ --version; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64 ./b2 -q \
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
    wget https://github.com/protocolbuffers/protobuf/releases/download/v3.8.0/protobuf-all-3.8.0.tar.gz; \
    tar -xvf protobuf-all-3.8.0.tar.gz; \
    cd protobuf-3.8.0; \
    PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/app/devtools/thirdparty/lib:/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64 ./configure --prefix=/app/devtools/thirdparty; \
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
	PATH=/opt/rh/devtoolset-8/root/usr/bin:/app/devtools/thirdparty/bin:$PATH LD_LIBRARY_PATH=/opt/rh/devtoolset-8/root/usr/lib:/opt/rh/devtoolset-8/root/usr/lib64:/app/devtools/thirdparty/lib python3 ./install.py --clang-completer;


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

WORKDIR /home/rajatgirotra
COPY --chown=rajatgirotra:rajatgirotra ycm_extra_conf.py .vim/.ycm_extra_conf.py
COPY --chown=rajatgirotra:rajatgirotra vimrc .vimrc

RUN set -ex;\
	\
	cd; \
	mkdir -p tools; \
	cd tools; \
        curl -o waf https://waf.io/waf-2.0.18; \
	chmod 755 waf; \
        echo "export PATH=/home/rajatgirotra/tools:\${PATH}" >> ~/.bashrc

WORKDIR /home/rajatgirotra
CMD scl enable devtoolset-8 bash;
