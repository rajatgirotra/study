#!/bin/bash

set -e

SCRIPTS_DIR=$(readlink -f $(dirname ${BASH_SOURCE[0]}))
echo "SCRIPTS_DIR=${SCRIPTS_DIR}"

MD5SUM="9de6494314ea199e3633211696735f65"
PYTHON_VERSION=3.6.4
URL="https://www.python.org/ftp/python/${PYTHON_VERSION}/Python-${PYTHON_VERSION}.tgz"
INSTALL_ROOT=/home/rajatgirotra/tools/python/${PYTHON_VERSION}

# download python source
echo "Downloading python source from ${URL}.."
curl --silent --url ${URL} --output Python-${PYTHON_VERSION}.tgz
echo "Done."

# valid checksum
echo "Verifying checksum."
[[ $(md5sum Python-${PYTHON_VERSION}.tgz | awk '{print $1}') != ${MD5SUM} ]] && (echo "Checksum failed. Downloaded python file is likely corrupt"; exit 1)

# remove current installation folder
rm -rf Python-${PYTHON_VERSION} 2>/dev/null
# untar source
echo "Extracting source."
tar -xzf Python-${PYTHON_VERSION}.tgz

#export LDFLAGS="-Wl,-rpath,\\\$\$ORIGIN/../lib"
rm -rf ${INSTALL_ROOT}
mkdir -p ${INSTALL_ROOT}
cd Python-${PYTHON_VERSION}

echo "Running configure"
./configure --enable-shared --enable-ipv6 --prefix=${INSTALL_ROOT} --enable-unicode=ucs4 --with-ensurepip=yes >/dev/null 2>/dev/null
echo "Compiling source"
make > /dev/null 2>/dev/null
echo "Creating install"
make install > /dev/null 2>/dev/null
cd -

PYTHON=${INSTALL_ROOT}/bin/python3
PIP=${INSTALL_ROOT}/bin/pip3

# Fix rpath for python executable
echo "Patching RPATHS.."
cd ${INSTALL_ROOT}/bin
for fil in $(ls)
do
    if file $fil | grep -q "ELF.*executable"
    then
        echo $fil
        patchelf --force-rpath --set-rpath '$ORIGIN/../lib' $fil
    fi
done
cd -

# install/upgarde packages.
echo "Upgrading PIP and Installing additional packages.."
${PIP} --quiet install --upgrade pip
${PIP} --quiet install virtualenv
${PIP} --quiet install -r ${SCRIPTS_DIR}/requirements.txt
#${PIP} --quiet install --egg scons==2.4.1
echo "Done."

# Fix rpath for all shared objects
echo "Patching RPATHS.."
${PYTHON} ${SCRIPTS_DIR}/fix_rpath.py ${INSTALL_ROOT}
echo "Done."

# package all up using makeself.
#echo "Creating python package.."
#TEMP_DIR=$(mktemp -d)
#cp python_explode.sh fix_shebang.py ${TEMP_DIR}
#chmod 755 ${TEMP_DIR}/{python_explode.sh,fix_shebang.py}
#PYTHON_DIRS=$(cd ${INSTALL_ROOT} && ls)
#tar -pczf ${TEMP_DIR}/python.tar.gz --directory ${INSTALL_ROOT} ${PYTHON_DIRS}
#makeself ${TEMP_DIR} gce_python.run "Python ${PYTHON_VERSION}" ./python_explode.sh
#rm -rf ${TEMP_DIR} 2> /dev/null
#echo "Done."


# [[ $(ls) != "" ]] && echo "folder \"$(ls)\" is not empty. Please choose an empty folder."; 
# makeself --gzip 2.7.12 gce_python.run.gz gce_python echo "Installing python"
