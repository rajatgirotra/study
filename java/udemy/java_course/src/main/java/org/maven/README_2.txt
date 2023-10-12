Lets dive a bit deeper in maven.

Maven has 3 lifecycles. Each lifecycle can have multiple phases and each phase can run multiple goals.
Lifecycles in maven are:
1) default (for building your project)
2) clean (for cleaning up)
3) site (for generating site and docs)
See here for a complete list of lifecycle phases in each lifecycle:
https://maven.apache.org/guides/introduction/introduction-to-the-lifecycle.html#Lifecycle_Reference

Clean everything and build again
===============================
"mvn clean deploy" # run clean lifecycle first, followed by all the phases of the default lifecycle till the deploy phase.

First thing you should do in your pom.xml is set the <packaging> element. default is jar, but you can set to "war", "ear", "pom".
Setting the <packaging> element will make maven set default goals for each lifecycle phase

Dependencies
============
you can fetch maven dependencies from maven central (you can just copy and paste the dependency from there)
Example:
<dependency>
    <groupId>junit</groupId>
    <artifactId>junit</artifactId>
    <version>4.12</version>
    <scope>test</scope>  <!-- scope = test means test time dependency -->
<!-- default scope if "compile". Other possible values are "test", "provided", "runtime", and some more.
     scope just help maven set the classpath correctly during compilation, testing, running and so on.
-->
</dependency>

Plugin configuration
=====================
For configuring your plugin, you should definitely consider using the "mvn help:describe -Dplugin=PluginName -Dgoal=PluginGoal -Ddetail"
command. It lists all the attributes for a goal that you can configure. The help will show you a property name also for every argument (if available).

Example: "mvn help:describe -Dplugin=compiler -Dgoal=compile -Ddetail" shows a source and target attribute with corresponding property names
"maven.compiler.source" and "maven.compiler.target"

Now to set the source and target configuration, there are many ways.
1) set the "source" and "target" attributes in the pom.xml.
<build>
  <plugins>
    <plugin>
      <artifactId>maven-compiler-plugin</artifactId>
      <version>3.3</version>
      <configuration>
        <source>1.5</source>
        <target>1.5</target>
      </configuration>
    </plugin>
  </plugins>
</build>

2) set the properties instead.
<properties>
  <maven.compiler.source>17</maven.compiler.source>
  <maven.compiler.target>17</maven.compiler.target>
  <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
</properties>

3) Pass on the mvn command line using -DparameterKey=parameterValue

mvn dependency plugin can be used to
 1) fetch dependencies from upstream.
 2) to look at the complete dependency tree for your project. try it out. Intellij even displays it nicely in a graph.
 3) playing around with your dependencies in general.

General structure of POM.xml
============================
in your pom.xml, you need to add your project artifactId, groupId, version anyway.
Also consider adding <packaging>, <name>, <url>, <licences>, <organization>, <developers> elements.


Resources
=========
In POM.xml, default is for resource files (audio, video, txt, image etc) to be stored at src/main/resources
similarly, while running test cases, test resources should be placed under src/test/testResources.
These can be fetched at runtime using.

YourClass.class.getClassLoader().getResource("weather.xml"); // for example

Basically getResource() or findResource() will look into the locations on the java classpath while finding any resource.
and mvn makes sure src/main/resources and src/test/testResources is on the classpath

Forcing mvn to use alternate JDK for different plugins
=======================================================
It is a totally valid use case that the JDK used for build might not be the same as the JDK on which you run your code in production.
mvn allows you to use different JDK's for compiling your code. By default (in the absence of any configuration), the various mvn plugins use
the same JDK tools (javac, javadoc, jar etc) under which mvn itself is running.
But you can change that at plugin level using the maven toolchain plugin. Start here to read details and try out:
https://maven.apache.org/plugins/maven-compiler-plugin/examples/set-compiler-source-and-target.html

In a Nutshell:
javac --source 8 --> Tell javac that your source code uses java 8 features, so needs at-least a compiler which can understand java 8 and up.
But what if maven itself is running using JDK 7 or lower? That's why you need th maven toolchain plugin to make sure the compiler plugin
uses at-least JDK 8 or up.

javac --target 7 --> Tells javac that you want to run your java code on JRE 7 or above. So produce class files compatible with JRE 7 and above.
However, using --target is not enough. There is something called as bootclasspath and that MUST ALSO BE SET to the same JRE as --target.
Example:
C\:>javac -source 8 -target 7 -bootclasspath C:\jdk1.7.0\lib\rt.jar -extdirs "" OldCode.java
So java 9 introduced a new flag/switch in java 9 called --release

javac --release 9 now implies "javac --source 9 --target 9 --bootclasspath <bootclasspath-from-java-9>"

So even in mvn now, consider setting the "release" attribute or "maven.compiler.release" property instead of using "source" and "target"

Creating self sufficient jar files
==================================
You can use the mvn assembly plugin to create a jar file with all your project dependencies. This will increase your jar file size,
but will make deployment a breeze as you just have a single jar.
Example configuration for assembly plugin
<build>
  <plugins>
    <plugin>
      <artifactId>maven-assembly-plugin</artifactId>
      <configuration>
        <descriptorRefs>
          <descriptorRef>jar-with-dependencies</descriptorRef>
        </descriptorRefs>
      </configuration>
    </plugin>
  </plugins>
</build>
mvn install assembly:assembly # meaning complete the "install" phase and then run assembly goal in assembly plugin.

Then you can run using:
java -cp simple-weather-1.0-jar-with-dependencies.jar <Main Class In Jar> <Arguments to your Java Program>

Attached goals to a phase
==========================
If you want to attach a plugin goal (for example, attached goal in the maven assembly plugin), you need to add an <executions>
elements under that <plugin> element. Example below shows how you can attach the assembly:attached goal to the "package" phase.

<build>
  <plugins>
    <plugin>
      <artifactId>maven-assembly-plugin</artifactId>
      <configuration>
        <descriptorRefs>
          <descriptorRef>jar-with-dependencies</descriptorRef>
        </descriptorRefs>
      </configuration>
      <executions>
        <execution>
          <id>simple-command</id>
          <phase>package</phase>
          <goals>
            <goal>attached</goal>
          </goals>
        </execution>
      </executions>
    </plugin>
  </plugins>
</build>