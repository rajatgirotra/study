The most important stuff.
Building conda packages

Here we'll see how to build a conda package and host on Anaconda, or any public or private repository.

There are two things you can do:
1) Build a package which is already hosted on let say pypi and you want to create a new release with a new version number.
2) Build a package from scratch.

Lets look at 1) first
We already have a package in pypi called pyinstrument which some kind of python profiler. Let say we want to make some fixes
and release a new version.

Step 1
=======
On Windows:
conda install unxutils
conda install conda-build

On Linux:
conda install conda-build

Step 2
======
Use conda skeleton command to create template files used for creating a python package to be hosted on PyPi

conda skeleton pypi pyinstrument --> Tell conda to create skeleton files for creating a conda package pyinstrument. The skeleton files should be produced for pypi package hosting.
If you run this command in your home directory, a pyinstrument directory is created with three files

meta.yaml ---> all metadata like package name, version, dependencies etc.
build.sh --> for unix
bld.bat --> for windows

conda will search look at meta.yaml and look at the dependecnies of pyinstrument and download all dependencies needed to build it. This can take some time.
Then you can make changes and say:

conda build pyinstrument --> which will create a tar.bz2 automatically for you in the conda-build directory. The conda-build directory is configurable in your .condarc file.
/home/rajatgirotra/conda-builds/linux-64/pyinstrument-0.13.1-py27_0.tar.bz2 was created by me.

You can then install it locally using
conda install --use-local pyinstrument --> --use-local means use locally built packages. So it installs the locally built pyinstrument-0.13.1-py27_0.tar.bz2 (which is in the conda build directory)

You can now convert this python package into python packages for other platforms You can specify --platform as osx-64, linux-32, linux-64, win-32 or win-64, all
conda convert --platform all /home/rajatgirotra/conda-builds/linux-64/pyinstrument-0.13.1-py27_0.tar.bz2 -o outputdir/

Obviously you cannot do this for gcc builds which are unix specific.
If you want to upload your package to anaconda, you do the following

1) Create an account on Anaconda.org (formerly binstart.org)
2) Install anaconda-client : "conda install anaconda-client"
3) login : "anaconda login"
4) upload: "anaconda upload /home/rajatgirotra/conda-builds/linux-64/pyinstrument-0.13.1-py27_0.tar.bz2"
5) logout: "anaconda logout"


Building from scratch
=====================

This is no different, except that you have to create skeleton files yourself.
Have a look at this link http://conda.pydata.org/docs/building/bpp.html which tells how to write the skeleton files.
The skeleton files are together called a conda-recipe.
https://github.com/conda/conda-recipes.git contains conda-recipes for a lot of softwares.
We can always tailor them for our purpose.
