# coding: utf-8
from rest_framework import serializers
from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser
from snippets.serializers import Snippet, SnippetSerializer

# Save a couple of snippets
snippet = Snippet(code='foo = "bar"\n')
snippet.save()
snippet = Snippet(code='print "Hello, world\n"')
snippet.save()

# The serializer class is very simple. All that it is responsible for is:
# 1) During serialization, convert Python Object to Dict
# 2) During de-serialization, convert Dict to Python Object
# We have saved two snipprt objects. Let's serialize a snippet object
serializer = SnippetSerializer(snippet)
print serializer.data
type(serializer.data)


# serializer.data is a dictionary. Its still not a JSON String. To convert to a json string, we use the JSONRenderer
# Renderers are used to convert a dictionary to the kind of data the renderer offers. We have multiple renderers.
content = JSONRenderer().render(serializer.data)
print content

from django.utils.six import BytesIO
# Let's convert a JSON String back to a snippet object
stream = BytesIO(content)
data = JSONParser().parse(stream)
print data
type(data)
# parse() method takes a stream and returns a dictionary. This dictionary can then be converted to Snippet object
data['title'] = 'SomeRandomTitle'
serializer = SnippetSerializer(data=data)
serializer.is_valid() # must call is_valid before accessing validated_data or save()
serializer.validated_data
snippet = serializer.save()  # will call create() or update() of the Serializer class depending on whether we are creating or updating an object.

s = Snippet(code='def foo():\n\tpass')
serializer = SnippetSerializer(s)
serializer.data
content = JSONRenderer().render(serializer.data)
content
stream = BytesIO(content)
data = JSONParser().parse(stream)
data.title
data['title'] = 'SomeNewRandomTitle'
serializer = SnippetSerializer(data=data, instance=s) # passing instance parameter also means update() will be called when save() method is called; otherwise create() is called.
news = serializer.save()
news = serializer.is_valid()
news = serializer.save()
news
news.id
