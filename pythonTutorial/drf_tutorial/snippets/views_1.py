from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, JsonResponse
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
from django.views.generic import ListView, CreateView, DetailView, UpdateView, DeleteView
from rest_framework.renderers import JSONRenderer
from rest_framework.parsers import JSONParser
from rest_framework import status
from .models import Snippet
from .serializers import SnippetSerializer
from .mixins import JsonView, JSonResponseMixin


@csrf_exempt
def snippet_list(request, *args, **kwargs):
    # return all snippets as json
    if request.method == 'GET':
        snippets = Snippet.objects.all()
        serializer = SnippetSerializer(snippets, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        # create a new snippet and return that as json
        # parse() function also takes a request object as HttpRequest provides a
        # file like interface.
        data = JSONParser().parse(request)
        serializer = SnippetSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, status=status.HTTP_201_CREATED)
        else:
            return JsonResponse(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


@csrf_exempt
def snippet_detail(request, pk):
    snippet = get_object_or_404(Snippet, pk=pk)
    if request.method == 'GET':
        serializer = SnippetSerializer(snippet)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'PUT':
        data = JSONParser().parse(request)
        serializer = SnippetSerializer(snippet, data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data, safe=False)

    elif request.method == 'DELETE':
        snippet.delete()
        return HttpResponse(status=status.HTTP_204_NO_CONTENT)

# read 2.txt next

# # We create a simple class based view to list oll code snippets
# class SnippetListView(JsonView):
#     model = Snippet
#
#     def get_queryset(self):
#         return Snippet.objects.all()
#
#     def get_data(self, context):
#         serializer = SnippetSerializer(self.object_list, many=True)
#         return serializer.data
#
#
# class SnippetDetailView(DetailView, JSonResponseMixin):
#     model = Snippet
#     pk_url_kwarg = 'pk'
#
#     def render_to_response(self, context, **response_kwargs):
#         return self.render_to_json_response(context, **response_kwargs)
#
#     def get_data(self, context):
#         serializer = SnippetSerializer(self.object)
#         return serializer.data
#
#
# @method_decorator(csrf_exempt, name='dispatch')
# class SnippetDeleteView(DeleteView, JSonResponseMixin):
#     model = Snippet
