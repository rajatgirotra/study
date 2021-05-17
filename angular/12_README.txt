Working with HTTP Requests
--------------------------

An angular app should never interact directly with a database (SQL or NoSQL). That is because
1) Angular is a front-end app. So we should have some middle tier to interact with DB
2) All your DB queries/credentials will be visible as angular code can be easily inspected in the browser.

What we usually do is always interact with an HTTP server (mostly a REST API, GraphQL API etc) which can interact with DB to store data, upload file, perform analytics etc and return you the results in JSON or any other format.

So to learn how to work with backends in Angular we need some dummy backend. We are going to use Firebase for that.
Firebase is a google service which provides a complete backend server with HTTP endpoints and database and is free to use. We set it up first by going to Firebase and logging in and creating a new project.

We created a project called my-angular-study, then we created a realtime database and in test mode so we can access without any authentication for now. later we will add authentication also.
my database endpoint is: https://my-angular-study-default-rtdb.asia-southeast1.firebasedatabase.app/



Anatomy of an HTTP request. the important parts of an HTTP request are:

1) HTTP endpoint: example /posts/1
2) HTTP verb: GET, PUT, POST, DELETE etc
3) HTTP Metadata: {Content-Type: 'application/json'} etc
4) Body



