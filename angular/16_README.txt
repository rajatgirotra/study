RXJS obeservables and operators
===============================

Its a very trivial concept. You have three entities
1) Observables
2) Observer
3) Subscription


observable is just an object which can emit a stream of data values. it also emit an error or indicate that there is nothing more to emit.

An observer is a js object which has three attributes:
{
next: function(value) { console.log(value); }
error: function(error) { console.log(error); }
complete: function(void) { }
}


every observer must "next", "error" and "complete" attributes whose values are functions. The contract is that observables will call:
- next() -> to emit a value
- error() -> to indicate an error in the observable. The observable is assumed to be finished and no more values can be emitted after error() is called.
- complete() -> to indicate that all values have been emitted.


a subscription is a js object returned when calling "observable.subscribe()". in the subscribe() function we can pass the observer object or also pass the next, error and complete function callbacks. Just think of Subscription object as holding a resource which must be disposed by calling unsubscribe().

You can also add multiple other subscriptions to a subscription object by calling subscription.add(anotherSubscription). This way when you unsubscribe() the parent, all the nested subscriptions will also be unsubscribed. the functions available on subscriptions object are therefore:
subscribe(), unsubscribe(), add(), remove()

operators
========
operators provided by RXJS are of two types:
1) Pipeable -->  these are functions which take some config options and they return a new function. the new function returned by the operator takes a source observable and returns a new observable. when this returned function is called by passing the source observable, it subscribes to it, and applies the config options and returns a new observable. To understand better, lets take an example:

const nums = of(1, 2, 3); // of is an RXJS operator that returns an Observable. so type(nums) = Observable.

const squareValues = map((val: number) => val * val); // map is a pipeable operator that takes a config option which is a function to square a value.

// sample implementation of map could be
Observable (*)(sourceObservable) map(configOption) { 
    const f = Observable function(SourceObservable) {
        newObservable = new Observable();
        sourceObservable.subscribe({
            "next": (val: number) {
                const result = mapFuction(val); // applying the config option
                newObservable.next(result);
            }, 
            "error": (err) => {
                 newObservable.error(err);
             },
            "complete": () => {
                 newObservable.complete();
             }
        }
        return newObservable;
    }
    return f;
}
therefore typeof(squaredValues) = Observable function(SourceObservable);

const squaredNums = squaredValues(nums); // calling the function in map which returns newObservable.

squaredNums.subsribe(x => console.log(x)); //prints 1, 4, 9

Similarly pipe() is an operator allows you to pipe() multiple operators() in sequence.


