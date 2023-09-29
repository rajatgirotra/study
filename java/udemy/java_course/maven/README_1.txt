Maven assumes some defaults

src dir:            ${basedir}/src/main/java
resource dir:       ${basedir}/src/main/resources
test dir:           ${basedir}/src/test/java
output class dir:   ${basedir}/target/classes
output jar file:    ${basedir}/target

Maven is a plugin based architecture. And we have a lifecycle in Maven. This lifecycle can be modified (new phases in lifecycles can be added etc)
by different plugins. Most of the plugins have goals. And that is where all action happens. Lets continue to learn further.

Both plugins and the project dependencies can be downloaded from the maven central repo. Maven also has some set of core plugins we will see in a bit.

To create a new mvn project: you will need archetype plugin
For compiling Java files: you will need a compiler plugin
For testing code: a test plugin (like Surefire)
For creating JAR files: A Jar plugin
For Plugin and other help: We need the help plugin
There are plugins for running reports, plugins for running Groovy code, plugins to publish to remote sites.
For executing java classes: exec plugin by Codehaus
Maven dependency plugin to resolve project dependencies
Maven assembly plugin to assembly your project for distribution (like a jar file with all dependencies, a tar.gz file, a war or ear file etc)
Maven exec plugin to execute java programs, example: "mvn exec:java -Dexec.mainClass=org.sonatype.mavenbook.weather.Main"


Maven has a concept of a Project. A project is defined using
1) Group Identifier
2) Artifact Identifier
3) Version

Projects can use these coordinates above to list their project dependencies. These dependencies are listed in a Maven POM file (Project Object Model)

Help Plugin
===========
Has 3 main goals. "active-profiles", "effective-pom", "effective-settings". Must be run from project ${basedir}
The 4th goal is "describe". It can be used to fetch help on other plugins, and many more things. Example, the help:describe goal takes a plugin
attribute/parameter (-Dplugin=<PluginName> or -Dplugin=group.identifier[.version]), to describe about that plugin. Try it.

mvn help:describe -DPlugin=help # i.e run the describe goal in the help plugin and pass -Dplugin=help as attribute.

to find out all the attributes/parameters (-D options supported for a plugin or goal, use "mvn help:describe -Dplugin=<Plugin> -Ddetail)

To get detail only for a single goal, run:
mvn help:describe -Dplugin=compiler -Dgoal=compile -Ddetail
mvn help:describe -Dplugin=exec -Dfull

A Mojo in maven is just a fancy name for a plugin goal.

Create a Simple mvn project using archetype project
===================================================
mvn archetype:generate -DgroupId=org.sonatype.mavenbook.ch03 -DartifactId=simple -DpackageName=org.sonatype.mavenbook

a pom.xml file in your project is what makes mvn do its work. However, your project pom inherits from the Super POM that Maven has internally.
maven also takes into account any parent POM files, user settings and active profiles before building an effective POM which is the actual POM maven uses.

user settings file is: ~/.m2/settings.xml
A file containing user-specific configuration for authentication, repositories, and other information to customize the behavior of Maven.

to see the effective pom, run "mvn help:effective-pom" in the project ${basedir}
We will learn about parent POM's, user settings and active profiles later on.

Maven lifecycles
================
Maven build lifecycle is split into multiple phases. You can run any phase you like. Eg: compile phase, package phase, test phase, install phase etc.
Each phase can have multiple goals attached to it. These goals are run by maven when in a phase is executed. Maven also makes sure that all previous phases
also execute before the one given on the command line. Eg: "mvn install" will run all phases before install and then the install phase.
some default goals executed as part of the default lifecycle are:

resources:3.0.2:resources
compiler:3.8.0:compile
resources:3.0.2:testResources
compiler:3.8.0:testCompile
surefire:2.22.1:test
jar:3.0.2:jar
install:2.5.2:install

You also have a "site" phase which is used to generate a site and documentation for your project. run "mvn site" to see that.

"mvn test" to run the test phase

"mvn install -Dmaven.test.skip=true" # to skip running unit tests.
"mvn test -Dmaven.test.failure.ignore=true" # to ignore unit test failure and proceed. This config will apply to the surefire test plugin.

Project dependencies
====================
project dependencies are listed inside the POM.xml file. Very trivial. You dont need to list dependencies of dependencies.
Maven can figure that out on its own. whenever maven downloads a dependency, a POM.xml file for that dependency is also downloaded in the ~/.m2 folder.
This pom.xml is very important for maven to figure out transitive dependencies.
Also, when you run "mvn install" a modified version of your project pom is also installed into the ~/.m2 folder so other users of your project can use it.
Project dependencies listed in pom.xml have a <scope> element and also an <optional> element.
A test-scoped dependency is a dependency that is available on the classpath only during test compilation and test execution. If your project has war
or ear packaging, a test-scoped dependency would not be included in the project’s output archive. Example is junit.
other option for <scope> could be "runtime"