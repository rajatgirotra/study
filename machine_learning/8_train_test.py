# I cannot stress more on the importance of train and test in ML. Training data is used to adjust your classifier so that
# it can make accurate predictions. Test data is indispensable as it tells how predictable your classifier really is.
# Train and test go hand in hand. scikit-learn provides many helper api's to divide all your data in training data and
# testing data automatically and also provides functions to report the percentage accuracy of your classifier.

# Also we'll see that there are multiple classifiers that we can use. The interface is just the same for all classifiers
# so it's easy to switch a classifier anytime. We'll continue to use the IRIS flower data set.

from sklearn.datasets import load_iris
from sklearn import tree
from sklearn.model_selection import train_test_split
from sklearn.metrics.classification import accuracy_score
from sklearn.neighbors.classification import KNeighborsClassifier

iris = load_iris()
X = iris.data
y = iris.target
# We call our features (iris.data) as X and our labels (iris.target) as y. This is because a classifier can be thought
# of as a function f(X) = y

# divide the iris data into training data and test data.
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=0.5)  # i.e. split iris dataset into 50% each

# Now create our classifier, just a one line change is needed to change your classifier function.
# clf = tree.DecisionTreeClassifier()
clf = KNeighborsClassifier()

clf = clf.fit(X_train, y_train)

predictions = clf.predict(X_test)  # predict output for X_test data.

# Now sklearn provides API to give % accuracy of your classifier.
print(accuracy_score(y_test, predictions))
# Note that every time, the accuracy score will be different depending on the train and test data split.
