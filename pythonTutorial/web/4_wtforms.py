#!/usr/bin/env python

# Ideally you should have your own custom message for validators
# supplied as a keyword argument
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
#form = RegistrationForm(username='Rajat Girotra', email='rajatgirotra@yahoo.com', accept_rules=False)

print('Username', form.username.data)
print('Email', form.email.data)
print('Accept', form.accept_rules.data)

form.validate()

print('Errors', form.errors)

# There are a plethora of Field types and Validator types available.
# Check documentation for usage.
