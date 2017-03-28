from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, HttpResponseRedirect
from django.urls import reverse
from django.views import generic
from .models import Post
from .forms import PostForm


# Create your views here.
def post_create(request):
    if request.method == "GET":
        # Creating a new empty PostForm
        # form = PostForm()

        # create a new PostForm passing an empty dictionary. When we do this. Django performs field validation based on
        # field definition. and then updates the form html to also include errors from fields and errors on the form
        # as a whole. This are built in validation errors. So this is better, because the first time it is requested,
        # we also display what is required
        # may be just use this information to display a red asterik instead of the error msg.
        form = PostForm(request.POST)

        # if for some reason you don't want to use PostForm(request.POST) for GET also, you can use
        # form = PostForm(request.POST or None)  # ie for GET it will be None, and for POST it will be  request.POST
        # so you don't need if else
        context = {
            "form": form
        }
        return render(request, 'post_form.html', context)
    else:
        # request.POST is a dictionary of filled up form data, so we ask Django to populate the form
        # object with all the data sent by the user.
        form = PostForm(request.POST)
        if form.is_valid():
            instance = form.save(commit=False)  # dont yet commit to DB
            instance.save()  # commit now, so that your model specific save() overrides if any get called. Prefer this
        # separately, you can edit an existing model instance using the form. Like this
        # Eg:
        # a = Post.object.get(pk=2)
        # form = PostForm(None, instance=a)
        # form.save()
        return HttpResponseRedirect(reverse('first-posts:post_list'))


def post_detail(request, pk):
    instance = get_object_or_404(Post, id=pk)
    context = {
        'title': instance.title,
        'instance': instance
    }
    return render(request, 'post_detail.html', context)


def post_list(request):
    queryset = Post.objects.all()
    if request.user.is_authenticated():
        context = {
            "objects_list": queryset,
            "title": "My User List"
        }
    else:
        context = {
            "title": "List"
        }
    return render(request, 'post_list.html', context)


def post_update(request, pk):
    if request.method == "GET":
        instance = get_object_or_404(Post, id=pk)
        form = PostForm(None, instance=instance)
        print form.data.get("title")
        context = {
            'instance': instance,
            'form': form
        }
        return render(request, 'post_update.html', context)
    else:
        instance = get_object_or_404(Post, id=pk)
        form = PostForm(request.POST, instance=instance)
        if form.is_valid():
            instance = form.save(commit=False)
            instance.save()
            return HttpResponseRedirect(reverse('first-posts:post_list'))


def post_delete(request):
    return HttpResponse("<h1>Delete</h1>")