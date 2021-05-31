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
