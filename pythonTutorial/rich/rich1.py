import json
from time import sleep
from datetime import datetime

from rich.console import Console

console = Console()
# Drawing a line using rich (with optional text)
console.rule("[bold red]print a list")

# by default, rich will apply some simple syntax highlighting for built-in data structures like list, dict, tuples, set etc
console.print([1, 2, 3])

# for strings, it will apply any console markup that you provide
console.rule("[bold red]using markup")
console.print("[blue underline]Looks like a link")

console.rule("default dict printing")
console.print(locals()) # locals() returns a dict so syntax highlighting is performed.

console.rule("applying style attribute to string")
console.print("FOO", style="white on blue") # you can also provide your own style using the style argument

console.rule("No highlighting")
console.print("Hello World") # just like normal print. no syntax highlighting.


# There are some convenience wrappers provided by rich. They all just use Console class's print/print_json method under the hood.
from rich import print, print_json
from rich.pretty import pprint

# print is just a drop in replacement for python's print. But it can take console markup for printing
console.rule("another example of markup")
print("[italic red]Hello[/italic red] World!", locals())

# pprint is a drop in replacement for python's pprint, But it takes on many named arguments to control the pretty printing
# lets try to use it to print a big object.
superhero = {"person": {"name": "John Jones", "age":30, "address":{"street": "123 Main St", "city": "Gotham",
            "state":"NY", "zip_code": "12345"}, "superpowers":{"leaps_buildings":True,"factorizes_polynomials":False},
            "contacts":[{"type":"email","value":"john.jones@heroes.are.us"}, {"type":"phone","value":"555-123-4567"}],
            "hobbies": ["reading","hiking","coding","crimefighting"],"family":{"spouse": {"name":"Griselda Jones", "age":28},
            "children":[{"name":"Bellatrix", "age":5, "name":"Draco", "age":8}]}}}
console.rule("using rich.pprint")
pprint(superhero, indent_guides=True, expand_all=True, max_depth=3)

console.rule("using print_json() method")
json_obj = json.dumps(superhero)
print_json(json_obj)

# Rich also provides a log() function which also print the time and file. Ok for basic logging
from rich.json import JSON
console.rule("using console.log")
console.log(JSON(json_obj))

# Status. Rich use Context Managers to display a status message with a spinner. this status message wont interfere with the rest of your
# output. the spinner argument is a string. Run python -m rich.spinner to see the available spoinners.
with console.status("[bold yellow]Working...", spinner="dots2"):
    sleep(2)


style = "bold white on blue"
console.print("Rich", style=style, width=20)
console.print("Rich", style=style, justify="left", width=20)
console.print("Rich", style=style, justify="center", width=20)
console.print("Rich", style=style, justify="right", width=20)

# Taking input from user just like python's input method
console.input("What is [i][bold]your[/bold][/i] [bold red]name[/]? :grinning: ") # :grinning: is an emoji. Run "python -m rich.emoji to find the emoji text

# Creating a console for error i.e. stderr
error_console = Console(stderr=True, style="bold red")
error_console.print("Undefined behavior!!")

# creating a console for file output.
with open("report.txt", "w") as report_file:
    file_console = Console(file=report_file)
    file_console.rule(f'[bold red]Report generated {datetime.now().ctime()}')

from rich.panel import Panel
from rich import box
console.print(Panel.fit("Hello, [bold red]World!", box=box.DOUBLE_EDGE))