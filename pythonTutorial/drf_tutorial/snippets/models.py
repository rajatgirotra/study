from __future__ import unicode_literals

from django.db import models
from django.shortcuts import reverse
from pygments.lexers import get_all_lexers
from pygments.styles import get_all_styles
from pygments.lexers import get_lexer_by_name
from pygments.formatters.html import HtmlFormatter
from pygments import highlight
# Create your models here.


LEXERS = [item for item in get_all_lexers() if item[1]]
LANGUAGE_CHOICES = sorted([(item[1][0], item[0]) for item in LEXERS])
STYLE_CHOICES = sorted((item, item) for item in get_all_styles())


# Create a model of Snippets
class Snippet(models.Model):
    created = models.DateTimeField(auto_now_add=True)
    title = models.CharField(max_length=100, default='', blank=True)
    code = models.TextField()
    linenos = models.BooleanField(default=False)
    language = models.CharField(choices=LANGUAGE_CHOICES, default='python', max_length=100)
    style = models.CharField(choices=STYLE_CHOICES, default='friendly', max_length=100)
    owner = models.ForeignKey('auth.User', related_name='snippets', on_delete=models.CASCADE)
    highlighted = models.TextField()

    class Meta:
        ordering = ('-created',)  # order by created. Most recent first

    def __unicode__(self):
        return 'snippet %s created on %s' % (self.title, self.created)

    def __str__(self):
        return self.__unicode__()

    # ignore the save() function as of now.
    def save(self, *args, **kwargs):
        """
           Use the `pygments` library to create a highlighted HTML
           representation of the code snippet.
           """
        lexer = get_lexer_by_name(self.language)
        linenos = self.linenos and 'table' or False
        options = self.title and {'title': self.title} or {}
        formatter = HtmlFormatter(style=self.style, linenos=linenos,
                                  full=True, **options)
        self.highlighted = highlight(self.code, lexer, formatter)
        print self.highlighted
        super(Snippet, self).save(*args, **kwargs)

    def get_absolute_url(self):
        return reverse('snippets:detail', kwargs={'pk': self.id})
# Lets read serializers.py next
