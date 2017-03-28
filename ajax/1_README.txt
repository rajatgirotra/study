Very simple. AJAX stands for Asynchronous Javascript And XML. It is a methodology to interact (send and receive data) with the web server even after the page is loaded in the browser. So behind the scenes you can send a request to the web-server. The web server will reply asynchronously and the reply is used to update the Javascript DOM. When the DOM gets updated, parts of the web-page change dynamically without the whole page getting re-loaded.

Example:
function loadDoc() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("demo").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "ajax_info.txt", true);
  xhttp.send();
}

Steps
-----
1) We create an XmlHttpRequest() object. Almost all modern browsers support it.
2) Then we use the open(method, url, async) function to prepare a request. The open() method takes
    a) method --> GET or PUT
    b) url --> a file on the server (can be any file .txt, .xml, .php, etc) which can take some action.
    c) async --> true or async, false otherwise
3) send() --> to send the request to the server.

When we get a response, here we have provided a definition of the "onreadystatechange" function. This function is called every time the "readyState" variable changes. In this function we update the Javascript DOM which updates the web page when the "readyState" value is 4 (meaning request finished and response is ready)
attributes/functions of the XMLHttpRequest object
a) "onreadystatechange"  --> callback which is called when "readyState" changes
b) readysState
c) status
d) open() --> to prepare the request
e) send() --> to send it
f) send(string) --> when sending via method="POST"
g) setRequestHeader(header-name, header-value)
h) responseText --> Get the response data as a string
i) responseXML --> get the response data as XML

Take Care
--------
var request = new XMLHttpRequest();
request.obj("GET", "abc.asp", true); --> Browsers can sometime cache the results of the request, so that the next time they dont have to hit the server. However if you dont want the browser to use the cache results, specify some random number in the url query
request.obj("GET", "abc.asp?t=" + Math.random(), true) --> This will ensure that your url is unique so browser will not be able to use the cache results.

xhttp.open("GET", "demo_get2.asp?fname=Henry&lname=Ford", true); --> to send query values


To send by POST
--------------
xhttp.open("POST", "ajax_test.asp", true);
You need to create/add additional headers to send data via post. Use the setRequestHeader() function to set the http request header and value
xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
xhttp.send("fname=Henry&lname=Ford"); --> send data.


Synchronous JAX
---------------
When using
request.open("GET", "abcd.asp", false);
request.send(); --> This will hang until you get a response back from server.
//Add code to handle response directly here. No need for the "onreadystatechange" function.


readyState values
----------------
readyState  Holds the status of the XMLHttpRequest. Changes from 0 to 4:
0: request not initialized
1: server connection established
2: request received
3: processing request
4: request finished and response is ready

status values
------------
200: "OK
404: Page not found

If you have multiple AJAX tasks on your page, then you can create a single function to create the Request object and send the request to the server. This function should take a callback function to be called when a response for that particular request is received.

function loadDoc(url, cfunc) { // cfunc is the callback func
    var xhttp;
    xhttp=new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            cfunc(this);
        }
    };
    xhttp.open("GET", url, true);
    xhttp.send();
}
