Databinding
==========
Think of angular data binding as communication between your TypeScript code which is your business logic and your templateUrl i.e. your HTML.

We have uni or bidirectional databindings. Different ways

From TypeScript to HTML
1) string interpolation {{ data }}
2) property binding [property] = "data")

From Html to TS
1) Event binding (event) = "expression")

Bidirectional

[(ngModel)] = "data"
