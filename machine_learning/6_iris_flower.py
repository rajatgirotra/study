# sklearn provides a bunch of data sets and easy utilities to load those data sets
from sklearn.datasets import load_iris
from sklearn import tree
import numpy as np

iris = load_iris()

# the dataset includes the actual data from Wikipedia + some metadata
print(iris.feature_names)
print(iris.target_names)

# data is contained in the data array
print(iris.data[0])  # prints the first row of feature values

print('data type is %s with dimensions %s' % (type(iris.data), iris.data.shape))
print('target type is %s with dimensions %s' % (type(iris.target), iris.target.shape))

print(iris.target)  # prints the labels ndarray

# What we'll do now is remove a few rows from the training data and use these rows as our testing data
# Testing is a VERY VERY IMPORTANT PART OF ML.
test_idx = [0, 50, 100]

# training data
train_target = np.delete(iris.target, test_idx)
train_data = np.delete(iris.data, test_idx, axis=0)

# testing data
test_target = iris.target[test_idx]
test_data = iris.data[test_idx]

# You should already know by now how to create a DecisionTreeClassifier and train it.
clf = tree.DecisionTreeClassifier()
clf = clf.fit(train_data, train_target)

# Now lets print our actual test targets and the predicted test targets
print('Actual test targets %s' % test_target)
print('Predicted targets %s' % clf.predict(test_data))
# They should match

# Remember the DecisionTreeClasifier is like an inverted tree. Every node in the tree asks some question
# about the features and based on the feature value, goes either to the left or right node. So the better the
# features are, the better will be the predictions. We'll see later how to write good features.

# sklearn also provides a way to look at the decision tree created by the training data using many graph libraries
# like graphviz, pydot, matplotlib etc.
# lets see the iris decision tree.
from sklearn.externals.six import StringIO
import pydotplus

dot_data = StringIO()
tree.export_graphviz(clf, out_file=dot_data, feature_names=iris.feature_names,
                     class_names=iris.target_names, filled=True, rounded=True, impurity=False)
graph = pydotplus.graph_from_dot_data(dot_data.getvalue())
print(type(graph))
graph.write_pdf('iris.pdf')  # isnt working at the moment. Try later.
