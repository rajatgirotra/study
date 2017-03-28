# Please read this after going through DRF tutorial 1,2,3,4.

Ok, any REST Framework API should be written if possible in a way that the API itself is discoverable. What this means
is that you should define an API root of your API. and then all responses should have API's embedded within them.

Example: We define the two API's below at the root.

@api_view(['GET'])
def api_root(request, format=None):
    return Response({
        'users': reverse('user-list', request=request, format=format),
        'snippets': reverse('snippet-list', request=request, format=format)
    })
# this FBV returns a dictionary which will be converted to JSON and shown.

So we will just give the following url to anyone:
http://localhost:8000/snippets/api_root.json

After that whenever we have to represent a relationship, like Plan has Target, Target has Environments, Environments
have Servers, Servers have Instances etc.. we can represent these in DRF in the following ways

1) Include the primary key in the response to represent the relationship
2) Use some unique slug field on the related entity. like Target.region on the Target json
3) Use hyperlinking between entities. (recommended)
4) Use default str() or repr() representation of the object instance.
5) Some other custom representation.

All of these are supported depending on the type of Serializer we use. A serializer is way of representing an instance
values

1) ModelSerializer: A model serializer will return you a dictionary representation of ur instance values. It will add
an "id" field. Also any relationship it has (for example, a Target has a Plan Foreign Key), will be represented by the
"id" of that Plan. So it will be like target = {'id': 1, 'region': 'tokyo', 'plan': 6}

2) HyperlinkedModelSerializer: It does not include the "id" attribute by default in the dictionary. It adds a url
key using HyperlinkedIdentityField() instance. Relationships will by default use HyperlinkedRelatedField() instead
of PrimaryKeyRelatedField()

Explore other Serializers yourself.



Also lets say you want to assign a URL to a particular attribute of your model. Let's say snippet has a "highlighted"
attribute which is nothing but HTML text. And you want to display the url of a page to display this HTML in the json
instead of outputting the HTML text. Then you can say

class SnippetSerializer(serializers.ModelSerializer):
    highlight = serializers.HyperlinkedIdentityField(view_name='snippet-highlight', format='html')
    # where snippet-highlight is defined in urls.py