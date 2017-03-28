from __future__ import unicode_literals

from django.db import models
from django.core.urlresolvers import reverse

# Create your models here.
class Post(models.Model):
    title = models.CharField(max_length=200)
    content = models.TextField()
    created = models.DateTimeField(auto_now=False, auto_now_add=True)
    last_updated = models.DateTimeField(auto_now=True, auto_now_add=False)

    def get_content_upper(self):
        return self.content.upper()
    get_content_upper.short_description = 'Detail'

    def get_absolute_url(self):
        return reverse('first-posts:detail', kwargs={"pk": self.id})

    def __unicode__(self):
        return self.title
