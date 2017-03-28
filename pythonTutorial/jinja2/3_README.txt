You can have different types of templates in jinja2
The default configuration has the following:

{% ... %} - This is a statement delimiter. You can have some control flow here like if/else, for loops, macros etc.
Whatever this evaulates to is not rendered anywhere. It basically to say that these are jinja statements

{{ ... }} - This is an expression which can contain variables etc. and whatever we have will be rendered in the output.

{# ... #} - this is a comment and jinja will ignore this.

# ... ## - these are line comments which we will see later.

When you say something like
{{ foo.bar }}
{{ foo[bar] }} - bar is called an attribute of foo. and it is upto the application to pass foo which has
a bar attribute. Jijna first tries to access bar attribute in foo object passes to it. If unsuccessful, it
will try to access bar using the subscript operator ([]). Note that any python class which implements
__getitem__ can be used in python to access the subscript operator (like list)
If this also fails, it will return an undefined object.

You can modify variables using filters. Very simple just suffix filters after variable name using pipe character. So
{{ name|striptags|title }}.. applies two filters on name variable title(striptags(name))
{{ listx|join(', ') }} .. filters can also have arguments. This will be called like join(', ', listx)
See the various built-in filters.

Besides this, jijna also provides a number of tests that you can use to verify variables. use the 'is' directive for that
inside statement blocks
{% if loop.index is divisibleby 3 %}
So you can see the list of builtin tests for more.

Comments are very straightforward and dont need explanation.
We'll ignore line statements for now. and come back to it later
If you want jinja to ignore processing some part of the template, wrap it inside the 'raw' macro like this
{% raw %}
    <ul>
    {% for item in seq %}
    <li>{{ item }}</li>
    {% endfor %}
    </ul>
{% endraw %}

This will ignore processing of the template. So you have seen here:

Statement Blocks
Expressions
Comments
Variable-Attributes
Tests
Filters
