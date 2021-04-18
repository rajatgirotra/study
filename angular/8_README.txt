Angular lifecycle and other hooks. hooks are just method's called by angular when certain events occur.
like constructor/destructor etc.

ngOnChanges
-----------
called whenever a new component is created or when an input property changes (properties decorated with @Input)

ngOnInit
---------
called when your TS object is initialized. i.e after the constructor has executed. You can safely access object properties here.
your object isn't part of the DOM yet.

ngDoCheck
---------
run by angular whenever the Angular change detection system runs. This event is called very frequently. Angular runs this mostly on many events to check if a change in the template needs to be made and then refreshes the DOM accordingly. Even when nothing needs to be changed, ngDoCheck will still run.

ngAfterContentInit
-------------------
called after content (ng-content) has been projected into the view.

ngAfterContentChecked
----------------------
called after the (ng-content) has been checked.

ngAfterViewInit
---------------
called after the component's view (and child views) has been initialized.

ngAfterViewChecked
---------------
called after the component's view (and child views) has been checked.

ngOnDestroy
-----------
called before destructor (when object is being destroyed).
