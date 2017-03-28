Conda Commands
=============

conda --version

conda info is a very useful command too.

conda update conda --> update conda

Creating/Removing Conda Environment
==========================

conda create --help --> for many options available
conda create --name <env_name> <package_spec>
Will create a new environment in conda_install_dir/envs/ and make the packages available in that environment.
You can optionally specify a package file also instead of specifying packages on the command line.
package_spec is a space delimited string of package1=version1 package2=version2 etc.


conda info --envs  --> display conda environments available
conda list --> list the packages available in the current environment. By default a new conda installation will have an environment called "root"

conda remove --name <env_name> -all  --> To remove a conda environment

conda create --name flowers --clone snowflakes --> cloning an environment

Switching environments
======================
source activate <env_name>
source deactivate

activate/deactivate scripts are in conda_install_dir/bin/


Searching packages
=================

conda search <package_name>  --> Search the channels for package with package_name
conda search --full-name <package_name> --> Search where name matches exactly.


Installing/Removing packages
==================

conda install <package_name> OR
conda install --name <env_name> <package_name> --> Install package_name in <env_name> environment.
conda install --channel https://conda.anaconda.org/pandas bottleneck --> Install bottleneck from anaconda if it is not available in the defaults channels.
conda remove --name <env_name> <package_name>/-all --> Can give a package name or --all to remove the environment completely.


Exporting an environment
=========================
There are multiple ways of doing this:

One
===
You can share your environment with someone else by creating a .yml file for the environment. You need to do two things
1) Activate the environment you wish to export
2) conda env export > environment.yml or
   conda env export -f environment.yml or
   conda env export --name <env_name> -f environment.yml (to export env_name)
   
Then mail or share the environment.yml file with your friend. who can create a similar environment using
conda env create -f environment.yml  OR
conda env create -f environment.yml  --force (to force create the env even if it already exists) OR 
conda env create (by default if -f is missing environment.yml is searched) OR
conda env create -n <env_name> (to create the environment using environment.yml but a different env_name).

This command only stores package names and version, NOT the source channel where the package was installed
from.

Two
===
Create a spec-file which lists all the conda and pip packages installed in your environment
1) conda list -e > spec_file.txt
2) conda create --name <new_evn_name> --file spec_file.txt

Three
=====
Sometimes, using Two, you can end up downloading packages from another source because your .condarc channels are different from that of your friend.
To handle these odd cases, you can include the channel info also in the spec-file.txt so that when conda creates an environment, it uses the channels
in the spec-file.
1) conda list --explicit > explicit_spec_file.txt
2) conda create --name <new_env_name> --file explicit_spec_file.txt
Note that the channel URLs in explicit_spec_file has are different for different architectures, so this method will only work if the two conda installations
are on the same os and architecture. Otherwise you option One or Two.


Update Packages
===============
Very simple

conda update <package_name>
