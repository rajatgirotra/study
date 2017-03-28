from django.conf.urls import include, url
from django.conf import settings
from django.conf.urls.static import static

from . import views

urlpatterns = [
    url('^$', views.post_list, name='post_list'),
    url('^create/$', views.post_create, name='post_create'),
    url('^(?P<pk>\d+)/edit/$', views.post_update, name='post_update'),
    url('^delete/$', views.post_delete, name='post_delete'),
    url('^(?P<pk>\d+)/$', views.post_detail, name='detail')
 ]

if settings.DEBUG:
    urlpatterns += static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)
