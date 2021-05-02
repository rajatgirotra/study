Services are just angular classes which can have
1) common code which can be shared across all of your app
2) some common data provider which provides data to your app.

Just thing like a TS class which offers something which can be re-used by other parts of your code.
Also you dont need to use and decorator like @Service (for Service classes), like you need for Component and Decorators

to use service in your components don't go on madly creating service objects anywhere and everywhere in your code.
instead rely on angular to create service objects for your componets. You need to do two things

1) in the @Component decorator, add the "providers" key in the javascript object and the value is the array of services
you need.

2) in the ctor of your component, create those services. example: let say we have a LoggingService which is required
by a MyComponent.

@Component({
selector: ...,
templateUrl: ...,
stylesUrl: [...],
providers: [LoggingService]
})
export class MyComponent implements OnInit {
    constructor(private loggingService: LoggingService) {}

    doWork() {
	loggingService.doLog();
    }
}


Hierarchy
========
the services injected in your components follow a hierarchy.
1) the services at the top-most level (ie the AppModule) level are automatically available to all the components and also services(yes once service can use another service) in your entire-app.
so they are available whole application wide

2) the next level after the AppModule level is the AppComponent level. at this level also all services are available to all the child/descendant components (not to services, only components). what i mean is that the same instance of the service class is available everywhere

3) the next level is the bottom-most Component level which doesnt have any child.

So if we specify:
providers=[LoggingService,DataService]
constructor(private logSvc: LoggingService, private dataSvc: DataService)
, we are telling Angular to create new instances of both LoggingService and DataService.

however if we specify,
providers=[LoggingService]
constructor(private logSvc: LoggingService, private dataSvc: DataService)
, we are telling Angular to create new instances of only the LoggingService. For DataService, get the instance from its parent.

This is often a source of bug in applications, where components use their own private service instances, when they should be using
a common instance.

Also remember if a service needs to use another service, it must be specified in the providers array at the AppModule level i.e in app.module.ts

Also create service TS files like logging.service.ts

Also if you want one service to use another service, use @Injectable() decorator in the service you are injecting.
infact you @Injectable() decorator in all services.

You can also communicate between Components by using Service. How?
------------------------------------------------------------------
your service can create an event emmitter object. example:

statusUpdated = new EventEmitter<string>();

then First component can emit an event and second component can subscribe to it
---------------------------------------------------------------------------------

this.myService.statusUpdated.emit('NEW_STATUS');

this.myService.statusUpdated.subscribe( 
	(status: string) => alert('new status ' + status);
	    
);
---------------------------------------------------------------------------------

in Angular 6+, there is a better way to provide application wide services instead of listing it in providers[] array in AppModule.
The way is that in your service class, use the decorator,

@Injectable({providedIn='root'})
export class MyService {
}

This way Angular can lazily load services only when they are used leading to better performance.
