# Create your views here.
# Create your views here.
from django.shortcuts import render_to_response
from django.template import RequestContext
from django.http import HttpResponseRedirect, HttpResponse
from django.core.urlresolvers import reverse
from django.template.loader import get_template

from django.contrib.auth.models import User
from django.contrib.auth.views import login
from django.contrib.auth import logout

from myproject.myapp.models import *
from myproject.myapp.forms import *

import ctypes #for call library

notAuthenticatedPage = '''
<html>
	<body>
		<p>User is not authenticated. Please <a href='/'>login</a>
	</body>
</html>
'''
# user_page takes 2 argument, request and username as a string
def user_page(request, username):
	if(request.user.is_authenticated()):
		# get the list of images that are belonged to username
		# log_in_user = User.objects.get(username=username)
		images_list = Image.objects.filter(user=request.user)
		return render_to_response('myapp/user_page.html',
							{'user':request.user, 'images_list':images_list},
							context_instance = RequestContext(request)
						)
	else:
		return HttpResponse(notAuthenticatedPage)
	
def upload_page(request, username):
    # Handle file upload
	if(request.user.is_authenticated()):
		if request.method == 'POST':
			form = ImageForm(request.POST, request.FILES)
			if form.is_valid():
				#request docfile
					newimg = Image( user = request.user,
								imgfile = request.FILES['imgfile']
							)
            		#save information in database
					newimg.save()
            		# libc = ctypes.CDLL("./media/lib/lib.so")
            		#call to address library
            		#/home/ht/workspace/myproject/src/myproject/media/documents
            		# libc.transfer_color("./media/documents/rose.jpg","./media/documents/blue.jpg","./media/documents/test.jpg")
            		# Redirect to the document list after POST
					
					# since user_page takes 2 arguments, reverse() needs to pass username to args field
					return HttpResponseRedirect(reverse('myapp.views.user_page', args=[username]))
		else:
			form = ImageForm()
	
		return render_to_response('myapp/upload.html',
									{'user':request.user, 'form':form},
									context_instance = RequestContext(request)
								)
	else:
		return HttpResponse(notAuthenticatedPage)								
						
def login_page(request):
	if(request.user.is_authenticated()):
		return HttpResponseRedirect('/user/%s' % request.user.username)
	else:
		return login(request)	# Redirect to django.contrib.auth.views.login
	
def logout_page(request):
	if(request.user.is_authenticated()):
		logout(request)
		return HttpResponse('USER LOG OUT SUCCESSFUL')
	else:
		return HttpResponseRedirect('/')

def registration(request):
	if(request.method == 'POST'):
		user_reg_form = UsernameForm(request.POST)
		pw_reg_form = PasswordForm(request.POST)	
		if(user_reg_form.is_valid() and pw_reg_form.is_valid()):
			User.objects.create_user(
					# Django provides some input validation for each field.
					# Inputs that are validated are stored in form.cleaned_data 
					# as a dict, while raw inputs are stored in form.data 
						username = user_reg_form.cleaned_data['username'],
						password = pw_reg_form.cleaned_data['password'],
						email = user_reg_form.cleaned_data['email']
					)
			return HttpResponse('SIGNUP SUCCEEDED')
	else:
		user_reg_form = UsernameForm()
		pw_reg_form = PasswordForm()
	return render_to_response(
			'registration/registration.html',
			{'user_reg_form':user_reg_form,
			 'pw_reg_form':pw_reg_form},
			context_instance=RequestContext(request)
		)

def change_password(request, username):
	if(request.user.is_authenticated()):
		if(request.method == 'POST'):
			pw_form = PasswordForm(request.POST)
			if(pw_form.is_valid()):
				request.user.set_password(pw_form.cleaned_data['password'])
				request.user.save()
				return HttpResponse('PASSWORD CHANGED')
		else:
			pw_form = PasswordForm()
		return render_to_response('myapp/change_password.html',
									{'pw_form':pw_form},
									context_instance=RequestContext(request)
								)
	else:
		return HttpResponse(notAuthenticatedPage)
