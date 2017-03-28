from __future__ import unicode_literals

from django.db import models
from django.urls import reverse
from django.utils import timezone
from datetime import timedelta


# Create your models here.
class Question(models.Model):
    question_text = models.CharField(max_length=50)
    # The string argument will be visible in the Admin site. If no argument passed, admin site will show "Pub date"
    # So for question_text field, it will show "Question text"
    pub_date = models.DateTimeField('published on')

    def __unicode__(self):
        return "%s" % self.question_text

    def __str__(self):
        return self.__unicode__()

    def was_published_recently(self):
        yesterday = timezone.now() - timedelta(days=1)
        return yesterday <= self.pub_date <= timezone.now()
    # Marking as boolean will show a red cross mark or a green right mark in the admin page
    was_published_recently.boolean = True
    # Column name to use in the admin page
    was_published_recently.short_description = 'Published recently?'
    # Django does all sorting at the database level. So in the admin page, you will not be able to sort based on this
    # field, as this field is not in the database. You can however enable sorting on this column by piggybacking on some
    # database field, in this case on pub_date by using the admin_order_field
    was_published_recently.admin_order_field = 'pub_date'

    def get_absolute_url(self):
        return reverse('polls:detail', kwargs={'pk': self.id})


class Choice(models.Model):
    question = models.ForeignKey(Question, on_delete=models.CASCADE)
    choice_text = models.CharField(max_length=100)
    votes = models.IntegerField(default=0)

    def __unicode__(self):
        return "%s" % self.choice_text

    def __str__(self):
        return self.__unicode__()