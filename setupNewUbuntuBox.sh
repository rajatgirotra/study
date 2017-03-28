#!/bin/bash
# Make installers and tools directory
echo "Making installers and tools directories"
sudo mkdir -p "${HOME}/installers"
sudo mkdir -p "${HOME}/tools"

#sudo apt-get update

# Install vim
#(echo "Fetching & Installing vim " && sudo apt-get install -y -qq vim) || (echo "Vim installation failed" && exit 1)

# Install curl
#(echo "Fetching & Installing curl " && sudo apt-get install -y -qq curl) || (echo "curl installation failed" && exit 1)

# Install perf
#(echo "Fetching & Installing Perf Profiler " && sudo apt-get install -y -qq linux-tools-common linux-tools-3.19.0-30-generic) || (echo "Perf installation failed" && exit 1)

# Install lzip
#(echo "Fetching & Installing lzip " && sudo apt-get install -y -qq lzip) || (echo "lzip installation failed" && exit 1)

# Install subversion and git
#(echo "Fetching & Installing subversion and git " && sudo apt-get install -y -qq git subversion) || (echo "subversion and git installation failed" && exit 1)

# Install makeself and patchelf
#(echo "Fetching & Installing makeself " && sudo apt-get install -y -qq makeself) || (echo "makeself installation failed" && exit 1)

# Install build essential
#(echo "Fetching & Installing linux-headers-$(uname -r) build-essential " && sudo apt-get install -y -qq linux-headers-$(uname -r) build-essential) || (echo "build-essential installation failed" && exit 1)

# Install libc6 32 bit headers
#(echo "Fetching & Installing libc6 32 bit headers " && sudo apt-get install -y -qq libc6-dev-i386 libc6-dev-x32) || (echo "libc6-dev-i386 installation failed" && exit 1)

# Install m4
#(echo "Fetching & Installing m4 " && sudo apt-get install -y -qq m4) || (echo "m4 installation failed" && exit 1)

#mkdir -p ${HOME}/.tmp/
#cd ${HOME}/.tmp
#curl -O http://nixos.org/releases/patchelf/patchelf-0.8/patchelf-0.8.tar.gz
#(echo "Installing patchelf" && tar xvzf patchelf-0.8.tar.gz && cd patchelf-0.8 && sudo ./configure && sudo make && sudo make install) || (echo "Patchelf installation failed" && exit 1)
#sudo rm -rf patchelf*



# Install gcc
#export GCC_VERSION=5.2.0
#export GMP_VERSION=6.0.0a
#export GMP_DIR=6.0.0
#export MPFR_VERSION=3.1.3
#export MPC_VERSION=1.0.3
#cd ${HOME}/installers
#curl -O http://ftp.tsukuba.wide.ad.jp/software/gcc/releases/gcc-${GCC_VERSION}/gcc-${GCC_VERSION}.tar.gz
#curl -O https://gmplib.org/download/gmp/gmp-${GMP_VERSION}.tar.gz
#curl -O http://www.mpfr.org/mpfr-current/mpfr-${MPFR_VERSION}.tar.bz2
#curl -O ftp://ftp.gnu.org/gnu/mpc/mpc-${MPC_VERSION}.tar.gz

#mkdir -p "${HOME}/tools/gcc/${GCC_VERSION}"
#mkdir -p "${HOME}/tools/gmp/${GMP_VERSION}"
#mkdir -p "${HOME}/tools/mpfr/${MPFR_VERSION}"
#mkdir -p "${HOME}/tools/mpc/${MPC_VERSION}"

# unpackage all these libraries
#tar  xvf gcc-${GCC_VERSION}.tar.gz
#tar  xvf gmp-${GMP_VERSION}.tar.bz2
#tar  xvf mpfr-${MPFR_VERSION}.tar.bz2
#tar  xvf mpc-${MPC_VERSION}.tar.gz

# GMP First
#cd gmp-$GMP_DIR
#chmod +x configure
#./configure --prefix=${HOME}/tools/gmp/${GMP_VERSION}
#make
#make install
#cd -
#rm -rf gmp-$GMP_DIR


# MPFR
#cd mpfr-$MPFR_VERSION
#chmod +x configure
#./configure --prefix=${HOME}/tools/mpfr/${MPFR_VERSION} --with-gmp=${HOME}/tools/gmp/${GMP_VERSION}
#make
#make install
#cd -
#rm -rf  mpfr-$MPFR_VERSION

# MPC
#cd mpc-$MPC_VERSION
#chmod +x configure
#./configure --prefix=${HOME}/tools/mpc/${MPC_VERSION} --with-gmp=${HOME}/tools/gmp/${GMP_VERSION} --with-mpfr=${HOME}/tools/mpfr/${MPFR_VERSION}
#make
#make install
#cd -
#rm -rf  mpc-$MPC_VERSION

# Gcc Now
#cd gcc-${GCC_VERSION}
#chmod +x configure
# Note fortran is required later for numpy python installation
#./configure --prefix=${HOME}/tools/gcc/${GCC_VERSION} --with-gmp=${HOME}/tools/gmp/${GMP_VERSION} --with-mpfr=${HOME}/tools/mpfr/${MPFR_VERSION} --with-mpc=${HOME}/tools/mpc/${MPC_VERSION} --enable-shared --enable-multiarch --enable-multilib-list=m32,m64,mx32 --enable-languages=c,c++,fortran --enable-lto
#make -j4 bootstrap-lean
#make check-gcc
#make check-c
#make check-c++
#make install
#cd -

# checkout rajatgirotra repository from subversion
#cd ${HOME}
#svn checkout https://rajatgirotra.unfuddle.com/svn/rajatgirotra_practice/ --username rajatgirotra --password '$NewDay2'

# Setup git bash completion and git prompt and PS1
#curl -o .git-completion.bash  https://raw.githubusercontent.com/git/git/master/contrib/completion/git-completion.bash
#curl -o .git-prompt.sh https://raw.githubusercontent.com/git/git/master/contrib/completion/git-prompt.sh

#touch ~/.bashrc
#echo 'source ~/.git-completion.bash' >> ~/.bashrc
#echo 'source ~/.git-prompt.sh' >> ~/.bashrc
#cat rajatgirotra_practice/trunk/ps1.txt >> ~/.bashrc
#echo "export PATH=${HOME}/tools/gcc/${GCC_VERSION}/bin:$PATH" >> ~/.bashrc

# Download emacs and .emacs.d from git hub
#cd ${HOME}
#git clone https://github.com/rajatgirotra/emacs.git .emacs.d
#git config --global user.name "Rajat Girotra"
#git config --global user.email rajatgirotra@yahoo.com
#git config --global core.editor emacs
#git config --global core.status auto
#git config --global core.branch auto
#git config --global core.diff auto
#git config --global core.interactive auto
#cd installers
#EMACS_VERSION=24.5
#mkdir -p ${HOME}/tools/emacs/${EMACS_VERSION}
#curl -O http://mirror.rise.ph/gnu/emacs/emacs-${EMACS_VERSION}.tar.xz
#tar xvf emacs-${EMACS_VERSION}.tar.xz
#cd emacs-${EMACS_VERSION}
#chmod +x configure
# Need to install jpeg, tiff , xpm, gif etc packages for emacs
#sudo apt-get install -y -qq libjpeg-dev libgif-dev libtiff4-dev libtiff5-dev libpng12-dev libxpm-dev libx11-dev texinfo libncurses-dev libgtk2.0-dev
#./configure --prefix=${HOME}/tools/emacs/${EMACS_VERSION}
#make
#make install
#echo "export PATH=${HOME}/tools/emacs/${EMACS_VERSION}/bin:$PATH" >> ~/.bashrc

# Download and install googlemock and googletest
#cd ${HOME}/installers
#git clone https://github.com/google/googletest.git
#export GTEST_DIR=${HOME}/installers/googletest/googletest
#export GMOCK_DIR=${HOME}/installers/googletest/googlemock
#g++ -pthread -isystem ${GTEST_DIR}/include -I ${GTEST_DIR} -isystem ${GMOCK_DIR}/include -I ${GMOCK_DIR} -c ${GTEST_DIR}/src/gtest-all.cc
#g++ -pthread -isystem ${GTEST_DIR}/include -I ${GTEST_DIR} -isystem ${GMOCK_DIR}/include -I ${GMOCK_DIR} -c ${GMOCK_DIR}/src/gmock-all.cc
#ar -rv libgmock.a gtest-all.o  gmock-all.o
#mkdir -p ${HOME}/tools/google_testing_framework/{include,lib}
#mv -v libgmock.a ${HOME}/tools/google_testing_framework/lib/
#cp -rf ${GTEST_DIR}/include/gtest ${HOME}/tools/google_testing_framework/include/
#cp -rf ${GMOCK_DIR}/include/gmock ${HOME}/tools/google_testing_framework/include/
#rm -rf gtest-all.o gmock-all.o googletest




# Download an install GNU global for ggtags
#cd ${HOME}/installers
#GLOBAL_VERSION=6.5.1
#curl -O http://tamacom.com/global/global-${GLOBAL_VERSION}.tar.gz
#tar xvf global-${GLOBAL_VERSION}.tar.gz
#cd global-${GLOBAL_VERSION}
#chmod +x configure
#mkdir -p ${HOME}/tools/global/${GLOBAL_VERSION}
#./configure --prefix=${HOME}/tools/global/${GLOBAL_VERSION}
#make
#make install
#cd -
#rm -rf global-${GLOBAL_VERSION}
#echo "export PATH=${HOME}/tools/global/${GLOBAL_VERSION}/bin:$PATH" >> ~/.bashrc

# Setup Python
./pythonTutorial/preparePython.sh

# Download and install Boost
#BOOST_VERSION=1.59.0
#cd ${HOME}/installers/
#wget -c "http://sourceforge.net/projects/boost/files/boost/${BOOST_VERSION}/boost_1_59_0.tar.bz2/download"
#mv download download.tar.bz2
#tar xvf download.tar.bz2
#cd boost_1_59_0
#mkdir -p ${HOME}/tools/boost/${BOOST_VERSION}
#./bootstrap.sh --prefix=${HOME}/tools/boost/${BOOST_VERSION} --with-python=${HOME}/tools/python/bin/python
#./b2 install toolset=gcc cxxflags="-std=c++11"

#Download and install nodejs
#NODEJS_VERSION=4.2.1
#cd ${HOME}/installers/
#curl -O https://nodejs.org/dist/v4.2.1/node-v4.2.1.tar.gz
#tar xvf node-v${NODEJS_VERSION}.tar.gz
#cd node-v${NODEJS_VERSION}
#mkdir -p ${HOME}/tools/nodejs/${NODEJS_VERSION}
#./configure --prefix=${HOME}/tools/nodejs/${NODEJS_VERSION}
#make
#make install
#echo "export PATH=${HOME}/tools/nodejs/4.2.1/bin:${PATH}" >> ~/.bashrc

# ZeroMQ Installation
#ZMQ_VERSION=4.1.3
#cd ${HOME}/installers/
#curl -O http://download.zeromq.org/zeromq-${ZMQ_VERSION}.tar.gz
#tar xvf zeromq-${ZMQ_VERSION}.tar.gz

# Dependency of libsodium
