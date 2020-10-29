TLS means Transport Layer Security. It is based on SSL and was developed after known vulnerabilities in SSLv3.

SSL/TLS provides
1) Data Encryption --> i.e. you can be sure that no one can make sense of your data.
2) Data Integrity --> i.e. you can be sure that your data hasnt been changed and tampered with
3) Authentication --> i.e. you can be sure that you are communicating with the intented person/server/application.

When communication with a peer, how do you make sure your data is not read by anyone else and that it is not changed.
You ensure this by ENCRYPTING IT and by SIGNING IT.  Both these require the use of keys. SSL/TLS uses asymmetric keys ie algos like RSA etc.

The PUBLIC KEY is used to ENCRYPT the message. and the PRIVATE KEY is used to DECRYPT it.
But how do you make sure the PUBLIC KEY belongs to the entity who claims it. The answer is that you need a Certificate Authority to sig n it.
That's what you call a Digital Certificate. A Digital Certificate establishes a link between the PUBLIC KEY and the entity who claims it.
Once signed, you can distribute your signed public key freely. This is an X.509 digital certificate.

Example on how web browsers speak with web servers:
1. Browser connects to server Using SSL (https)
2. Server Responds with Server Certificate containing the public key of the web server.
3. Browser verifies the certificate by checking the signature of the CA. To do this the CA certificate needs to be in the browser’s trusted store
4. Browser uses this Public Key to agree a session key with the server.
5. Web Browser and server encrypt data over the connection using the session key.

Generally a certificate is valid for use on a single fully qualified domain name (FQDN). That is a certificate purchased for use on www.mydomain.com cannot be used on mail.mydomain.com or www.otherdomain.com.
However if you need to secure multiple subdomains as well as the main domain name then you can purchase a Wildcard certificate.  A wildcard certificate covers all sub domains under a particular domain name.

For example a wildcard certificate for *.mydomain.com can be used on:

mail.mydomain.com
www.mydomain.com
ftp.mydomain.com

Common file formats for Digital Certificate files are. Certificate files can be bin ASCII format or Binary.

1) .der
2) .pem
3) .crt
4) .cert
5) .cer
6) .key

We must learn to differentiate between the file extensions above and the actual encoding used for the certificate. Encoding is different to the file extensions. The following codings are available

1) DER: A binary encoding used for the X.509 certificate. These kind of files can have the extension .der, .crt, .cert, .cer
2) PEM: An ASCII endoded X.509 certificate. Has -- BEGIN CERTIFICATE-- and -- END CERTIFICATE -- lines. file extension could be .pem, .crt, .cert, .cer
3) KEY: Just contains the PUBLIC or PRIVATE in PKCS8/PCKS12 format.

you can use openssl tools to find the encoding type or convert between encoding types.
For example a PEM format is a simple ASCII format which has BEGIN CERTIFICATE and END CERTIFICATE delimiters.

the certificate authority can create subordinate certificate authorities. Each of these subordinate certificate authorities can create more subordinates forming a chain of certificate authorities. Any of the subordinate certificate authorities or the root authority can be used for signing a public key.

A certificate can be stored individually in a file. or many ROOT certificates can be stored together in a file called a BUNDLE. On debian systems like ubuntu, the file /etc/ssl/certs/ca-certificates.crt contains all the root certificates on the system.


Some helpful commands using openssl to convert between different file formats and encodings

Remove password from PEM encoded private Key to get a plaintext Key in PEM Format
----------------------------------------------------------------------------------
openssl rsa -in privateKey.pem -out private.key

Remove password from PEM encoded private Key to get a plaintext Key in DER Format
----------------------------------------------------------------------------------
openssl rsa -in privateKey.pem -out private.key -outform DER

Convert a .crt file in DER format to PEM format, where the .crt file contains the certificate
----------------------------------------------------------------------------------------------
openssl x509 -inform DER -outform PEM -in server.crt -out server.crt.pem

Extract only private key from a PKCS#12 file (.pfx .p12) containing both private key and certificates into PEM format
----------------------------------------------------------------------------------------------------------------
openssl pkcs12 -in file.pfx -out file.key -nodes -nocerts

Extract only certs from a PKCS#12 file (.pfx .p12) containing both private key and certificates into PEM format
----------------------------------------------------------------------------------------------------------------
openssl pkcs12 -in file.pfx -out file.crt.pem -nodes -nokeys

Convert a PEM certificate file and a private key to PKCS#12 (.pfx .p12)
------------------------------------------------------------------------
openssl pkcs12 -export -out certificate.pfx -inkey privateKey.key -in certificate.crt -certfile CACert.crt

Just view a certificate file
-----------------------------
openssl x509 -in cert.crt -text -noout

Generate a new RSA public/private key pair
------------------------------------------
openssl genrsa -out private.pem 1024 (will create a private.pem file which can be used to get the public key also. see next cmd)
openssl rsa -in private.pem -out public.pem -pubout -outform PEM

Encrypt/Decrypt
----------------
openssl rsautl -encrypt -inkey public.pem -pubin -in file.txt -out file.ssl
openssl rsautl -decrypt -inkey private.pem -in file.ssl -out decrypted.txt
