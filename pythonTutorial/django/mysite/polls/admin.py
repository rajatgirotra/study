from django.contrib import admin

from .models import Question, Choice


# class ChoiceInline(admin.StackedInline):
class ChoiceInline(admin.TabularInline):
    model = Choice  # The model name
    extra = 3  # How many choices to show inline


# Register your models here.
@admin.register(Question)
class QuestionAdmin(admin.ModelAdmin):

    # fields to be displayed on the edit page in order
    # fields = ('pub_date', 'question_text',)
    # Use fieldsets to better organize fields on the edit page. fields and fieldsets are mutually exclusive
    # Is a list of tuples. First item in a tuple is the name of the field set (can be None also)
    # second item is a dictionary of attributes
    fieldsets = [
        (None, {'fields': ['question_text']}),
        ('Date information', {'fields': ['pub_date'], 'classes': ['collapse']})
    ]
    # classes = collapse means collapse the fieldset on the page.

    # Also We can either register Choice Model with Admin separately, as shown below
    # or it makes more sense to add Choices whenever we add a new question. So you can tell admin to choices inline
    # for that we don't need to register Choice Model with Admin separately
    inlines = (ChoiceInline,)

    # What fields will be displayed on the admin home page
    # default is modelInstance.str() string
    list_display = ('get_question', 'pub_date', 'was_published_recently')

    def get_pub_date(self, obj):
        return obj.pub_date
    get_pub_date.short_description = 'Published On'

    def get_question(self, obj):
        return obj.question_text;
    get_question.short_description = 'Question'

    list_display_links = ('get_question',)
    list_filter = ('pub_date',)
    search_fields = ('question_text',)
    site_header = 'Polls Administration'
    site_title = 'Polls Admin'

# @admin.register(Choice)
# class ChoiceAdmin(admin.ModelAdmin):
#     pass


# Apart from modifying the Admin attributes above, there are two ways in which you can further customize the look and feel
# of the admin site
# 1) You override the admin templates and provide your own templates
# 2) You use the admin templates but override the default admin context data.