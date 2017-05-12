# The first command is the plot() function This function is used to draw lines/markers on your figure.. It is very generic.
# plot(*args, *kwargs) --> *args can be multiple combinations of x/y coordinates and line style and color. Example plot([1,2,3], [1,2,3], 'b-', 5, 6, 'rD') ie draw a line with coordinates (1,1), (2,2), (3,3) in blue color with '-' marker and draw a point (5,6) in red diamond shape marker. 
# plot (y), plot(y, 'r+') --> When x coordinates are missing, assume that they grow from 0..N-1.
# plot([1,2,3], [1,2,3], 5, 6) --> line style/color is optional in which case a different style/color is given by matplotlib depending on the rc setting (see axes.prop_cycle) rcParam

# plt.show() will show your plot in matplotlib.
# plot() returns a list of matplotlib.lines.Line2D objects corresponding to each line drawn. The kwargs is used to set properties on these line objects. whatever set_* functions are available in Line2D class can be set using kwargs. Notible properties are:
# 1. linewidth
# 2. label
# 3. antialiased --> What is it. By default is On. When you see a higher resolution plot on devices with lower resolution we can get distortion effects. aliasing removes these distortions. Just note that antialiased=False will produce quicker plots. Try plt.plot(range(10), antialiased=True/False) and see the difference.
# 4. color, linestyle, marker, markersize, markerfacecolor
# Another good example:
# plt.plot(2, 3, color='green', linestyle='dashed', marker='D', markerfacecolor='orange', markersize=12)  --> This will draw only a single Diamond shape orange marker at (2,3)
# plt.plot([1,2], [3,4], color='green', linestyle='dashed', marker='D', markerfacecolor='orange', markersize=12)  --> This will draw only a line with co-ordinates (1,3) (2,4) in green color dashed line with Diamond shape orange markers at both co-ordinates.

# Matplotlib is designed to work with numpy arrays. We can use that also to plot. Infact lists are internally converted to numpy arrays.
import numpy as np
t = np.arange(0,5,0.2) # produce an ndarray from 0 to 5 with step of 0.2
plt.plot(t,t, t, t**2, t, t**3) # draw three lines x = x, x = x*x, x = x*x*x
plt.show()


