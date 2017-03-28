import os
import sys
import subprocess as sp
import fnmatch
from os.path import realpath, join, dirname, abspath


def usage():
    print "\nUsage:"
    print ("\tpython " + sys.argv[0] + " <PYTHON_ROOT>")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        usage()
        sys.exit(1)
    PYTHON_ROOT_PATH = sys.argv[1]
    PYTHON_LIB_PATH = realpath(join(PYTHON_ROOT_PATH, 'lib'))
    PYTHON_LIB_NAME = 'libpython'
    # Iterate all shared objects under PYTHON_ROOT
    for root, dirnames, filenames in os.walk(PYTHON_LIB_PATH):
        for fil in fnmatch.filter(filenames, '*.so'):
            # Ignore python library
            if fil not in PYTHON_LIB_NAME:
                # Find if this shared object is linked to libpython2.7
                sopath = join(root, fil)
                cmd = 'ldd ' + sopath
                try:
                    output = sp.check_output(cmd, shell=True,
                                             universal_newlines=True)
                except:
                    continue
                if PYTHON_LIB_NAME not in output:
                    continue
                cnt = 0
                sopath = join(root, fil)
                while dirname(sopath) != PYTHON_ROOT_PATH:
                    cnt += 1
                    sopath = dirname(sopath)
                rpath = '/..' * cnt
                rpath = join(rpath, 'lib')
                rpath = '\$ORIGIN' + rpath
                sopath = join(root, fil)
                
                prp = 'patchelf --print-rpath ' + sopath
                o = sp.check_output(prp, shell=True, universal_newlines=True)
                if len(o.strip()) == 0:
                    o = 'No rpath'
                else:
                    rpath += ":" + o.strip()
                cmd = 'patchelf --force-rpath --set-rpath ' \
                      + rpath + ' ' + abspath(sopath)
                #print (abspath(sopath), cnt, cmd, o)
                sp.check_call(cmd, shell=True)
