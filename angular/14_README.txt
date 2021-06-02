ngModules are a way to organize related Components, Directives, Pipes, Services etc together as a single unit.
By default, these entities in a module are only accessible from within the module and not outside unless you export it.
defining an new module required to use the @ngModule directive with the following javascript object keys.

1) declarations -> a list of all Components, Directives, Pipes you use.

2) imports -> a list of other ng modules that you want to use like BrowserModule, HttpClientModule, FormsModule, ReactiveFormsModule, RouterModule.

3) exports -> a list of entities you want to export. When a module imports your module, all entities you define in exports list will be accessible in the module you are importing into

4) bootstrap --> a list (usually with only one Component name) which defines the entry point for your module. The selector for this entry module should be present in the index.html file where angular starts.

5) providers --> a list of services used in your module. You can optionally also use @Injectable({providedIn: 'root'}) syntax which is preferred now.

Note that services are only required to be imported in one module and can be freely used in all other modules of your app.
Also note that BrowserModule (which provides common directives like ngFor, ngIf) can only be imported once in your app module. thereafter other modules can use the CommonModule which also provide these directives.

You can now go ahead and try to divide your main recipe-shopping project into three modules.
1) RecipesModule
2) ShoppingModule
3) AuthModule

-----------------------------------------------------------------------------------------------------------

so we have modified the recipe-shopping project to separate it into many modules
1) RecipesModule
2) ShoppingListModule
3) AuthModule
these are called feature modules. 

4) SharedModule --> to have common components in one module which can be imported into other modules
5) CoreModule --> To have all your services into this module.

But what benefit is separating the source code into multiple modules?? The only benefit is better code structuring. So why did we do it?
it is because it sets the tune for lazy loading of modules which can really improve the performance of your applications.
What is lazy loaded modules?

Normally when you dont separate components in your module and everything is in the main AppModule (inside the declarations list), your web browser client will need to fetch all these components (as bundles) from the server. this can really slow down user experience as you are fetching all modules even though you might not need all of them together. 

so to optimize this you should separate components into separate modules along with the routes of those modules. Then you can put a special property called "loadChildren" in the main root routes in your app-module to tell angular that a module should be lazily loaded, i.e do not download the module bundle unless its used. Once you do this you should also remove the name of the module from the [imports] array in the app-module. Also always make sure you do not import any extra components/services than what is not needed.

There is one more optimization you can do: you can set,
@NgModule({
    imports: [
        RouterModule.forRoot(appRoutes, {preloadingStrategy: 'PreloadAllModules'})
     ]
   })

What this does is that your browser will silently download/fetch all modules from the server in the background while you are still interacting with the website like if you are still entering auth credentials, browser can download recipes and shopping list bundles.
-----------------------------------------------------------------------------------------------------------

Services and Modules
-------------------
Where all can you provide services.
1) in the AppModule itself inside @NgModule( { providers: [MyService] })
   These services are available application wide. You should use this often.

2) in the AppComponent. @Component( {selector: 'app-component', providers: [MyService] })
   These services are available only in the AppComponent component tree. Use it if you have such a use case.

3) Eagerly loaded components: @Component( {selector: 'app-component', providers: [MyService] })
   These services are available application wide. These are similar to providing services in the AppModule itself. DO NOT USE THIS.
   IT CAUSES A LOT OF CONFUSION.

4) lazily loaded components: @Component( {selector: 'app-component', providers: [MyService] })
   A new instance of the service object is created for this component. Use it if you have such a use case.

5) SharedModule: NgModule( { providers: [MyService] })
   For services provided in shared modules, it depends how the SharedModule is available.
   If the sharedModule is imported in an Eagerly loaded component, then the service will be available application wide.
   If the sharedModule is imported in a lazily loaded component, then a new service instance will be available only to that service.
