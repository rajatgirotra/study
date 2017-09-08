from sklearn import tree

# training data, features will be input to the classifier and labels are the output
# features = [[140, "smooth"], [130, "smooth"], [150, "bumpy"], [170, "bumpy"]]
# labels = ["apple", "apple", "orange", "orange"]

# let's replace each of the string features and labels with numbers
# scikit-learn uses real-values feature. We'll explore later what this exactly means
# "smooth" is 1, "bumpy" is 0
features = [[140, 1], [130, 1], [150, 0], [170, 0]]
# "apple" is 0, "orange" is 1
labels = [0, 0, 1, 1]

# There are many types of classifier functions, we use a decision tree here.
# A decision tree classifier is like a box of rules. Let's create an empty box of rules first
clf = tree.DecisionTreeClassifier()

# Now we have an empty box of rules. We now need a learning algorithm. A learning algorithm is the thing
# that will create the rules. Note, you are not creating rules by yourself. The learning algorithm will create
# for you by looking at patterns in your training data. In scikit-learn, this algorithm is included in the
# classifier object and its called "fit"
clf = clf.fit(features, labels)  # fit means find patterns in data.
# We'll see later how the classifier is trained by the training data.

print('%s' % clf.predict([[160, 0]]))  # the training data seems to suggest that oranges usually weigh higher
# which is correct, note that [160, 0] is a new type of fruit which is not in the data set.
