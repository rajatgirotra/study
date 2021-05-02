import {Component, OnDestroy, OnInit} from '@angular/core';
import {ActivatedRoute, Params, Router} from '@angular/router';
import {Subscription} from 'rxjs'; // rxjs is 3rd party Observable library which Angular uses.

@Component({
  selector: 'app-user',
  templateUrl: './user.component.html',
  styleUrls: ['./user.component.css']
})
export class UserComponent implements OnInit, OnDestroy {
  user: {id: number, name: string};
  paramsSubscription: Subscription;
  /**
   * ActivatedRoute is a javascript object.
   * @param router
   * @param activatedRoute
   */
  constructor(private router: Router, private route: ActivatedRoute) { }

  ngOnInit(): void {
    /**
     * this.route.snapshot.params will give you the params of this route when it is loaded for the first
     * time. However once the UserComponent is loaded and let's say we click a link on the UserComponent page which has different params
     * than the snapshot params, we wont know about it as angular will not destroy and re-create the UserComponent (for performance reasons)
     * So in those cases we use Observables. Observables are things that you can subscribe to and take action when an Observable changes.
     * this.route.params is such an observable, so we subscribe to it in ngOnInit()
     */
    this.user = {
      id: this.route.snapshot.params.id,
      name: this.route.snapshot.params.name
    };
    // console.log('ngOnInit this.user ' + this.user.id, this.user.name);

    // must store subscription and destroy using ngOnDestroy
    this.paramsSubscription = this.route.params.subscribe(
        (params: Params) => {
          this.user.id = params.id;
          this.user.name = params.name;
        }
    );
  }

  ngOnDestroy(): void {
    this.paramsSubscription.unsubscribe();
  }
}
