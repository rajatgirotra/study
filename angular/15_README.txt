ngRX

ngRX is an angular module which is used to manage application state.
you will need to use ngRX only when your application grows big. otherwise most of the time the use of "localStorage", and use of "EventEmitter" and "Subject" will be enough.

ngRX is based on Redux. We can use Redux also with angular (there is no restriction that redux can only be used with react), but ngRX is preferred as it is deeply integrated with angular and supports rxjs operators etc.


What is Redux
-------------
Redux basically is a design pattern to manage application state. in redux we have an application state which is the single source of truth. think of it as a large javascript object.

application state can be read directly from this appliation store.

for making a change to the application state, you dispatch something called as Actions. Actions are nothing but javascript objects which have an id and an optional payload. the "id" identifies the kind of action and the payload which maybe needed to perform the action.

these actions dont go to the application state directly. these actions infact reach something called as reducers. reducers are javascript functions which take as input the current state (a copy of the current state is given to the reducers) and also the action. they then change the copy of the state to the desired state and that state is written back to the application store.

There is also an chrome browser extension available called "Redux devtools". you can install it. To use it, you need to
1) intsall @ngrx/store-devtools npm package using "sudo npm install --save-dev @ngrx/store-devtools"
2) add StoreDevToosModule to app-module
   StoreDevToosModule.instrument({
                          maxAge: 25, // Retains last 25 states
                          logOnly: environment.production, // Restrict extension to log-only mode                    
                         })
3) start "ng serve" and in chrome developer tools select "Redux" in application tab.

There is also another ngrx npm package called @ngrx/router-store. Install it using "npm install --save @ngrx/router-store" and inject it into the app-module using "StoreRouterConnectingModule.forRoot()".
What this module does is that dispatches a lot of actions related to routing along with the payload so all you have to do is act on these actions in your reducer if you are interested. You can also view all the actions in the redux chrome extension.
