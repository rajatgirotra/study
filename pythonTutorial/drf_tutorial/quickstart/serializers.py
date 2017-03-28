# the standard django.contrib.auth app provides User and Group models.
from django.contrib.auth.models import User, Group
# the serializer class is used to specify which all fields to use during
# serialization and de-serialization
from rest_framework import serializers


# means that the we are creating a serializer for a model.
class UserSerializer(serializers.ModelSerializer):
    class Meta:
        model = User
        fields = ('url', 'username', 'email', 'groups')


# similarly create a serializer for Group
class GroupSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = Group
        fields = ('url', 'name')
