Gradle is a build system for Java. It has an extension API which is written in Java. So gradle needs a JVM to run. To interact with gradle's java api, gradle provides a DSL (Domain specific language) using Groovy. i.e. it defines certain code blocks which you can use in the gradle build script to tell gradle what to do.

Behind the scenes, gradle api has a "Project" interface and in turn many other interfaces are defined which extend the "Project" interface. example:
1) DependencyHandler
2) RepositoryHandler
3) Task
4) Action (which extends Task) etc etc.

gradle always creates an object of a concrete class which derives from Project. All the elements/blocks that you define in your build.gradle file interact with this object.

gradle defines many phases in its build lifecycle. And for every phase, you can define hooks/listeners/callbacks where you can monitor or configure your build system.

Have a look at the gradle java api here: https://docs.gradle.org/current/javadoc/index.html
and the gradle dsl here: https://docs.gradle.org/current/dsl/index.html

