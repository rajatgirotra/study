#!/usr/bin/env python


def test():
    print "Hello World!"

# pylint --function-rgx="[a-z_][a-z0-9_]{2,30}$" config_test.py -rn
# means function name should start with a-z or _,
# followed by multiple a-z or _ (minimum 2 to 30 ) chars
# Similarly look at https://pylint.readthedocs.io/en/latest/user_guide/options.html
# to see what other options are supported.
