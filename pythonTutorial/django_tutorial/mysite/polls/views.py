from django.shortcuts import render
from django.http import HttpResponse

# Create your views here.
def index(request):
    print(f'request is of type {type(request)}')
    print(f'{request}')
    return HttpResponse("Hello World. You are at the polls index")


def detail(request, question_id):
    return HttpResponse(f"You are looking at question {question_id}")


def results(request, question_id):
    return HttpResponse(f"You are looking at the results of question {question_id}")


def vote(request, question_id):
    return HttpResponse(f"You are voting on question {question_id}")
