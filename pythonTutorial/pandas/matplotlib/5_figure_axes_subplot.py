# Matplotlib has a concept of figures and subplots (axes). A figure is basically your drawing canvas (an object of type matplotlib.figure.Figure). A figure can have multiple subplots.

# What is a subplot. A subplot is a matplotlib class "matplotlib.axes._subplots.AxesSubplot" which derives from the Axes class "matplotlib.axes.Axes". Almost of the plotting functions work the subplot/axes objects.

# What is the difference between subplot and axes. Every subplot is an axes, but every axes is not a subplot; because subplot derives from Axes. A subplot basically has a X and Y axis and it's position in the figure is defined by a "rect" argument of type list [left, bottom, width, height]. When you add a subplot to a figure, matplotlib determines the position by itself. However, it is also possible to place an axes manually in a figure using the axes() command. All arguments in "rect" are between 0 and 1.

# There are just so many different ways to create figures/subplots/axes, that can easily confuse you. I'll try to go slowly over few of these.

import matplotlib.pyplot as plt

######################################################################################################################
# plt.figure(num=None, facecolor, edgecolor, other args...) 
# figures are numbered in matplotlib. If num is None(the default), a new Figure object is created and the figure number is incremented by one
# Calling figure() also make it the active figure.
# if num is an int, a lookup is performed to find a Figure object with that number (Figure has a number attribute). If not found, a new Figure is created.
# num can also be a "string", i.e. a figure label and you can lookup later using the figure name which is more intiutive.
# Also use plt.close(f) -> f is the Figure object to free up resources held by this object.
# the figure/subplot.axes objects have a number of set_* and get_* methods for setting/getting various parameters.

f = plt.figure()
print('1st Figure %s with number %s' % (f, f.number))
f.set_label("1stFigure")

f = plt.figure()
print('2nd Figure %s with number %s' % (f, f.number))
f.set_label("2ndFigure")

f = plt.figure("Profits")  # "Profits" is the label
print('3rd Figure %s with number %s and label %s' % (f, f.number, f.get_label()))

# lookup figure
print('figure(1) %s' % plt.figure(1).get_label())
print('figure(profits) %s' % plt.figure("Profits").number)

######################################################################################################################
# once you have the figure object, you can add a set of subplots using the figure.subplots() method

f = plt.figure("Profits")
#[[ax1, ax2],[ax3, ax4]] = f.subplots(nrows=2, ncols=2, sharex=False, sharey=False)  # can specify more args too, lookup online doc
# update matplotlib if the above command doesn't work. 
# under the hood, subplots() calls figure.add_subplot() to create each subplot.
# figure.add_subplot(i, j, k) is very trivial. It means add ith plot on the grid with j rows and k cols.

######################################################################################################################
# the best approach is to use plt.subplots() which automatically creates the figure and subplots() for you. This is preferred
# instead of creating figure object and calling its add_subplot() or subplots() method.
f, [[ax1, ax2],[ax3, ax4]] = plt.subplots(nrows=2, ncols=2, sharex=False, sharey=False)  
print('\nusing plt.subplots() %s %s' % (f, f.number))
print('using plt.subplots() ax1 type %s\n' % type(ax1))
######################################################################################################################

# plt.plot() command automatically creates a figure and a subplot(111). 111 means 1 row, 1 col and 1st subplot.
# Also the subplot(111) becomes active so the plt commands will now work on the first subplot.
# i would still recommend using the above approach of using plt.subplots()

######################################################################################################################
# using plt.subplot() --> this will automatically create a figure with 2 rows, 1 col and make the 1st subplot active.
plt.subplot(2, 1, 1)
plt.plot(2, 3, marker='D', markersize=12)
######################################################################################################################
# manually add axes using plt.axes() or Figure.add_axes() --> return matplotlib.axes.Axes instances.
# rect = l, b, w, h
# plt.add_axes(rect, **kwargs) --> kwargs are the kwargs that can be passed to Axes c'tor like projection, frameon,
# facecolor etc.
# plt.axes(rect, **kwargs) 
# Remember that a lot of api's have kwargs, and you should think yourself what the kwargs could be. 
# if you are adding some text to a figure using some text api, then kwargs could be the args that can be passed to Text c'tor

# CAVEAT: plt.axes(ax1) --> makes ax1 the current axes and the figure of ax1 the current figure. and return ax1


######################################################################################################################
# A note on plt.show() --> plt.show() hows all the figures and then blocks (if non-interactive mode, like running a python script)
# or not block (if interactive mode like ipython). Each figure will also has the figure label which we have set/get before
plt.show()
######################################################################################################################

# close all figures
plt.close('all')
