Almost all the time you want to configure your project, you want to and save values like path to an executable, location of include and lib directories etc. and then use these during the build phase. You can do this in waf using the Context object.  
When you call "waf configure", the ctx object argument to the configure(ctx) function is waflib.Configure.ConfigurationContext. This class has an "env" attribute which if of type ConfigSet. ConfigSet is a dictionary like object. You can set values in this dictionary and use it during build phase. ConfigSet provides other functions like append_value, prepend_value, append_unique etc. Above all it provides serialization capability
By default, if a key doesnt exist, and you try to fetch it, it will return you an empty list. So the default value for this dictionary is list.

Note that the type of Context object received by a function, depends on the function.
1) configure will get waflib.Configure.ConfigurationContext
2) options will get waflib.Options.OptionsContext
3) build will get waflib.Build.BuildContext
4) normal functions like ping(ctx), pong(ctx) will get waflib.Context.Context

Run
"waf configure --foo=test"
waf build
waf distclean

# also note that use of
1) ctx.env.derive() --> used to create a copy of the ctx.env object
2) ctx.path.make_node() --> ctx.path is actually a Node object. A node object is very simple. In waf, Node objects are used to provide an abstraction over the file system. You they can represent a file or folder on the file system. They also provide details like list of files and folders under a give Node directory. etc. So here you are just creating a new Node object.
3) node.abspath() --> gives the absolute path
4) ctx.env.load() and .stor() are used to serialize and deserialize ConfigSet objects

the line
tg = ctx(rule=..., source=..., target=...) 
tg is an instance of class type waflib.TaskGen.task_gen. This class is responsible for creating waflib.Task.Task objects which actually run your rules. like compilaton, linking etc. waf will create many task_gen objects and then finally resolve the dependencies between them so they are built in the proper order.
