Tags
====

Robot allows tagging your test cases. Tags can be applied in different ways.

1) In the Settings table, you can have "Default Tags" and "Force Tags" settings. "Force Tags" setting can also be used in test suite initialization file.The tags here will apply to all the test cases in this file. and the levels below (if this setting is in a test suite initialization file)

2) Default Tags --> If a test case does not have an explicit [Tags] setting, then the tags in this setting will apply

3) [Tags] --> Test case specific setting

4) Remove Tags, Set Tags, Fail, Pass keywords --> Can apply tags at run-time.

5) --settag option --> Additional tag you want to apply at runtime.

Timeouts
========
*** Settings ***
Test Timeout   2 minutes    # Used to indicate 2 mins timeout for every test case.

At keyword and test case level also, [Timeout] setting can be used. If [Timeout] setting is empty, there is no timeout. See robots Time format on how time can be specified.
Examples:

*** Test Cases ***
Override
    [Documentation]    Override default, use 10 seconds timeout
    [Timeout]    10
    Some Keyword    argument

Custom Message
    [Documentation]    Override default and use custom message
    [Timeout]    1min 10s    This is my custom error
    Some Keyword    argument

Variables
    [Documentation]    It is possible to use variables too
    [Timeout]    ${TIMEOUT}
    Some Keyword    argument
