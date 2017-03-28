#!/usr/bin/env python

from wtforms import Form, BooleanField, StringField, validators


class RegistrationForm(Form):
    username = StringField('Username', [validators.Length(min=4, max=25)])
    email = StringField('Email Addressl', [validators.Length(min=6, max=30)],
                        default=u'rajatgirotra@yahoo.com')
    accept_rules = BooleanField('I accept site rules',
                                [validators.InputRequired()])

form = RegistrationForm(username='Rajat Girotra', accept_rules=False)

print('Username', form.username.data)
print('Email', form.email.data)
print('Accept', form.accept_rules.data)

form.validate()

print('Errors', form.errors)
