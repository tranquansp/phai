# Create your views here.
# Create your views here.
from django.shortcuts import render_to_response
from django.template import RequestContext
from django.http import HttpResponseRedirect
from django.core.urlresolvers import reverse

from myproject.myapp.models import Document
from myproject.myapp.forms import DocumentForm

import ctypes #for call library

def list(request):
    # Handle file upload
    if request.method == 'POST':
        form = DocumentForm(request.POST, request.FILES)
        if form.is_valid():
			#request docfile
            newdoc = Document(docfile = request.FILES['docfile'])
            #save information in database
            newdoc.save()
            libc = ctypes.CDLL("./media/lib/lib.so")
            #call to address library
            #/home/ht/workspace/myproject/src/myproject/media/documents
            libc.transfer_color("./media/documents/rose.jpg","./media/documents/blue.jpg","./media/documents/test.jpg")
            #call function in library
            #document = Document(docfile='documents/tem.jpg')
            #document.save()
            # Redirect to the document list after POST
            return HttpResponseRedirect(reverse('myapp.views.list'))
    else:
        form = DocumentForm() 
    # A empty, unbound form
    # Load documents for the list page
    documents = Document.objects.all()#list image in database
    # Render list page with the documents and the form
    return render_to_response(
        'myapp/list.html',
        {'documents': documents, 'form': form},
        context_instance=RequestContext(request)
    )# return list image
