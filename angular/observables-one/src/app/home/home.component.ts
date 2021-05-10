import {Component, OnDestroy, OnInit} from '@angular/core';
import {interval, Observable, Subscription} from 'rxjs';
import {filter, map} from 'rxjs/operators';

@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit, OnDestroy {

  intervalSubscription: Subscription;
  constructor() { }

  ngOnInit(): void {
    /**
     * Observables are provided using an external library rxjs. Observables that TS provides using rxjs like
     * 1) this.route.params() etc are also unsubscribed by angular on your behalf. But if you write your own obervables
     * you must unsubscribe() yourself in ngOnDestroy() otherwise there will be a resource leak.
     * Here we use a very simple observable in rxjs called interval which just emits an incremental integer after a specified time interval
     * and we use that to show why it is important to call unsubscribe().
     */

    // this.intervalSubscription = interval(1000).subscribe((value) => {
    //   console.log(value);
    // });

    /**
     * writing a custom i.e your own Observable is alo trivial. We use the Observable.create() method. The create needs to be passed a
     * function as an argument. This function takes one parameter which is set by rxjs module. Its the "observer" or the listener which is
     * interested in getting events from your observable. Now the Observable must do three things.
     * 1) Either inform of an event using observer.next(event)
     * 2) Or inform of any error using observer.error()
     * 3) Or inform that all events are done using observer.complete(). Lets now create a customObservable.
     */
     const customObservable = Observable.create((observer) => {
       let count = 0;
       setInterval(() => {
         observer.next(count);
         ++count;
         /**
          * throw error if count > 4
          */
         // if (count > 4) {
         //   observer.error(new Error('count is greater than 4!'));
         // }
         /**
          * stop and complete observable after count reaches 5
          */
         if (count >= 5) {
           observer.complete();
         }
       }, 1000);
     });

     /**
      * subscribe function also takes 3 arguments.
      * 1) function taking argument as returned by Observable (function called when observer.next() is called.
      * 2) function taking error argument as returned by Observable (function called when observer.error() is called)
      * 3) function taking no argument. (function called when observer.complete()) is called.
      */
     // this.intervalSubscription = customObservable.subscribe(count => {
     //   console.log(count);
     // }, error =>  { // (error) => {} and error => {} is same
     //   alert(error);
     // }, () => {
     //   console.log('completed!');
     // });


     this.intervalSubscription = customObservable.pipe(filter(count => {
      return count > 0; // returns a boolean and we ignore the first event
    }), map((count: number) => {
      return 'Round ' + (count + 1);
    })).subscribe(count => {
      console.log(count);
    }, error =>  { // (error) => {} and error => {} is same
      alert(error);
    }, () => {
      console.log('completed!');
    });

  }

  ngOnDestroy(): void {
    if  (this.intervalSubscription) {
      this.intervalSubscription.unsubscribe();
    }
  }
}

/**
 * rxjs Operators:
 * Many times you dont have control over observables. You can only subscribe to them and any manipulation/filtering must be done by yourself
 * in side the subscribe method. However rxjs provides many operators as you will see above. These operators can map, filter and do many
 * things to the event emitted, so that the events reach your subscribe method in the way you want.
 * To use operators, you have to use the pipe() method of the observable. this method takes a series of operators. each operator takes a
 * function with argument as the event published by the observable.
 * Here we use two operators, filter and map. filter will filter out the first event and map will just prefix some random string.
 *
 * Subjects
 * Subjects are also Observables. However there is one difference from Observables. Subjects are active and Observables are passive.
 * What this means is that When you create an Observable, you need an observer also on which you call next(), error(), complete() etc.
 * However for Subject observable, you can call next() on the Subject observable itself.
 *
 * Normally Subject observable is always a good choice compared to EventEmitter and also the use of Subject is just like EventEmitter.
 * The only difference is that for Subject you call next() to emit and event and for EventEmitter you call emit().
 * Now in recipes-shopping project, find all EventEmitters and convert them to Subjects.
 */
