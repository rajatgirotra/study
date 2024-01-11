A gradle project can have a root project and multiple sub projects. With this setting, gradle needs a settings.gradle file at the root of your source tree; which defines the name of your root project and the various sub projects. Each sub project in turn has its own build.gradle script.

A plugin adds tasks to a project. It also adds properties and methods to a project. For example: the application plugin defines tasks that package and distribute an application, such as the "run" task. The Application plugin provides a way to declare the main class of a Java application, which is required to execute the code.
Applying the Application plugin also implicitly applies the Java plugin. The java plugin adds Java compilation along with testing and bundling capabilities to a project.

plugins {
   id("application")
}

application {
    mainClass = "com.example.Main"
}
