from django.conf.urls.defaults import patterns, url
from django.contrib.auth.views import login
# Address for the web site , example 127.0.0.1:8000/list/
urlpatterns = patterns('myapp.views',
    #url(r'^list/$', 'list', name='list'),
	url(r'^register/$', 'registration', name='registration'),
	url(r'^user/(\w+)/$', 'user_page', name='user_page'),
	url(r'^user/(\w+)/upload$', 'upload_page', name='upload_page'),
	url(r'^logout/$', 'logout_page', name='logout_page'),
	#url(r'^process/$', 'process', name='process'),
)
