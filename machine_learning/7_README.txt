Features are an essential part in supervised learning. How to decide which features are good. Lets say we want some features to
distinguish between two breeds of dogs: Labrador and GreyHounds.

1) Greyhounds are generally taller than labs --> So height might be a good feature, but it wont always be correct.
There will be Labradors who are taller than greyhounds.
2) Lets say these two breeds can only have blue and brown eyes --> This feature is useless as there is a 50% chance that
a dog with blue eyes is a lab or greyhound. We could have simply write an if statement and dont need a classifier.
AVOID USELESS FEATURES AS THEY MIGHT ADVERSELY IMPACT YOUR CLASSIFIER PREDICTIONS.
3) Avoid highly correlated features, like height in inches and height in cms -> Only one is enough. Ie the more independent
the features are, the better it is.
4) Avoid complex features, Features should be simple. Lets say you want to find how much time it takes to send a letter
better two cities. Obviously a good feature would be the distance b/w the two cities. A bad feature would be the longitude and latitude of the
two cities, as its very difficult to derive a good prediction using this feature.