# plt.axis() is a convenience function for setting both x and y axis together. 
# for individually setting an axis, use ylim or xlim

# plt.axis() will return you a list [xmin, xmax, ymin, ymax]
# plt.axis([xmin, xmax, ymin, ymax]) will set the axis
# plt.axis('off')
# plt.axis('tight') 
# plt.axis('equal') ie, both axis will be scaled equally.

# xmin, xmax = xlim() # if called without any argument
# xlim(xmin, xmax) or xlim((xmin, xmax)) # ie give as a tuple
# xlim(xmax=3) # leave xmin unchanged
# xlim(xmin=1) # leave xmax unchanged.

# ylim() is similar
