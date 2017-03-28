# Lets now make use of CBV instead of FBV using DRF APIView class

from django.shortcuts import get_object_or_404
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.request import Request
from rest_framework import status
from .models import Snippet
from .serializers import SnippetSerializer


# the APIView class derives from django View class and overrides
# dispatch to call your view function with the DRF request object instead of standard HttpRequest object
# Also it provides a bunch of other functionality will look into later.
class SnippetList(APIView):
    """ List all snippets, or create a new one. """
    def get(self, request, *args, **kwargs):
        snippets = Snippet.objects.all()
        serializer = SnippetSerializer(snippets, many=True)
        return Response(serializer.data)

    def post(self, request, *args, **kwargs):
        # Will create a serializer using JSON data in request.data
        serializer = SnippetSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        else:
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


class SnippetDetail(APIView):
    """ Retrieve, update or delete a snippet. """
    def get(self, request, *args, **kwargs):
        snippet = get_object_or_404(Snippet, id=kwargs['pk'])
        serializer = SnippetSerializer(snippet)
        return Response(serializer.data)

    def put(self, request, *args, **kwargs):
        snippet = get_object_or_404(Snippet, id=kwargs['pk'])
        serializer = SnippetSerializer(snippet, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        else:
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, *args, **kwargs):
        snippet = get_object_or_404(Snippet, id=kwargs['pk'])
        snippet.delete()
        return Response(status=status.HTTP_204_NO_CONTENT)


def index_view(request, *args, **kwargs):
    context = {

    }
    return render(request, 'snippets/index.html', context)


def dashboard_view(request, *args, **kwargs):
    context = {

    }
    return render(request, 'snippets/dashboard.html', context)
