2_README.txt first

You already know that some websites support basic HTTP authentication (simple username/password, like svn access in web browser).
If you have a URL which requires which basic HTTP authentication, how can java handle that?

java needs to extend the Authenticator class and override the
"protected PasswordAuthentication getPasswordAuthentication()" method. This function should return a PasswordAuthentication object which is a trivial class
with a "String username" and a "char[] password".

You must set your class to be used for Authentication using the "Authenticator.setDefault(Authenticator o)" api.
The URL class doesn't call getPasswordAuthentication() directly. It actually calls one of the several overloads of the
"static PasswordAuthentication requestPasswordAuthentication()" function which internally calls getPasswordAuthentication()
These overloaded functions take multiple parameters like
InetAddress of the requesting server, host, port, authority, protocol, prompt, scheme etc. So all this information can be accessed inside the getPasswordAuthentication()
function using the various get() methods to decide which username/password to use.

SimpleDateTimeClient.java next