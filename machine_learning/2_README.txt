Classifier: What is it??
A classifier is nothing but a function that takes some data as input and assigns it some label as output. Like
1) An image is an Apple (label is apple here)
2) This mail is Spam (label is spam here)

The technique to write the classifier automatically is called supervised learning. You expose your algorithm to examples of the problem you are trying to solve (learning by example). We'll use scikit-learn to code this up.

pip install scikit-learn 
import sklearn

For supervised learning (ie learning by example), we need to do the following religously:

1) Collect training data (ie data-sets of what we want to teach our algorithm).
2) Then we feed our data to the classifier (ie the function).
3) The classifier then makes prediction based on the input data set.

So a classifier is essentially made of two things:
1) an empty box of rules.
2) an algorithm to create rules based on patterns in the training data.
