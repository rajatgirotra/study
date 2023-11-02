Java Flight Recorder (JFR)
=========================
JFR is a feature which is built into the JVM using which you can do lightweight performance analysis. Unfortunately JFR is not available
for all JVM. It is available for Oracle Hotspot JVM though.

How it works
============
Very trivial. JFR works on events. You can enable various events in the JVM like
1) a thread blocks on a monitor
2) a database query happens
3) an HTTP request is received etc.
Whenever such events occur, JFR will record data about these events to either memory (a circular buffer in memory) or to a file. This data can later be loaded in a diagnosis tool like
JMC (Java Mission Control) for searching for potential performance issues. The data is loaded either from the live JVM if recording is occurring in memory or is otherwise loaded from a file.

Enabling JFR
============
using command line
-------------------
To enable JFR, you need to pass -XX:+FlightRecorder to the command line of your application. for some JDK 8 versions, you might need to add -XX:+UnlockCommericalFeatures option as well.
This only enables the feature, but does not start any recording. To start the recording, you need to pass -XX:+FlightRecorderOptions=<OPTIONS> parameter.
OPTIONS are a CSV delimited string of name and value pairs.
If you start only using -XX:+FlightRecorderOptions, the default options will be set. By default, JFR is set up so that it has very low overhead: an impact below 1% of the
program’s performance.

To immediately start JFR recording when your application starts, you can use the -XX:+StartFlightRecording=<OPTIONS>.

If you forget to include these flags, remember that you can use "jinfo" to change their values and enable JFR.

To just start the JFR after your process has started, you can use "jcmd"
jcmd <processID> JFR.start [OPTIONS]

You can have multiple JFR recordings running at the same time. To check how many records are running, run
jcmd <processID> JFR.check [verbose]

To stop the recording:
jcmd <processID> JFR.stop [OPTIONS]

If a continuous recording has been enabled (read below "using jmc" section to understand difference between Fixed duration recording vs continuous recording), the current data in the circular buffer can be dumped to a file at any time via this command:
jcmd <processID> JFR.dump [OPTIONS]

using jmc
---------
you can also start the Java mission control tool, using which you can enable Java flight recorder. When you start jmc, it will show you all the available JVM processes running,
and you can choose which one to start the flight recorder for.

Flight recordings are made in one of two modes: either for a fixed duration (like 1 minute, 30 seconds etc) or continuously.
For continuous recordings, a circular buffer in memory is utilized; the buffer will contain the most recent events that are within the desired duration and size.
The continuous recording is best for reactive analysis. This lets the JVM keep the most recent events and then dump out a recording in response to an event.
For example, the WebLogic application server can trigger that a recording be dumped out in response to an abnormal event in the application server (such as a
request that takes more than 5 minutes to process). You can set up your own monitoring tools to dump out the recording in response to any sort of event.

To perform proactive analysis—meaning that you will start a recording and then generate some work (like sending a burst or orders) or do load-testing experiment after
the JVM has warmed up, a fixed-duration recording should be used. That recording will give a good indication of how the JVM responded during the test.

OPTIONS
=======
name=name
    The name used to identify the recording.
defaultrecording=<true|false>
    Whether to start the recording initially. The default value is false; for reactive analysis, this should be set to true.
settings=path
    Name of the file containing the JFR settings (see the next section on JFR Events).
delay=time
    The amount of time (e.g., 30s, 1h) before the recording should start.
duration=time
    The amount of time to make the recording.
filename=path
    Name of the file to write the recording to.
compress=<true|false>
    Whether to compress (with gzip) the recording; the default is false.
maxage=time
    Maximum time to keep recorded data in the circular buffer.
maxsize=size
    Maximum size (e.g., 1024K, 1M) of the recording’s circular buffer.

JFR Events
==========
As mentioned earlier, JFR supports many events. Often, these are periodic events: they occur every few milliseconds (e.g., the profiling events work on a
sampling basis). Other events are triggered only when the duration of the event exceeds a certain threshold (e.g., the event for reading a file is triggered only if
the read() method has taken more than a specified amount of time).

JFR is extensible: applications can define their own events. Hence, your JFR implementation may show many more available event types depending on
the application in question. For example, the WebLogic application server enables multiple application server events: JDBC operations, HTTP operations, and so on.
These events are treated just like the other JFR events: they can be individually enabled, may have a threshold associated with them, and so on. Similarly,
later versions of the JVM may have new and additional events.

Collecting events naturally involves overhead. The threshold at which events are collected also plays a role in the overhead that comes from enabling a JFR recording,
but sometimes this extra overhead is worthwhile.

The events (and the threshold for events) that JFR captures are defined in a template (which is selected via the settings option on the command line). JFR
ships with two templates: the default template (limiting events so that the overhead will be less than 1%) and a profile template (which sets most
threshold-based events to be triggered every 10 ms). The estimated overhead of the profiling template is 2%.

Templates are managed by the jmc template manager. Templates are stored in two locations: under the $HOME/.jmc/<release> directory (local to a user) and in
the $JAVA_HOME/jre/lib/jfr directory (global for a JVM). The template manager allows you to select a global template, select a local template, or define a new template.
To define a template, cycle through the available events, and enable (or disable) them as desired, optionally setting the threshold at which the event kicks in.
Templates are nothing but XML files.
