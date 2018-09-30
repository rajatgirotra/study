settings.xml is an xml file. The important elements are:

<localRepository/> --> the url to a local repository where your artifacts can be deployed. These artifacts can then be used by other inhouse projects. default is {user.home}/.m2/repository.
"mvn install" installs to this location. 

<interactiveMode/> --> should maven try to interact with the user for input or not. Default is true.

<usePluginRegistry> --> ignore.

<offline> --> if you want to work in offline mode.

<pluginGroups>
   <pluginGroup/>
   <pluginGroup/>
</pluginGroups>
A list of group id's which are searched for goals in case you do not specify the groupId on the command line. "org.apache.maven.plugins" and "org.codehaus.mojo" are already added by default.

<servers>
    <server/>
    <server/>
</servers>
You can define mutiple servers that you can connect to download and deploy artifacts. Here you only define the server permissions and credentials. The sub-elements of the server elements are <id>, <username>, <password>, <privatekey>, <passphrase>, <filePermissions>(664), <directoryPermissions>(775).

<mirrors>
    <mirror/>
    <mirror/>
</mirrors>
This is where you define the repository managers. the sub-elements of <mirror> are <id>, <name>, <url>, <mirrorOf>

<proxies>
    <proxy/>
    <proxy/>
</proxies>
For defining proxy settings

<profiles>
    <profile/>
    <profile/>
</profiles>
Profiles are slightly complex. Let me try to explain in steps:
1) The sub-elements of the <profile> elements are only a sub-set of the <profile> elements in a project pom.xml. The sub-elements are only <id>, <activation>, <repositories>, <pluginRepositories> and <properties>. These concern themselves with the build system as a whole and are not related to any user or project specific configuration. Let's go through each of these elements

<id> --> just a user friendly name

<activation> --> This itself has many sub-elements. When maven is running, certain profiles can be activate or non-activate. In the <activation> element you can specify sub-elements based on which maven can decide to activate this profile or not. Lets see these sub-elements

    <activeByDefault>true</activeByDefault> --> ie always active
    <jdk>1.5</jdk> -->activate profile if jdk version is 1.5
    <os></os> --> has sub-elements (see online) based on which a profile is activated or not
    <property>  --> activate profile is this property exists.
        <name/>
        <value/>
    <property>
    <file> -->activate this profile if a file is existing or missing
        <exists/>
        <missing/>
    </file>

Other ways of activating a profile are:
1) via the <activeProfile> elements in the settings.xml (must give the profile id there).
2) specify -P profileId on the command line explicitly
"mvn help:active-profiles" will give you more pointers.

<repositories>
    <repository>
        <id/>
        <name/>
        <url/>
        <release>
            <enabled/>
            <updatePolicy/>
            <checksumPolicy> 
        </release>
        <snapshots>
            <enabled/>
            <updatePolicy/>
            <checksumPolicy> 
        </snapshots>
    </repository>
</repositories>

This exists within a profile and is only used when a profile is activated.
<pluginRepositories> --> is exactly similar to <repositories> just that it is for maven plugin repositories, not for general project dependency repository.

<properties> --> There are 5 different types of properties available. Properties are nothing but a name and value pair.
1) Environment Variables
${env.X} --> will return the value of an environment variables in settings.xml or pom.xml

2) project.x --> a dotted notation in POM.xml will return the value of the corresponding elements. exmaple: <project><version>1.0</version></project>, ${project.version} will return 1.0

3) settings.x --> ditto as above but for settings.xml

4) All Java system properties accessible via java.lang.System.getProperties() are available like ${java.home}

5) explicitly set properties in <properties> elements, example: ${someVar}

We are done with <profiles> now.

Last element in settings.xml is <activeProfiles>. which can have one or more <activeProfile> sub-elements which contain the profile id which you want to make active by default. If no such profile exists in POM.xml, nothing will happen and maven will just ignore it and continue.

to activate a profile defined in settings.xml use the <activeByDefault> element or use the -P flag to mvn command as explained above. 

Last Note: if a profile id exists in pom.xml and settings.xml, settings.xml will win.
