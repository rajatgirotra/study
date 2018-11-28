Tags
====

Robot allows tagging your test cases. Tags can be applied in different ways.

1) In the Settings table, you can have "Default Tags" and "Force Tags" settings. "Force Tags" setting can also be used in test suite initialization file.The tags here will apply to all the test cases in this file. and the levels below (if this setting is in a test suite initialization file)

2) Default Tags --> If a test case does not have an explicit [Tags] setting, then the tags in this setting will apply

3) [Tags] --> Test case specific setting

4) Remove Tags, Set Tags, Fail, Pass keywords --> Can apply tags at run-time.

5) --settag option --> Additional tag you want to apply at runtime.
