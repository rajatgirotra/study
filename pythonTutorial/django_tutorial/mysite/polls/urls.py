from django.urls import path
from . import views

urlpatterns = [
        # ex: polls/
        path('', views.index, name='index'),
        # ex: polls/34/
        path('<int:question_id>/', views.detail, name='detail'),
        # ex: polls/34/results/
        path('<int:question_id>/results/', views.results, name='results'),
        # ex: polls/34/vote/
        path('<int:question_id>/vote/', views.vote, name='vote')
        ]
