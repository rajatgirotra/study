#!/bin/bash

DIST_NAME=python.tar.gz
INSTALL_TO=${HOME}/tools/python

if [ -d ${INSTALL_TO} ]
then
 rm -rf ${INSTALL_TO}
fi

echo "Installing python in ${INSTALL_TO}"

mkdir -p ${INSTALL_TO}
tar xvzf ${DIST_NAME} -C ${INSTALL_TO}

${INSTALL_TO}/bin/python fix_interpreter_line.py

cat << EOF > ${INSTALL_TO}/bin/activate

_OLD_PATH=\$PATH
_OLD_PS1=\$PS1
_OLD_PYTHON_PATH=\$PYTHONPATH

export PATH=${INSTALL_TO}/bin:\$PATH
export VIRTUAL_ENV=${INTALL_TO}
export PYTHONPATH=${INTALL_TO}/pymodules:\$PYTHONPATH

PS1="\n(venv)"\$PS1

function deactivate() {
    export PATH=\${_OLD_PATH}
    export PS1=\${_OLD_PS1}
    export PYTHONPATH=\${_OLD_PYTHON_PATH}
    unset VIRTUAL_ENV
    unset -f deactivate
}

EOF

chmod a+x ${INSTALL_TO}/bin/activate
