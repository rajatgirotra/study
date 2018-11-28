There are mainly 3 styles of writing test cases.

1) Keyword style: Most commonly used, test case names are self explanatory like, "Perform Logon", "Validate Order", "Terminate Connection" etc. Test case contains the keyword names followed by keyword arguments.

2) Behavior Driven: Mostly used by non technical guys to write test cases, like "Given", "When", "Then". example:
*** Test Cases ***
Valid Login
    Given login page is open
    When valid username and password are inserted
    and credentials are submitted
    Then welcome page should be open

3) Data Driven : This is accomplished using template keywords. ie you define a keyword template. and then you just specify arguments (data) to the template keyword in your test cases.

Keyword driven test cases are converted to data driven test cases using template keywords. ie the [Template] setting. et's see in example:

| *Test Cases* | *Arguments* |
| Normal Test case | Example Keyword | first argument | second argument |
| Templated test case | [Template] | Example keyword |
|                     | first argumet | second argument |
|                     | first argumet | second argument |
|                     | first argumet | second argument |

The templated test case above just defines a test case which runs the "Exmaple Keyword" and expects 2 arguments. We are calling the same "Example keyword" multiple times with a different set of arguments.

If all your test cases in the test case file use the same template then you can also define the template in the "Settings" table using the "Test Template" setting.

Embedded variables in keywords
===============================
You already know that keywords take arguments. It is possible also to embed arguments in the keyword name itself. In that case it can take any additional arguments. The reason this is allowed is to create keywords which read more natural. We can use embedded keywords with template test cases too. Let's see example.

Read template_test.robot next
