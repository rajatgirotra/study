# Lets now use DRF mixins instead of using APIView.

from django.shortcuts import get_object_or_404
from django.contrib.auth.models import User
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.request import Request
from rest_framework import status
from rest_framework import mixins
from rest_framework import generics
from rest_framework import permissions
from .permissions import IsOwnerOrReadOnly
from .models import Snippet
from .serializers import SnippetSerializer, UserSerializer


# GenericAPIView has "queryset" and "serializer_class" attributes. You should provide values for these attributes in
# your class or override the "get_queryset()" and "get_serializer_class()" functions in your CBV.
# the ListModelMixin is fairly simple. It has one function called list() which calls get_queryset() and
# get_serializer_class() and then returns the data.

# the CreateModelMixin has a create() function which reads the "request.data" and uses the "serializer_class" attribute
# to create a serializer. It then calls perform_create() function which by default calls serializer.save(). You can
# override this function "perform_create" to provide custom behavior while saving.

# Also DRF adds a number of permission classes to control who can see/edit what. Look at rest_framework.permissions.
# here we use permissions.IsAuthenticatedOrReadOnly, ie if someone is not logged in , he can only get read access.
# Also default permissions are given in the settings.py file.
# See permission_classes = api_settings.DEFAULT_PERMISSION_CLASSES in GenericAPIView.APIView
# We can also write our own permission classes by subclassing from BasePermission and decide what permission to give
# based on user and that particular snippet detail. See permissions.py where we create a new permission
class SnippetList(mixins.ListModelMixin,
                  mixins.CreateModelMixin,
                  generics.GenericAPIView):
    queryset = Snippet.objects.all()
    serializer_class = SnippetSerializer
    # permission_classes = (permissions.IsAuthenticatedOrReadOnly,)
    permission_classes = (IsOwnerOrReadOnly, )

    def get(self, request, *args, **kwargs):
        return self.list(request, *args, **kwargs)

    def post(self, request, *args, **kwargs):
        return self.create(request, *args, **kwargs)

    def perform_create(self, serializer):
        serializer.save(owner=self.request.user)


# DestroyModelMixin has a destroy() function. This calls "get_object()" which uses queryset (get_queryset()) function
# and then filters queryset based on the kwarg passed in the URL. This kwarg can be specified in the following attributes
# lookup_field = 'pk' # default is 'pk' meaning the get_object_or_404() function in get_object() will be passed a dict
# in which a key 'pk' will be set. The value will be taken from kwargs[lookup_url_kwarg] in request. So there are two
# attributes lookup_field and lookup_url_kwarg.
# The destroy function then calls perform_delete() which you can override. By default, perform_delete() calls delete() on
# the object and returns Http_204_NO_CONTENT.

# Retrive is also very trivial. Calls get_object() followed by get_serializer() and return Response(serializer.data)
# Update is also trivial. It has and update() function which calls get_object() and
# get_serializer(instance=get_object()), and then calls perform_update() which calls save() by default
class SnippetDetail(mixins.DestroyModelMixin, mixins.UpdateModelMixin,
                     mixins.RetrieveModelMixin, generics.GenericAPIView):

    queryset = Snippet.objects.all()
    serializer_class = SnippetSerializer
    # permission_classes = (permissions.IsAuthenticatedOrReadOnly,)
    permission_classes = (IsOwnerOrReadOnly,)
    def put(self, request, *args, **kwargs):
        return self.update(request, *args, **kwargs)

    def get(self, request, *args, **kwargs):
        return self.retrieve(request, *args, **kwargs)

    def delete(self, request, *args, **kwargs):
        return self.destroy(request, *args, **kwargs)


class UserList(generics.ListAPIView):
    queryset = User
    serializer_class = UserSerializer


class UserDetail(generics.RetrieveAPIView):
    queryset = User
    serializer_class = UserSerializer

# Note that using command prompt (httpie) u need to send username/password too to authenticate yourself.
# example: http -a tom:password123 POST http://127.0.0.1:8000/snippets/ code="print 789"


def index_view(request, *args, **kwargs):
    context = {

    }
    return render(request, 'snippets/index.html', context)


def dashboard_view(request, *args, **kwargs):
    context = {

    }
    return render(request, 'snippets/dashboard.html', context)


# Next read 2_README.txt