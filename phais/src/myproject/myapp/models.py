from django.db import models

# Create your models here.
# python manage.py syncdb 
# create table "Document" for database , 2 columns is id and docfile
class Document(models.Model):
    docfile = models.FileField(upload_to='documents')
