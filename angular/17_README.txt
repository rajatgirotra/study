Angular Universal
=================

Angular univeral allows you to pre-render pages so that they are available as soon as they are loaded in the browser. What does that mean actually?
If you right click and "View Page Source" of an angular app, you will only see <app-root> and a bunch of javascript files (which is your compiled, optimized and packaged angular app).
The javascript in your code needs to run and prepare your page(convert to HTML and DOM) before its rendered. This is called rendering. If there is no rendering, then <app-root> doesnt really mean anything in HTML.

Also search engines like google etc view the page source only, and for angular app's they wont see anything except <app-root>. so your website will not get a good index score.
If your page on the other hand was pre-rendered (ie all HTML and DOM was pre-prepared), it would load faster in the browser and also give a good index score. pre-rendering is also
very important for slower connections, where js files take too long to download and really nothing can happen until they are fully downloaded.
