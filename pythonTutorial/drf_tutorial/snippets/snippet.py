# coding: utf-8
from django.utils.six import BytesIO
from rest_framework import serializers
from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser
from snippets.serializers import Snippet, SnippetSerializer
# Create a couple of snippet instances
snippet = Snippet(code='foo = "bar"\n')
snippet.save()
snippet = Snippet(code='print "Hello, world\n"')
snippet.save()
# Serialization
# First create a SnippetSerialization instance and then view its data attribute
serializer = SnippetSerializer(snippet)
serializer.data
# data is nothing but the instance attributes in a python dictionary
# Now we can render this data into JSON using JSONRenderer
content = JSONRenderer().render(data)
content = JSONRenderer().render(serializer.data)
content
type(content)
# Deserialization
# Read a json stream first
stream = BytesIO(content)
type(stream)
# stream is an instance of BytesIO
data = JSONParser().parse(stream)
type(data)
data
# Data is now converted from a BytesIO instance to a python Dict
# Now we need to convert this Dict to a Snippet instance, this is again done by SnippetSerializer
serializer = SnippetSerializer(data=data)
# SnippetSerializer is now taking a Dict input to de-serialize, earlier it took a snippet instance for serialization
serializer.is_valid()
# Check if data is valid
# Now convert it into a snippet instance
snippet = serializer.save()
# serializer.validated_data contains proper data
serializer.validated_data
snippet
get_ipython().magic(u'save snippet.py 1-40')
