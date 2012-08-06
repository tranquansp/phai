from django.conf.urls.defaults import patterns, url
# Address for the web site , example 127.0.0.1:8000/list/
urlpatterns = patterns('myapp.views',
    url(r'^list/$', 'list', name='list'),
	# main page is login page
    # (r'^$', 'django.contrib.auth.views.login')
	#url(r'^process/$', 'process', name='process'),
)
