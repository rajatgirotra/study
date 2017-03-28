Conda is a package manager. It is written in python.
Alternative to fig which you used in DRW.

Conda is python agnostic. You can build and install anything not just python modules.
Conda is not available separately and you must install Anaconda or Miniconda

Anaconda - Includes Python with about 150+ packages for scientific computing with python
Miniconda - Just python and conda.

I installed miniconda under /home/rgirotra/tools/miniconda2.


Tab Completion
=============
conda supports tab completion. For this you have to:
1) Install a conda package "argcomplete" : conda install argcomplete
2) add eval $(register-python-argcomplete conda) to your bash profile.
