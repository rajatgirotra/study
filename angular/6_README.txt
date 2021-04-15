Debugging
========
developer tools is your best friend. when things dont work as expected.

1) try to open developer tools and check for obvious errors.

2) If they are no errors and likely there is some logical error, you can also debug typescript directly. Although angular converts all TS to javascript in the browser.
developer tools maintains a map of TS to javascript and also the TS is visible in developer tools under "Source". Think of it like gcc maintains debug symbols in the executable
when run using -g option. You can set breakpoint in TS directly.

3) Use a Chrome extension called Augury. it's really nice and gives a lot of details. worth exploring.
