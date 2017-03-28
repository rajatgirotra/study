#!/usr/bin/env python

# jinja2 is a very simple template library. Just create templates
# which contain keywords and other text then substitute those keywords
# using a dictionary where the keywords are replaces by their values.

# Mostly its used to generate HTML code but it could have other uses too

from jinja2 import Template

template = Template('Hello {{ name }}!')
templateArgs = {'name': 'Rajat Girotra'}
# Use template.render(dict or keywordArgument)
# to render your template
result = template.render(templateArgs)
print('Type result', type(result))  # note by default jinja2 gives u unicode
print('result', result)

