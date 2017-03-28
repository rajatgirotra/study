import datetime
from django.test import TestCase
from django.utils import timezone
from .models import Question, Choice
from django.urls import reverse


# Create your tests here.
class QuestionMethodTests(TestCase):
    def test_was_published_recently_with_future_question(self):
        """ was_published_recently should return False if published date is in the future. """
        time = timezone.now() + datetime.timedelta(days=10)
        # create a Question with pub_date in the future
        q = Question(question_text='Are we in future??', pub_date=time)
        self.assertIs(q.was_published_recently(), False)

    def test_was_published_recently_with_old_question(self):
        """ was_published_recently should return False if published date is more than one day old. """
        time = timezone.now() - datetime.timedelta(days=2)
        # create a Question with pub_date in the past
        q = Question(question_text='Are we in future??', pub_date=time)
        self.assertIs(q.was_published_recently(), False)

    def test_was_published_recently_with_recent_question(self):
        """ was_published_recently should return True if published date is previous day. """
        time = timezone.now() - datetime.timedelta(hours=23)
        # create a Question with pub_date as one day old.
        q = Question(question_text='Are we in future??', pub_date=time)
        self.assertIs(q.was_published_recently(), True)

    def test_was_published_recently_with_today_question(self):
        """ was_published_recently should return True if published date is today. """
        time = timezone.now()
        # create a Question with pub_date today.
        q = Question(question_text='Are we in future??', pub_date=time)
        self.assertIs(q.was_published_recently(), True)


def create_question(question_text, days):
    """ Creates and returns a Question instance with the question_text and pub_date = now()+days. """
    time = timezone.now() + datetime.timedelta(days=days)
    # Question will also be persisted.
    return Question.objects.create(question_text=question_text, pub_date=time)


class QuestionIndexViewTests(TestCase):
    def test_index_view_with_no_questions(self):
        """ If no questions exist, an appropriate message should be displayed. """
        response = self.client.get(reverse('polls:index'))
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, "No polls available.")
        self.assertQuerysetEqual(response.context['questions'], [])

    def test_index_view_with_past_questions(self):
        """ If questions exist with pub_date in the past, they should be visible in the view. """
        time = timezone.now()
        create_question('Question_1', -5)
        create_question('Question_2', -1)
        response = self.client.get(reverse('polls:index'))
        self.assertEqual(response.status_code, 200)
        self.assertQuerysetEqual(response.context['questions'], ['<Question: Question_2>', '<Question: Question_1>'])

    def test_index_view_with_future_questions(self):
        """ If questions exist with pub_date in the future, they should NOT be visible in the view. """
        time = timezone.now()
        create_question('Question_1', 5)
        create_question('Question_2', 1)
        response = self.client.get(reverse('polls:index'))
        self.assertEqual(response.status_code, 200)
        self.assertQuerysetEqual(response.context['questions'], [])


class QuestionDetailViewTests(TestCase):
    def test_detail_view_with_future_questions(self):
        """ A question in the future should not be visible on this view."""
        future_question = create_question('Question_1', 5)
        response = self.client.get(reverse('polls:detail', kwargs={'pk': future_question.id}))
        self.assertEqual(response.status_code, 404)

    def test_detail_view_with_past_questions(self):
        """ A question in the future should not be visible on this view."""
        past_question = create_question('Question_1', -5)
        response = self.client.get(reverse('polls:detail', kwargs={'pk': past_question.id}))
        self.assertEqual(response.status_code, 200)
        self.assertContains(response, past_question.question_text)
