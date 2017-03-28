from django.shortcuts import render, get_object_or_404
from django.views import generic
from django.http import HttpResponseRedirect, HttpResponse
from django.views.decorators.http import require_http_methods
from django.urls import reverse
from django.utils import timezone

from .models import Question, Choice


# Use generic views. Generic views are class based views defined by Django.
class IndexView(generic.ListView):
    template_name = 'polls/index.html'
    context_object_name = 'questions'  # the context variable name which will be provided in the template.

    def get_queryset(self):
        """ return the last five published questions"""
        return Question.objects.filter(pub_date__lte=timezone.now()).order_by('-pub_date')[:5]
        #return Question.objects.order_by('-pub_date')[:5]


# generic.DetailView view will get the Question instance automatically
# DetailView expects a primary key which must be given by the "pk" argument in the URL.
class DetailView(generic.DetailView):
    template_name = 'polls/detail.html'
    model = Question

    def get_queryset(self):
        # This filter will be applied to the record fetched using the pk. If filter fails, then a 404 is thrown
        # automatically.
        return Question.objects.filter(pub_date__lte=timezone.now())


class ResultView(generic.DetailView):
    template_name = 'polls/result.html'
    model = Question


@require_http_methods(['POST'])
def vote(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    context = {
        'question': question
    }
    try:
        user_choice = Choice.objects.get(pk=request.POST['choice'])
    except (KeyError, Choice.DoesNotExist):
        context['error_message'] = 'You did not vote!!'
        return render(request, 'polls/detail.html', context)
    else:
        user_choice.votes += 1
        user_choice.save()
    return HttpResponseRedirect(reverse('polls:results', kwargs={'pk': question.id}))
