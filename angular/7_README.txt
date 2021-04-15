you have already seen the .css file in your components. Now Angular GUARANTEES that whatever styles you define in your own component only applies to your component.
How?? What angular does is that it generates a unique attribute for your component and applies that attribute to all elements in your component. Then in your css also, it overrides all styles to apply those styles only for that unique attribute.

example: you have in you app.component.html a <p> and <h1> tag. Angular will generate a unique identifier example _ngcontent-ejo-0 and make the elements in HTML like

<p _ngcontent-ejo-0> and <h1 _ngcontent-ejo-0>

and if you define css like:

p { color: red; } it will change it to

p _ngcontent-ejo-0 { color: red; }

so only your elements in your component are effected.

Most often this is the desired behavior, but you can override this using "encapsulation: ViewEncapsulation.None" in your @Component() decorator.
