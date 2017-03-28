# The views here are standard views. We should as much as possible make use of generic views.

from django.shortcuts import render, get_object_or_404
from django.http import HttpResponse, HttpResponseRedirect
from django.views.decorators.http import require_http_methods
from .models import Question, Choice
from django.urls import reverse
# Create your views here.


def index(request):
    # get last 5 questions based on published date.
    # -pub_date means get in descending order.
    last_5_questions = Question.objects.order_by('-pub_date')[0:5]
    context = {
        "questions": last_5_questions
    }
    return render(request, 'polls/index.html', context)


def detail(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    context = {
        'question': question
    }
    return render(request, 'polls/detail.html', context)


def results(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    context = {
        'question': question
    }
    return render(request, 'polls/result.html', context)


@require_http_methods(['POST'])
def vote(request, question_id):
    question = get_object_or_404(Question, pk=question_id)
    user_choice = get_object_or_404(Choice, pk=request.POST['choice'])
    user_choice.votes += 1
    user_choice.save()
    context = {
        'question': question
    }
    return HttpResponseRedirect(reverse('polls:results', kwargs={'question_id': question.id}))


