Deploying angular apps
---------------------

trivial way to deploy angular app is to copy your complete project folder over to the prouction host and run "ng serve" there. However that approach has problems.
1) the size of the node_modules folder is huge. that's where all your dependencies are saved.
2) even if you omit node_modules and copy others, still the size of some of the javascript dependencies is much larger than it should be.

So the correct way to prepare a deployment pack is to use
"ng build --prod"

but what does "ng build --prod" do?? It does a number of steps to fully optimize and prepare your deployment package
1) minification.
this is where all your javascript files are reduced in size, mainly by removing comments and removing spaces.

2) uglification
this is where some of the long names (like variable names and functions names) are replaced with very short identifiers. example:
export class HomeComponent { void onClick() {}} becomes export class HC { void oC() {}}

3) bundling
bundling means combining one or more javascript together into a larger javascript file. this helps the client browser as it has to send fewer requests to the server to download all javascript files and ultimately your angular app becomes more responsive as the client now needs to make less http requests.

4) dead code elimination
this is where you remove classes/files which are not used or referenced so we dont want to bring them in our production package.

5) Ahead of time (AOT) compilation
This is game changer as it significantly improves performance, but what is it really?

"ng build --prod" does all the above for you.

JIT(Just in time) vs AOT compilation

JIT compilation
---------------
in Angular framework you have a compiler(called ngc, it will be in node_modules/.bin/ngc). This compiler is strange because the angular compiler takes javascript code and produces javascript code only. So what does it do really? Well JIT reads all of the components files like template files, css files, typescript files and converts it to equivalent javascript.
Example:
<div style="text-align:center;">
   <h1>
     Welcome to {{ title }}
   </h1>
   <img width="300" src="/path/to/image.png" />
</div>
will be converted by angular compiler to something like

var div = document.createElement('div');
var h1 = document.createElement('h1');
div.appendChild(h1);


AOT compilation
--------------
Now this JIT compiler will compile all your code at run-time for all your clients in production. and its the same output that the JIT compiler will produce each time. That is very wasteful. instead, we can do this once during package preparation time and then we dont need the angular compiler (ngc) anymore during deployment. and that saves a lot of time and disk space both. If we dont do AOT, we need to ship ngc shipped with our bundles (angular compiler is part of a vendor bundle). Also with AOT compilation, we catch errors early at compilation phase only. Also we get better security as there is less opportunity for injection attacks.

You can run "ngc" under node_modules/.bin/ngc and see the output. there will be many extra classes created for css, template and your typescript classes.

ng build --prod
---------------
ng build command creates a dist folder where for each typescript file we have a two files produced
1) a javascript file
2) a map file (used for debugging. It can map the produced javascript back to your typescript code when you have to debug something)

environments
------------
you angular app has an environments folder which has an environment.ts and environment.prod.ts files. This is where you can configure the environment for your prod and dev instances. Like for prod instances.
1) you can have different navbar color to indicate its prod
2) you can change the name of the navbar-brand to add a "PROD" suffix etc etc.
