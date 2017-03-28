Let us now discuss how Angular JS achieves the two way day binding between the modal and the view.
You know already that Javascript is synchronous. At one time only one line of code is executing.

Separately, Javascript has an event loop. In your Javascript code, you can add event listeners like keyPressed, FocusChanged, DataChanged,
MouseHover, MouseClicked and many more. All these events are processed by the event loop and put in a queue. When javascript finished processing,
it starts looking at events in the event queue and runs the event listeners.

Now AngularJS takes this event loop one step further. What AngularJS does is:

1) It constructs a watchers list which consists of all variables (properties and functions) which are shared between the modal and the view.
   ie. all variables in $scope
2) Next it implements many of the event listeners for you.
3) Then, whenever an event happens, it checks if any of the variables in the watchers list is changed/modified. If yes, it runs a special loop
   called the DIGEST loop. This loop will update the variable in both the view and the modal. Basically, in the watchers list, for each variable an old value
   and new value is maintained. If after the first cycle, there are still variables whose old and new values do not match, it will run another iteration of the digest loop.

This way it makes sure that modal and view are in sync.
There is one caveat. All of this happens inside an angular context, ie if you are usinng angular services ($scope, $timeout etc) type variables.
So if you have any code in plain javascript which modifies $scope, angular will never know that the scope changed, so it will not update the view.

Lets see things in action now.
