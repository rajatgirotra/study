#There are n people lined up, and each have a height represented as an integer. A murder has happened right in front of them, and only people who are taller than everyone in front of them are able to see what has happened. How many witnesses are there?
#
#Example:
#Input: [3, 6, 3, 4, 1]  
#Output: 3
#Explanation: Only [6, 4, 1] were able to see in front of them.
# #
# #
# # #
#####
#####
######
#36341   x (murder scene)

# note that murder scene is on the right

def witnesses(heights):
    # we start traversing from reverse as murder scene is on the right
    # the last index will always see the murder scene
    witness = 1
    max_height = heights[-1]
    for i in range(len(heights)-1, -1, -1):
        if heights[i] > max_height:
            max_height = heights[i]
            witness += 1
    return witness 


print (witnesses([3, 6, 3, 4, 1]))

