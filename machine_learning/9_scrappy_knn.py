# K-Nearest Neighbours (KNN) is also a classifier. Very trivial, for test data, it computes the distance between the
# test data and training data. It then calculates which training data is closest and uses the label of the closest
# training data as the output. Here we are going to override the KNN classifier with our own classifier. You will need
# to override the "fit()" and "predict()" functions.

from sklearn.neighbors.classification import KNeighborsClassifier
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics.classification import accuracy_score
import random
from scipy.spatial import distance


def euc(a, b):
    return distance.euclidean(a, b)

# K is always 1 in our ScrappyKNN
if __name__ == '__main__':
    class ScrappyKNN(object):
        def fit(self, X_train, y_train):
            self.X_train = X_train
            self.y_train = y_train
            return self
            # Make it learn now

        def predict(self, X_test):
            # We need to calculate the distance between the train and test data
            # We will use the euclidean distance formula : square root of (x2-x1) square + (y2-y1) square
            # You know this from pythagoras theorem.
            scrappy_predictions = []
            for row in X_test:
                # label = random.choice(y_train)  # random prediction
                label = self.closest(row)
                scrappy_predictions.append(label)
            return scrappy_predictions

        def closest(self, row):
            best_dist = euc(row, self.X_train[0])
            best_index = 0
            for i in range(1, len(self.X_train)):
                dist = euc(row, self.X_train[i])
                if dist < best_dist:
                    best_dist = dist
                    best_index = i
            return self.y_train[best_index]


iris = load_iris()
X = iris.data
y = iris.target

X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=0.7)

# clf = KNeighborsClassifier()
clf = ScrappyKNN()

clf = clf.fit(X_train, y_train)

predictions = clf.predict(X_test)

print('Accuracy score %s' % accuracy_score(y_test, predictions))


# The K in the KNN is used when two or more training data are the same distance from the test data. So in this case, you
# can randomly break the tie, or you find the distance between the second farthest training data and test data. So if
# your training data has red and green dots and a test dot is the same distance away from a red and green dot, and K is
# 2, then you find how far is the second green and red dot. Whichever is closer, is choosen the winner.

# Pros
# this algorithm is very simple and works well in some cases
# Cons
# CPU intensive, slow as you need to go through the whole training data
# It just works on distance and cannot give more weight to one feature over the other.
