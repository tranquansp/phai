# -*- coding: utf-8 -*-
from django import forms
from django.contrib.auth.models import User
import re	# regular expression for input validation
# create a notification
class ImageForm(forms.Form):
    # can use ImageField for imgfile, however
	# Python Imaging Lib must be installed
    imgfile = forms.FileField(
        label='Select a file',
        help_text='max. 42 megabytes'
    )


# All custom validation methods used in a form 
# must have the format clean_[fieldname]

class UsernameForm(forms.Form):
	username = forms.CharField(label='Username:')
	email = forms.EmailField(label='Email (Optional):',
							required = False)
	# Username Validation
	# This method checks if the username is existed.
	# More validation should be implemented:
	# 	- makes sure the username only contains
	#	alphanumeric chars and underscore
	# 	- username should contain at least 
	#	1 alphabet char.

	def clean_username(self):
		username = self.cleaned_data['username']
		try:
			User.objects.get(username=username)
		except User.DoesNotExist:
			return username
		# return error if username is existed
		raise forms.ValidationError('Username is already taken.')

class PasswordForm(forms.Form):
	password = forms.CharField(label='Password:',
								widget = forms.PasswordInput())
	retyped_password = forms.CharField(label="Retype your password:",
										widget = forms.PasswordInput())

	# Password Validation
	# Check if retyped password matches initial password
	def clean_retyped_password(self):
		password = self.cleaned_data['password']
		if(len(password) > 0):
			retyped_password = self.cleaned_data['retyped_password']
			if(password == retyped_password):
				return password
			raise forms.ValidationError('Passwords does not match.')
		else:
			raise forms.ValidationError('Password field is empty.')
