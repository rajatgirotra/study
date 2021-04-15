CSS is Cascading Style Sheets. Used to enhance the look and feel of your website.
very trivial.

syntax
=====

selector: {
    property_name_1: property_value_1;
    property_name_2: property_value_2;
}

CSS can be included in three ways:
1) external: you write a css file with .css extension. Then include it in your webpage using <link> element in the <head> element
<head>
    <link rel="stylesheet" href="/path/to/my.css" />
</head>

2) internal: by including all css inside <style> element in the <head> element
<head>
    <style>
        h3 {
           color: red;
	}
	   
    </style>
</head>

3) Inline: using style attribute of an element.
<p style="background-color: lightblue; border: 1px solid red;"> Something </p>

Inline style always takes precedence over internal and external. Also between internal and external, precedence depends on which css is included last. So if <link> element is after <style> element, external css takes precedence. and vice-versa


Selectors
=========

simple selectors
----------------
p { color: red; } --> simple element selector
h3.white_text { background-color: black; } --> applied to all h3 elements which use "white_text" class. Example <h3 class="white_text">/h3>
.class { color: red; } --> class is some css class
#elementId { color: red; } --> applied to elements with a given id attribute.
* { color: red; } --> applied to all elements on page.

h3, h2, p { color: red;} --> applied to all h2, h3, and p elements

combination selectors
---------------------
div p { color: red;}  --> applied to all <p> elements inside a div. whether <p> is direct child or nested deeply.

div > p { color: red;} --> applied when <p> element is an immediate child of <div>

div + p {color: red;} --> applied when a <p> comes immediately after a <div>. ie. <p> is an immediate sibling of <div>

div ~ p {color: red;} --> applied when any <p> comes after a <div>. doesnt necessarily needs to be an immediate sibling of <div>. But <p> must follow <div>, not preced it.
