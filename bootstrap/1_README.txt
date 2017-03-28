What is it?
Very trivial. Just a collection of HTML 5 elements and CSS to create responsive websites.
Responsive meets that they can work everywhere. Mobile phones, tables, desktops and larger screens.

How to get it?
Either download it. There is a bootstrap,css and bootstrap-theme.css and bootstrap.js
and their minified versions. Or better just add a link to these files and they will automatically get downloded.

<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" integrity="sha384-1q8mTJOASx8j1Au+a5WDVnPi2lkFfwwEAa8hDDdjZlpLegxhjVME1fgjWPGmkzs7" crossorigin="anonymous">

<!-- Optional theme -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap-theme.min.css" integrity="sha384-fLW2N01lMqjakBkx3l/M9EahuwpSfeNvV63J5ezn3uZzapT0u7EYsXMjQV+0En5r" crossorigin="anonymous">

<!-- Latest compiled and minified JavaScript -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/js/bootstrap.min.js" integrity="sha384-0mSbJDEHialfmuBBQP6A4Qrprq5OVfW37PRR3j5ELqxss1yVqOtnepnHVP9aJ7xS" crossorigin="anonymous"></script>


Bootstrap must be written within a container or container-fluid class.

container and container-fluid - both are responsive meaning they change shape based on the width of the viewport.
the difference is that container-fluid will completely occupy the width of the viewport, and will be responsive to slightest of changes in the viewport,
wheres
container will be responsive only when the width changes past a threshold value. We'll see more in a while.

Bootstrap provides a grid system. where it divides the complete width of the viewport (the visible area for the website) into 12 columns.
When you define a <div class="row">, you must define define details for all 12 columns. Format for defining columns is:

col-*-*, where first * is one of

xs - extra small for targeting mobile phones and up
sm - small for targeting tables and up
md - medium for targeting desktops
lg - large for targeting larger screens

the second * can be number 1-12.

Let's start with some example.
