#!/bin/bash
#
## First lets make sure we have all dependencies satisfied.
SCRIPT_DIR=`dirname "$0"`
SCRIPT_DIR=`realpath $SCRIPT_DIR`
PYTHON_VERSION=2.7.10
echo "Building Python version: $PYTHON_VERSION"
sudo apt-get install -y -qq zlib1g-dev libssl-dev libbz2-dev libfreetype6-dev libpng12-dev libxft-dev libsqlite3-dev python-dev libldap2-dev libsasl2-dev libssl-dev python-lxml libxml2-dev lib32z1-dev libkrb5-dev realpath libpython2.7-dev libxslt-dev liblapack-dev libreadline-dev libdb-dev libgdbm-dev
#
# Python version to install
BUILD_DIR=$1
if [ -z ${BUILD_DIR} ]
then
    BUILD_DIR=${HOME}/installers/python/${PYTHON_VERSION}
fi

# extract the major and minor version
MAJOR_MINOR_VERSION=`expr "${PYTHON_VERSION}" : '\(...\).*'`
if [ -d ${BUILD_DIR} ]
then
    echo -e "Path ${BUILD_DIR} exists. This will be deleted and a fresh install will be done.. Proceed?? (y/n) \c"
    read choice
    case $choice in
        y|Y) echo 'You acknowledged' ;;
        *) echo 'You did not acknowledge' && exit 1
    esac
fi
rm -rf ${BUILD_DIR}
mkdir -p ${BUILD_DIR} # make sure build directory exists.
#
# download
curl https://www.python.org/ftp/python/${PYTHON_VERSION}/Python-${PYTHON_VERSION}.tgz -so python.tar.gz
# untar
tar -xvzf python.tar.gz
# install
cd Python-${PYTHON_VERSION}
./configure --prefix=${BUILD_DIR} --enable-shared
make -j5
make install

# Patch python executable to set rpath to the correct libPython version
# By default variable $ORIGIN points to the location of the current executable.
patchelf --set-rpath '$ORIGIN/../lib' ${BUILD_DIR}/bin/python${MAJOR_MINOR_VERSION}

# Install pip - Remove this if installing python 3
${BUILD_DIR}/bin/python -m ensurepip --upgrade
# Upgrade pip
${BUILD_DIR}/bin/pip install --upgrade pip


# install elpy and jedi for using python completion in emacs/vim.
${BUILD_DIR}/bin/pip install elpy
${BUILD_DIR}/bin/pip install jedi

# install other packages using PIP
# by default, python downloads packages from PyPI (called the cheeseshop  https://pypi.python.org/simple/)
# But we are going to use the DRW local PyPI mirror in Singapore.
${BUILD_DIR}/bin/pip install Cython==0.23.4
${BUILD_DIR}/bin/pip install pika==0.10.0
${BUILD_DIR}/bin/pip install MarkupSafe==0.23
${BUILD_DIR}/bin/pip install psutil==3.2.2
${BUILD_DIR}/bin/pip install pycrypto==2.6.1
${BUILD_DIR}/bin/pip install python-dateutil==2.4.2
${BUILD_DIR}/bin/pip install pytz==2015.6
${BUILD_DIR}/bin/pip install pyzmq==14.7.0
${BUILD_DIR}/bin/pip install simplejson==3.8.0
${BUILD_DIR}/bin/pip install tornado==4.2.1
${BUILD_DIR}/bin/pip install ujson==1.33
${BUILD_DIR}/bin/pip install python-ldap==2.4.20
${BUILD_DIR}/bin/pip install GitPython==1.0.1
${BUILD_DIR}/bin/pip install bumpversion==0.5.3
${BUILD_DIR}/bin/pip install paramiko==1.15.3
${BUILD_DIR}/bin/pip install wsgiref==0.1.2
${BUILD_DIR}/bin/pip install Fabric==1.10.1
${BUILD_DIR}/bin/pip install numpy==1.10.1
${BUILD_DIR}/bin/pip install scipy==0.16.0
${BUILD_DIR}/bin/pip install matplotlib==1.4.3
${BUILD_DIR}/bin/pip install ipython==4.0.0
${BUILD_DIR}/bin/pip install pandas==0.17.0
${BUILD_DIR}/bin/pip install sympy==0.7.6.1
${BUILD_DIR}/bin/pip install node==0.9.16
${BUILD_DIR}/bin/pip install lxml==3.4.4
${BUILD_DIR}/bin/pip install cpplint
${BUILD_DIR}/bin/pip install jupyter
${BUILD_DIR}/bin/pip install asyncio
${BUILD_DIR}/bin/pip install websockets
${BUILD_DIR}/bin/pip install gevent
${BUILD_DIR}/bin/pip install WTForms
${BUILD_DIR}/bin/pip install flask

## You can refine the libraries above and what you need.
## Backup python
cp -rf $BUILD_DIR backup.$BUILD_DIR
## Then we need to set rpath to point to the libPython library we just installed.
cd ${BUILD_DIR}
for so in `find ${BUILD_DIR}/ -name "*.so"`
do
    soRealPath=`realpath $so`
    soRelPath=${soRealPath#${BUILD_DIR}/}
    echo $soRelPath | grep -qi libpython 2> /dev/null
    rc=$?
    if [ $rc -eq 0 ]
    then
        continue
    fi
    number_of_occurrences=$(grep -oi '/' <<< "$soRelPath" | wc -l )
    rpath=
    while [ ${number_of_occurrences} -ne 0 ]
    do
        rpath="../${rpath}"
        number_of_occurrences=`expr $number_of_occurrences - 1`
    done
    rpath='$ORIGIN/'${rpath}lib
    patchelf --set-rpath "${rpath}" "$soRelPath"
done

mkdir -p ${HOME}/installers/dist/
cp -v ${SCRIPT_DIR}/install.sh ${HOME}/installers/dist/
cp -v ${SCRIPT_DIR}/fix_interpreter_line.py ${HOME}/installers/dist/
$tar cvzf python.tar.gz .
mv python.tar.gz ${HOME}/installers/dist
makeself ${HOME}/installers/dist rajat_python.run "" ./install.sh

# After everything is done, we need to run python.run and have the install script install it in tools/python also actiavte the python environment
${BUILD_DIR}/rajat_python.run
echo "source ${HOME}/tools/python/bin/activate" >> ~/.bashrc
