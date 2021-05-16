Pipes
----
very trivial. Pipes are used to transform your output in the template files.
exmaple

{{ username | uppercase }}

uppercase is a pipe which is going to output username in upper case. multiple pipes can be chained together using the pipe delimiter. example:

{{ some_date | date:'fulldate' | uppercase }}

here we chain two pipes, the date pipe and uppercase pipe.
Also pipes can take one or arguments separated by colon (:)
