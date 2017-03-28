import os
import sys
import argparse
import glob
import shutil

if __name__ == "__main__":
    # Create argparser
    parser = argparse.ArgumentParser(description="Patch shebang in new python installation")
    parser.add_argument("--scripts-dir", default=os.path.dirname(sys.executable),
                       help="Directory where python scripts to be patched are located");

    args = parser.parse_args()

    SCRIPTS_DIR = args.scripts_dir
    SHEBANG = '#!' + os.path.join(args.scripts_dir, os.path.basename(sys.executable)) + '\n'

    for f in glob.glob(SCRIPTS_DIR + '/*'):
        if open(f).read(2) != '#!':
            continue
        tmp_f = f + '.tmp'
        mode = os.stat(f)[0]
        with open(tmp_f, 'w') as fp:
            for line in open(f):
                if(line[:2]) == '#!':
                    line = SHEBANG
                fp.write(line)

        shutil.move(tmp_f, f)
        os.chmod(f, mode)
