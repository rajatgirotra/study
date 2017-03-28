# In DRF, the first thing you need to do to create a WEB/REST API is to create a serializer class for you model.
# We have serializers.Serializer class and many of its subclasses which you can use. The Serializer class tells you how
# to serialize and deserialize your model objects

# Note that DRF also has a browseable API  which can be used for adding/modifying/deleting Objects
# and for viewing serialized data and debugging.

from django.contrib.auth.models import User
from rest_framework import serializers
from .models import LANGUAGE_CHOICES, STYLE_CHOICES, Snippet


# define all the fields which you want to serialize and deserialize.
# serializer classes work in a very similar way to Django forms
# class SnippetSerializer(serializers.Serializer):
#     id = serializers.IntegerField(read_only=True)
#     created = serializers.DateTimeField(read_only=True)
#     title = serializers.CharField(max_length=100, allow_blank=True, required=False)
#     # the style below will be used by the browsable web api.
#     code = serializers.CharField(style={'base_template': 'textarea.html'})
#     linenos = serializers.BooleanField(required=False)
#     language = serializers.ChoiceField(choices=LANGUAGE_CHOICES, default='python')
#     style = serializers.ChoiceField(choices=STYLE_CHOICES, default='friendly')
#     # We see there is a lot of redundancy in the fields defined here and in the corresponding
#     # model Snippet. Later we'll see how we can eliminate this by using ModelSerializer class
#
#     # the create or update method is automatically called when someone calls save()
#     # on this serializer instance. validated_data is similar to cleaned_data as in django form
#     # it has been validated and can be used by create() or update()
#     def create(self, validated_data):
#         """ Create and return a new Snippet instance given validated_data"""
#         # store in DB, validated_data is a Dictionary
#         return Snippet.objects.create(**validated_data)
#
#     def update(self, instance, validated_data):
#         """ update and return the snippet instance """
#         # instance is of type Snippet
#         instance.title = validated_data.get('title', instance.title)
#         instance.linenos = validated_data.get('linenos', instance.linenos)
#         instance.code = validated_data.get('code', instance.code)
#         instance.language = validated_data.get('language', instance.language)
#         instance.style = validated_data.get('style', instance.style)
#         instance.save()
#         return instance

# # Lets jump to django shell and do some manipulation with SnippetSerializer
# # Also we'll see what LEXERS, LANGUAGE_CHOICES, and STYLE_CHOICES.
# See somefile.py next

# Lets use a ModelSerializer instead of just Serializer
class SnippetSerializer(serializers.ModelSerializer):
    owner = serializers.ReadOnlyField(source='owner.username')
    class Meta:
        model = Snippet
        fields = ('id', 'created', 'title', 'code', 'linenos', 'language', 'style', 'owner')

# Read somefile.py to understand the usage of a serializer class. Then go an and read views.py


# adding a serializer for Django Auth Users
class UserSerializer(serializers.ModelSerializer):
    snippets = serializers.PrimaryKeyRelatedField(many=True, queryset=Snippet.objects.all())

    class Meta:
        model = User
        fields = ('id', 'username', 'emails', 'snippets')