DRF defines a concept of ViewSets. A viewset is nothing but a class which inherits from a combination of mixins and a
view class. For example,

class ReadOnlyModelViewSet(mixins.RetrieveModelMixin,
                           mixins.ListModelMixin,
                           GenericViewSet):

Now in your views.py, your CBV only needs to inherit from these ViewSets. You don't need to override any of the HTTP methods
like get, put, post, delete etc. All you need to do is define a mapping between the http methods and the corresponding
methods in the ViewSet. Example:

class SnippetViewSet(viewsets.ModelViewSet):
    queryset = Snippet.objects.all()
    serializer_class = SnippetSerializer
    permission_classes = (permissions.IsAuthenticatedOrReadOnly,
                          IsOwnerOrReadOnly,)

    @detail_route(renderer_classes=[renderers.StaticHTMLRenderer])
    def highlight(self, request, *args, **kwargs):
        snippet = self.get_object()
        return Response(snippet.highlighted)

    def perform_create(self, serializer):
        serializer.save(owner=self.request.user)
-----------------------------------------------------------------
In your urls.py, you'll do:

snippet_list = SnippetViewSet.as_view({
    'get': 'list',
    'post': 'create'
})
snippet_detail = SnippetViewSet.as_view({
    'get': 'retrieve',
    'put': 'update',
    'patch': 'partial_update',
    'delete': 'destroy'
})
snippet_highlight = SnippetViewSet.as_view({
    'get': 'highlight'
}, renderer_classes=[renderers.StaticHTMLRenderer])

ie we define multiple functions (snippet_list, snippet_detail, snippet_highlight), where we list the mapping b/w the
http method and the viewset method.

and then define the URL like below:

urlpatterns = format_suffix_patterns([
    url(r'^$', api_root),
    url(r'^snippets/$', snippet_list, name='snippet-list'),
    url(r'^snippets/(?P<pk>[0-9]+)/$', snippet_detail, name='snippet-detail'),
    url(r'^snippets/(?P<pk>[0-9]+)/highlight/$', snippet_highlight, name='snippet-highlight')
])

-------------------------------------------------------------------------------------

Infact all of the above tasks (like defining view function mapping, defining urls) is also automated using the
Router classes. All you do is create a DefaultRouter() instance and register your viewsets with it.

router = DefaultRouter()
router.register(r'snippets', views.SnippetViewSet) # first argument is the prefix name to be used in the url.
router.register(r'users', views.UserViewSet) # also the register function is used to create an api-root view automatically.

urlpatterns = [
    url(r'^', include(router.urls)),
]