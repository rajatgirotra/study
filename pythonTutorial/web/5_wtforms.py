#!/usr/bin/env python

# You can also write your own custom iterators. Just define
# a function which takes a form and field parameter and raise a ValidationError if validation fails

from wtforms.validators import ValidationError
from wtforms import Form, IntegerField


def is_42(form, field):
    if field.data != 42:
        raise(ValidationError('Field value is not 42'))


class MyForm(Form):
    is_42 = IntegerField('Label', [is_42])

if __name__ == "__main__":
    form = MyForm(is_42=42)
    # form = MyForm(is_42=100)
    form.validate()

    print(form.errors)
