Maven is a build tool for Java. It is written in Java itself so it runs in JVM. Trivial to install. Just download from tar.gz from apache and untar somewhere. 

Maven is plugin based; a plugin call have one or more goals. Goals are nothing but functions implemented in that plugin. Each goal can take one more argument. The basic command line is:

maven [options] [goals] [phases] [args]

Phases: Maven defines a build lifecycle which has multiple phases. You can either specify a goal to execute or a phase. When a phase is given, maven will execute all phases before it and including the phase given. Phases are also nothing but a short alias used for a goal defined in some plugin.

Just set JAVA_HOME to a valid JDK for maven to work. No need to set any M2_HOME, M2 or any other environment variable.

Configure Maven
==============
Maven can be configured at 3 places
1) MAVEN_OPTS --> This environment variable can be set to pass arguments to the JVM under which maven is running.
2) settings.xml --> There are 2 places where settings.xml can be specified. The MAVEN_HOME/conf/settings.xml (for everyone) and $HOME/.m2/settings.xml (user-specific). Both are merged and user specific is more dominant. Just copy the global setting.xml and make changes in that.
3) .mvn folder --> In your project root folder, the .mvn folder can have maven.config and extensions.xml files that contain project specific maven configurations.

Repository Manager
=================
You must consider using repository manager and configuring it in the settings.xml. A repository manager is a server application that acts like a proxy server for many public maven repositories. It also acts as a deployment destination where you can deploy your own project artifacts. There are many open source and commercial repository managers available.

Apache Archiva (open source)
CloudRepo (commercial)
Cloudsmith Package (commercial)
JFrog Artifactory Open Source (open source)
JFrog Artifactory Pro (commercial)
Sonatype Nexus OSS (open source)
Sonatype Nexus Pro (commercial)
packagecloud.io (commercial)
