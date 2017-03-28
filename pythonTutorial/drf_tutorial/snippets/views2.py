# DRF provides a Request object which derives from HttpRequest and provides more flexible request parsing
# the main attribute is request.data which can handle put, patch, post all three

# Similarly it provides a Response object which is a type of TemplateResponse which takes the content and then uses
# content negotiation to determine the actual content_type to return to the client. Content negotiation means dynamically
# figuring out the content_type by
# 1) Looking at the "Accept" value in the corresponding request
# 2) Figuring out the content type based on URI
# 3) Looking at the data and figuring out the correct content_type

# To use the new Request and Response objects, decorate your FBV with @api_view decorator
# or derive from APIView class in DRF

from django.shortcuts import get_object_or_404, render
from rest_framework.request import Request
from rest_framework.response import Response
from rest_framework import status
from rest_framework.decorators import api_view, permission_classes
from rest_framework import permissions
from .models import Snippet
from .serializers import SnippetSerializer


@api_view(['GET', 'POST'])
@permission_classes((permissions.AllowAny,))
def snippet_list(request, *args, **kwargs):
    """ List all snippets or create a new one."""
    if request.method == 'GET':
        snippets = Snippet.objects.all()
        serializer = SnippetSerializer(snippets, many=True)
        return Response(serializer.data)
    else:
        # Parse the request.data attribute
        # need to check how SnippetSerializer takes request.data
        serializer = SnippetSerializer(data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        else:
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@api_view(['GET', 'PUT', 'DELETE'])
def snippet_detail(request, *args, **kwargs):
    snippet = get_object_or_404(Snippet, pk=kwargs['pk'])
    if request.method == 'GET':
        serializer = SnippetSerializer(snippet)
        return Response(serializer.data)
    elif request.method == 'PUT':  # update snippet
        serializer = SnippetSerializer(snippet, data=request.data)
        if serializer.is_valid():
            serializer.save()
            return Response(serializer.data)
        else:
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)
    elif request.method == 'DELETE':  # delete snippet
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
