#-*- coding: utf-8 -*-

# you can add text at various places using matplotlib; like
# 1. The label on x/y axis
# 2. Setting the subplot title
# 3. Setting the figure title
# 4. Putting text at arbitrary location in the plot/figure
# 5. Annotating text - meaning showing an arrow to some location in the plot and putting the text along side the arrow
# 6. Writing text with special symbols like mu, sigma etc.

# Some of the functions available for text are:
#  plt.xlabel() --> add a label to x-axis --> calls matplotlib.axes.Axes.set_xlabel()
#  plt.ylabel() --> add a label to y-axis --> calls matplotlib.axes.Axes.set_ylabel()
#  plt.title() --> add a subplot title --> calls matplotlib.axes.Axes.set_title()
#  plt.suptitle() --> add a figure title --> calls matplotlib.figure.Figure.suptitle()
#  plt.text() --> add text to arbitrary location on the subplot --> calls matplotlib.axes.Axes.text()
#  plt.figtext() --> add text to arbitrary location on the figure --> calls matplotlib.figure.Figure.text()
#  plt.annotate --> annotate text --> calls matplotlib.axes.Axes.annotate()

# All the above functions return matplotlib.text.Text instance, which can be further configured using the set_* methods.

# Lets see it in action. Ignore the call to creation of histogram, we'll understand that later.

import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

np.random.seed(21051983)

mu, sigma = 100, 15
x = mu + sigma * np.random.randn(10000)

# create histogram
n, bins, patches = plt.hist(x, 50, normed=1, facecolor='g', alpha=0.75)

# CONCENTRATE HERE
plt.xlabel('Smarts')
plt.ylabel('Probability')
plt.title('Histogram of IQ')
plt.text(60, 0.025, r'$\mu=100,\ \sigma=15$', color='red', fontsize=20)  # special symbols are written like this called TeX format. r means raw string so dont interpret backslashes as escape sequences.
plt.text(120, 0.02, u'unicode: \0930', color='magenta', fontweight='bold')  # special symbols are written like this called TeX format. r means raw string so dont interpret backslashes as escape sequences.
plt.axis([40, 160, 0, 0.03])  # [xmin, xmax, ymin, ymax]
plt.grid(True)  # draw grid lines
plt.show()

# Obviously you can pass kwargs to the above text manipulation calls where kwargs are same as that for matplotlib.text.Text c'tor.

