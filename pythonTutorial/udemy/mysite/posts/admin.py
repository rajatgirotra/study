from django.contrib import admin

# Register your models here.
from .models import Post


# when a field in model is None or an iterable field has size 0, use 'None'
# can also override this on per Model basis or a per field basis
admin.site.empty_value_display = 'None'


def get_last_updated(obj):
    # obj will be a model instance
    return obj.last_updated
    # short_description is used to provide your own heading for a column
get_last_updated.short_description = 'Last Updated'


@admin.register(Post)
class PostAdmin(admin.ModelAdmin):
    # date_hierarchy means the admin site will include a drill down navigation by that field.
    date_hierarchy = 'last_updated'

    # the list display is a tuple which tells what columns to display from the model. list display can be either a
    # field name from your model, a callable, a string representing an attribute from your ModelAdmin or a string
    # representing an attribute on the model. By default, list display is set to __str__ which means you should
    # provide an __str__ for your model class always. Can also be html if you want. Read online ModelAdmin
    # documentation for more.
    list_display = ('title', get_last_updated, 'get_created', 'get_content_upper')

    def get_created(self, obj):
        return obj.created
    get_created.short_description = 'Created On'

    # means which columns should be clickable. Again a tuple
    list_display_links = (get_last_updated, 'get_content_upper')

    # if you provide to want filter one or more columns. Filters appear on the right hand sidebar
    # More complex user defined filters can also be provided by subclassing a SimpleListFilter. See documentation.
    list_filter = ('title', 'last_updated')

    # fields which will be editable in the changelist
    list_editable = ('title',)

    # fields on the basis of which you can search for posts
    search_fields = ('title', 'content')
    # and many other filters
