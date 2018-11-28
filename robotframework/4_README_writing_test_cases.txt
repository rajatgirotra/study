How to write a TEST CASE
=======================
A test case is written in a test case table. There should be no blank line between the test case table header and the name of the first test case.
Test case names are written in the first column.

First column -> Test case name
Second column -> Can be any of the following
1) Keywords
2) One or more variables which are returned from keywords, followed by the keyword itself
3) Settings for that test case (in square brakcets) like [Documentation], [Tags], [Setup], [Teardown], [Template], [Timeout] etc

After the keyword, the rest of the row are the arguments to that keyword.

All test by default get a scalar variable ${TEST_NAME} which you can use to refer to that test. This variable is available in all keywords used in the test and also in the test setup and teardown keywords.


Settings in a test case
=======================

[Documentation] --> used to add documentation. Also supports a bit of markup like *this text will be bold*, _this text will be italics_ etc.
typically test case names should be good enough that you require least documentation. If you require excessive documentation, you need better test case names.


When test cases fail
=====================
Usually a test fails when a keyword fails. And usually the keyword also returns the error string. At that point, the test teardown is done and the next test case starts executing. However, we can also continue the test case even if one or more keywords fail using the keywords "Run Keyword And Ignore Error" and "Run Keyword And Except Error" but we'll see those later. Failure messages are usually text, but you can prefix *HTML* to make them html content

Where does a test case find Keywords
===================================
Keywords can be specified in the imported test libraries, or resource files or also defined in the Keyword table in the test case file.
Passing arguments to keywords is also trivial. You can pass positional arguments, or named arguments or variable arguments also just like in python. Very trivial, you'll get used to it as you write test cases. Note that for named argument syntax there should be no space to the left and right of the = sigm. example: arg=value


Setup and Teardown
=================
We have setup and teardown at various levels

1) Suite level (directory)
"Suite Setup" and "Suite Teardown" are run at start and end of a test suite. Test suite can be either a test case file or a test directories. In case of test directory, the "Suite Setup" and "Suite Teardown" must be part of the directory initialization file. These are just keywords which can take arguments. Suite Setup is run once before all test cases in that suite are run and Suite Teardown is run after. Suite Teardown is run even if Suite Setup fails and all keywords are run even if keywords in the Suite Teardown fail. If Suite Setup fails all test cases are marked failed and not run.

2) Suite level (file)
Since a test case file is also a test suite. You can have Suite Setup and Teardown at file level also. Also at this level you have 2 other keywords "Test Setup" and "Test Teardown" which are run before starting and after finishing every test in that file.

3) Test Level
You have settings [Setup] and [Teardown] at every test case level. If this present, it overrides the "Test Setup and Teardown". If this is specified but empty, this means there is no Setup and Teardown.

