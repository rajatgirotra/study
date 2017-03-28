#!/usr/bin/env python3

## I have not yet set the matplotlib support setup in plain old python interactive shell.
## So Dont run the commands here in a normal shell. Please use ipython shell.

import matplotlib as mpl
#import matplotlib.pyplot as plt

# the plot(*args, **kwargs) is in the matplotlib.pyplot module which is the set of matplotlib interface classes for creating plots

plt.plot(5)
# With just one argument, it assumes it is a value on y-axis and corresponding value on x-axiz is 0.
# Also be default, plot shows plot in blue color with dashed lines ie 'b-', since here we are just plotting a point
# instead of lines, nothing will be visible as there is no line. So instead of lines we need to use markers. You can
# check online - matplotlib supports many different types of markers. So you can say
plt.plot(5,'rD') # plot (0,5) in red color and Diamond shape marker


plt.plot(5, 2, 'g^') # Here plot point (5,2) with green triangle shaped marker

plt.plot(2.5,'mo', 3.5, 'rD', 4.5, 'g<', 5.5, 'b.') # plot these four points in majenta, red, green and blue colors
# Also o means circular marker, D is diamond shaped, < is triangle_left marker, . is point marker

plt.plot([1,2,3,4],[0.5,1.5,2.5,3.5],'b+-') # x values are 1,2,3,4 and y values are 0.5,1.5,2.5,3.5,
# color is blue, style is plus marker and line, so you'll see plus markers at the 4 points.


plt.plot([1,2,3],[1,2,3], 'go-', label='line 1', linewidth=2) # Using keyword args, you can set parameters on lines
# like label and linewidth
plt.plot([1,2,3],[1,4,9], 'rs', label='line 2')
plt.axis([0,5,0,10]) # settig the minimum and max x and y axis
plt.legend() ## Will display the legend about the two lines in the plot itself.
## All these keywords like label, linewidth are actually properties of matplotlib.lines.Line2D
# Have a look online on how many different types of properties are supported.


##later you'll see how plot command works not only with scalars or simple lists, but also with numpy ndarray
# Infact lists are internally converted to ndarray only.




