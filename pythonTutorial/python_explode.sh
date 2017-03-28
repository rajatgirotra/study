#!/bin/bash

INSTALL_PATH=${1}
[[ $# -ne 1 ]] && read -p "Install to [${HOME}/python]: " INSTALL_PATH
: ${INSTALL_PATH:=${HOME}/python}

if [[ ! -d ${INSTALL_PATH} ]]
then
    mkdir -p ${INSTALL_PATH} 2> /dev/null
    rc=$?
    [[ ${rc} -ne 0 ]] && echo "Could not create directory ${INSTALL_PATH}. Please check permissions." && exit 1
else
    [[ $(ls ${INSTALL_PATH}) != "" ]] && echo "Directory ${INSTALL_PATH} is not empty." && exit 1
fi

echo "Installing to ${INSTALL_PATH}"
tar -xvzf python.tar.gz --directory ${INSTALL_PATH}

${INSTALL_PATH}/bin/python ./fix_shebang.py
