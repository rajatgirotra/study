you write angular code in components. infact
src/app is a component. a component in angular will have

1) a template file which is the app.component.html here.
2) a corresponding CSS file which is app.component.css here
3) a type script file which is a scripting language which is converted to javascript later - app.component.ts file where.

If you see app.component.ts file you will see code like:

export class AppComponent {
    title = 'my-first-app';
}

Also you see the name 'my-first-app' in the localhost:4200 page. So looks like title in html is being picked up from this ts file. this is called dynamic data binding which we will study next. try to change "title" in app.component.ts and see the change in browser.

Also if you view/inspect source code in browser. you will see just a bunch of javascript imports in the bottom of the page and you will see a new html element <app-root></app-root> near the bottom of the page.

<body>
  <app-root></app-root>
<script src="runtime.js" defer></script><script src="polyfills.js" defer></script><script src="vendor.js" defer></script><script src="main.js" defer></script></body>
</html>

so what does it mean. If you see src/index.html, you will realize that this is the file actually loaded at localhost:4200.
this file has <app-root></app-root> element defined. So angular will look at all its components (in the src folder) and see the type script file there (like src/app/app.component.ts file) and check the Component selector in that file. if the component selector is "app-root" that component will be loaded.
so angular injects the component dynamically at run time and as part of that the javascripts are added dynamically at the bottom of the page.

angular directives
==================
angular works with directives. also angular itself has many modules in which these directives are defined. So if you want to use a directive, make sure you import the correct angular module for that directive. the imports are defined in app.module.ts

we will now modify the localhost:4200 file (app.component.html) to just add an <input> element and a paragraph element <p> and use the ngModel directive to create a two way binding. Any change in input will also change the paragraph.

Once you finish that revert all your changes so we can be ready for the next project


Typescript
=========
Typescript is just a superset of javascript. It provides more features than javascript like
1) strict types
2) classes
3) interfaces etc
4) decorators (like in python)
but eventually the TypeScript is converted to javascript by the CLI itself, so everything you see in browser is just javascript.

Importing Bootstrap
==================
we want to import bootstrap version 3 and use it in our project. For that we need to install/download bootstrap css and save it in node_modules.
we can do that using npm. 

npm install --save bootstrap@3

once saved, you can edit angular.json file in your project (angular.json is the project wide config). in this file add the path to the bootstrap css under "styles" in the json. then verify by loading localhost:4200 again and go to developer tools->Elements->"link rel style.css" and see if bootstrap is listed there.


class objects and javascript and TS are references. that it means, if you copy, you are copying a reference so both variables still
point to the same underlying object.
