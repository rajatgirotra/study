from django.shortcuts import render
from django.contrib.auth.models import User, Group
from rest_framework import viewsets
from .serializers import UserSerializer, GroupSerializer
# Create your views here.


class UserViewSet(viewsets.ModelViewSet):
    """ API Endpoint that allows users to be viewed and edited. """
    queryset = User.objects.all().order_by('-date_joined')
    serializer_class = UserSerializer


class GroupViewSet(viewsets.ModelViewSet):
    """ API Endpoint that allows users to be viewed and edited. """
    queryset = Group.objects.all()
    serializer_class = GroupSerializer
