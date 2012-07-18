#include <stdio.h> 
#include <stdlib.h> 
#include <dlfcn.h> 
#include <string.h>
int main(int argc,char **argv) 
{ 
	if(!strcmp(argv[1],"--h"))
	{
		printf("Transfer Color Library  \n");
		printf("Version: TransColor beta http://www.code.google.com/p/phai \n");
		printf("Copyright : MHST12  \n");
		printf("Develope from ImageMagick 6.5.7-8 2012-04-30 Q16 http://www.imagemagick.org  \n");
		printf("Usage: ./phai.bin filename1 filename2 \n");
		printf("-------------------------------------- \n");
		printf("Description : \n");
		printf("filename1 : Source image \n");
		printf("filename2 : Target image \n");
		return 0;
	}
	void * my_lib_handle;
	int (*some_func)(char *,char *); 
	my_lib_handle = dlopen("./transferlib.so",RTLD_NOW); 
	if(my_lib_handle==NULL) { 
	printf("Error loading library\n"); 
	exit(-1); 
	} 
	some_func = (int (*)(char*,char*)) dlsym(my_lib_handle,"transfer_color"); 
	if(some_func==NULL) { 
	printf("Error loading transfer function \n"); 
	exit(-1); 
	} 
	printf("loading ...\n",(*some_func)(argv[1],argv[2])); 
	return 0; 
} 
  
