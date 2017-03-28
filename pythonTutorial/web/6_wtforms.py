#!/usr/bin/env python

# How to render these fields in HTML. Turns about the Widget instance in each Field
# knows how to render that field. But what do you type in HTML such that the field gets displayed.
# Very simple, simply connverting a Field to str() prints out the HTML.
# So if you are rendering using any template library like ninja, and if your field name is username for example,
# just do
# <div>
# <form method="POST" action="/login">
# {{ form.username.label }}: {{ form.username(class="some_css_class") }}
# </div>
# </form>

# actually whatever you type in the parameter list (like class="some_css_class") becomes the attributes of the field.

from wtforms import Form, BooleanField, StringField, validators


class RegistrationForm(Form):
    username = StringField('Username', [validators.Length(min=4, max=25)])
    email = StringField('Email Address',
                        [validators.Length(min=6, max=30),
                         validators.Email(message='Thats not a valid email')])
    accept_rules = BooleanField('I accept site rules',
                                [validators.InputRequired(
                                    message='Please accept to continue')])

form = RegistrationForm(username='Rajat Girotra', email='rajatgirotra', accept_rules=False)

print('Username', form.username.data)
print('Email', form.email.data)
print('Accept', form.accept_rules.data)

form.validate()

print('Errors', form.errors)

print('Username Render', str(form.username))
print('Email Render', str(form.email))
print('Accept Render', str(form.accept_rules))

# By default, wtforms gives your field an "id" and "name" which is the same as the field variable name you define
# in your form. Also the first parameter passed to a Field c'tor is the label. which can be used to render a label in HTML
# using example: field.username.label (ie what should be displayed as the label before the HTML render the input box)
