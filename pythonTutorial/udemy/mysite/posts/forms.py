from django import forms
from .models import Post


class PostForm(forms.ModelForm):
    class Meta:
        # tell django which model you are using
        model = Post
        # tell django which fields out of the Post model you are using
        fields = [
            'title',
            'content'
        ]