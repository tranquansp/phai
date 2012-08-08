from django.db import models
from django.contrib.auth.models import User
# Create your models here.
# python manage.py syncdb 
# create table "Document" for database , 2 columns is id and docfile
class Image(models.Model):
    user = models.ForeignKey(User)	# each image is linked to a user
    # can use ImageField for imgfile, however
	# Python Imaging Lib must be installed
    imgfile = models.FileField(upload_to='documents')
	
	# display username and the path to image when printing 
	# instead of object reference
    def __unicode__(self):
		return (self.user.username, self.imgfile.url)
