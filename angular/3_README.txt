how angular starts up.

You already know that angular are single page applications. When we create a new project using "ng new", an index.html is created which has an <pp-root> element. This is the html that gets loaded in the browser.

Then how to do we see something else at localhost:4200.

ok: when a new project is created, angular cli creates a component for you called the app component. this component ties all other components together. this is the root or parent component to which we later add/nest our other components.

now when "ng serve" rebuilds our process, it injects a bunch of javascript files in the index.html file and those scripts are then executed which call the "main.ts" file in the src folder. "main.ts" is where the angular process really starts. in "main.ts", we have a statement.

platformBrowserDynamic().bootstrapModule(AppModule);

this tells angular to look into the app.module.ts file in the src/app component and look at the "bootstrap" expression there.
in app.module.ts we have:

import { AppComponent } from './app.component';
bootstrap: [AppComponent]
this tells angular that the only component we are interested to load up are the app.component.ts file. Angular then looks at the app.component.ts file and find a selector "app-root". when it finds it, angular sees this selector is same as the "app-root" tag in my index.html, so it copies the app.component.html file there and all of that file is then visible in the browser. 
