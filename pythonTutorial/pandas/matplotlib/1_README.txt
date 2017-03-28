matplotlib is a 2D plotting library.

matplotlib is basically made of three parts

1) The first is the interface.. ie the set of classes and objects you use to create plots (import matplotlib.pyplot as plt) for this.
2) The frontend - this is a collection of classes which do all the heavy weight lifting of storing plot information like,
   line lengths, color, axis labels, plot details etc. It is completely abstract and unaware of the actual drawing details.
3) The backend is plot rendering devices which are device specific. EG: we have Agg for using with ipython notebook.
   Many other backend types are available.

When matplotlib library is imported, it reads a config file. This config file can be at three locations
1) Project specific : in the current working directory; called matplotlibrc
2) User specific :  in .config/matplotlib/matplotlibrc
3) Installation specific for everyone: INSTALL_DIR/matplotlib/mpl-data/matplotlibrc

Use the following function to find out which matplotlibrc is read

'import matplotlib as mpl'
print(mpl.matplotlib_fname())

All these config settings are called rc settings in matplotlib and is nothing but a dictionary type. So in python script, you
can always refer to it as

print(mpl.rcParams)

You can also edit rc setting directly by modifiying rcParams
mpl.rcParams['lines.linewidth'] = 2
mpl.rcParams['lines.color'] = 'r'

matplotlib also provides a convenience function to set properties belonging to the same group; like lines here
mpl.set('lines', linewidth=2, color='r')

Use matplotlib.rcDefaults() to restore the default rc settings.

Best is that you work with matplotlib in ipython shell.
in ipython shell, do

[In]: %matplotlib inline
[In]: import matplotlib as mpl  # this contains the frontend classes
[In]: import matplotlib.pyplot as plt  # this contains the interface for plotting.

Next lets look at various plot functions in matplotlib
