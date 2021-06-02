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
