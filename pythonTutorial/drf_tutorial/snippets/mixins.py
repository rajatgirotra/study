from django.http import JsonResponse
from django.views.generic import ListView
from .serializers import Snippet, SnippetSerializer


class JSonResponseMixin(object):
    """ A mixin that can be used to render Json responses. """

    def render_to_json_response(self, context, **response_kwargs):
        """ Convert context to json string. """
        return JsonResponse(self.get_data(context), safe=False, **response_kwargs)

    def get_data(self, context):
        """ do serialization here. """
        return context


# ListView inherits from MultipleObjectTemplateResponseMixin which derives from TemplateResponseMixin
# You already know TemplateResponseMixin defines "get_template_names()" and "render_to_response()".
# MultipleObjectTemplateResponseMixin overrides "get_template_names()" to provide multiple templates
# names, however, it may never be called if render_to_response() is overriden. Like in our case.
class JsonView(JSonResponseMixin, ListView):
    def render_to_response(self, context, **response_kwargs):
        return self.render_to_json_response(context, **response_kwargs)
