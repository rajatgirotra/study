| *Settings*    | *Value*    |
| Library       | BuiltIn    |
| Test Setup    | Start Test |
| Test Teardown | Stop Test  |

| *Keywords*                                         |
| Start Test                                         | Log         | Starting test ${TEST_NAME} |
| Stop Test                                          | Log         | Stopping test ${TEST_NAME} |
| Log Something                                      | Log         |
| The result of ${calculation} should be ${expected} |
|                                                    | ${result} = | Evaluate | ${calculation} |
|                                                    | Should Be Equal As Integers | ${result} | ${expected} |

| *Test Cases* |
| Templated Test Case | [Template] | Log |
|                     | HelloWorld | level=WARN  |
|                     | CruelWorld | level=INFO  |
|                     | Goodbye    | level=DEBUG |
| Different arguments | [Template] | The result of ${foo} should be ${bar} |
|                     | 1 + 1      | 2        |
|                     | 4 - 1      | 3        |
| Only few arguments  | [Template] | The result of ${calculation} should be 6 |
|                     | 3 * 2      |
|                     | 5 + 1      |
| New arguments       | [Template] | The ${meaning} of ${life} should be 42 |
|                     | result | 21 * 2 |
