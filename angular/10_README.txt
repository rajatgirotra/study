Forms
-----

Normally when you create a form element in browser, it has attributes action and metho
1) action gives the location where the http request with the form details must be submitted to
2) method(GET or POST) indicate the type of request. Usually POST
Also the form has a button inside with type="submit" which tells the button to submit the form.

However in angular you do not want to submit the form to the server via http request. Instead you want to prevent the http request and want angular to take care of it as it is a SPA.
so in angular we just use the <form> element with "action" and "method" attributes and instead use "(ngSubmit)" directive which angular processes and returns you the details of the form-controls as a javascript object.
Lets see that in action in forms-one project.

Also angular provides two approaches to handling forms.

1) Template driven approach.
Here you import the FormsModule in your app.module.ts. When this module is imported and you provide a <form> element in your template html, angular will automatically process this <form> element and create a javascript object
for you. Well all-most automatically, With just a few changes. So think of <form> as sometype of angular directive which does all this processing and giving you a javascript object.

