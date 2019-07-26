just run
"waf ping pong ping pong"
you will notice that every time the id(ctx) print something different. id() is just an integer which is unique and constant for an object's lifetime. When an object is destroyed, an another object created, it may also have the same id() value.

Also note that the ctx type is waflib.Context.Context
