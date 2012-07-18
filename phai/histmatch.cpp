//============================================================================
// Name        : exe_im.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

// This may look like C code, but it is really -*- C++ -*-
//
// Copyright Bob Friesenhahn, 2003
//
// Test STL colorHistogram function
//

#undef USE_VECTOR
#define USE_MAP

#include <Magick++.h>
#include <string>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#if defined(USE_VECTOR)
#  include <vector>
#  include <utility>
#endif
#if defined(USE_MAP)
#  include <map>
#endif

using namespace std;

using namespace Magick;
extern "C" int transfer_color(char *argv1,char *argv2)
{

  // Initialize ImageMagick install location for Windows
  InitializeMagick("lmagick");

  int failures=0;

  try {

    string srcdir("");
    if(getenv("SRCDIR") != 0)
      srcdir = getenv("SRCDIR");

    // Read image
    Image image;
    image.read( srcdir + argv2 );

    // Create histogram vector
#if defined(USE_MAP)
    std::map<Color,size_t> histogram;
#elif defined(USE_VECTOR)
    std::vector<std::pair<Color,size_t> > histogram;
#endif

    colorHistogram( &histogram, image );

    // Print out histogram
#if (MAGICKCORE_QUANTUM_DEPTH == 8)
    int quantum_width=3;
#elif (MAGICKCORE_QUANTUM_DEPTH == 16)
    int quantum_width=5;
#else
    int quantum_width=10;
#endif

    cout << "Histogram for file \"" << image.fileName() << "\"" << endl
         << histogram.size() << " entries:" << endl;
    int size = histogram.size();
#if defined(USE_MAP)
    std::map<Color,size_t>::const_iterator p=histogram.begin();
#elif defined(USE_VECTOR)
    std::vector<std::pair<Color,size_t> >::const_iterator p=histogram.begin();
#endif
    size_t max=0,x=0,y=0,z=0;
    int ends = (int)(size-size*0.2);
    int begins = (int)(size * 0.2);
     for(int foo=begins;foo < ends;foo++)//p != histogram.end())
      {
      /*cout << setw(2) << (int)p->second << ": ("
             << setw(quantum_width) << (int)p->first.redQuantum() << ","
             << setw(quantum_width) << (int)p->first.greenQuantum() << ","
             << setw(quantum_width) << (int)p->first.blueQuantum() << ")"
             << endl;*/
        if( ((int)p->second) > max )
		{
			max = (int)p->second;
			x = (int)p->first.redQuantum() / 257;
			y = (int)p->first.greenQuantum() / 257;
			z = (int)p->first.blueQuantum() / 257;
		}
        p++;
      }
     cout << "so mau lon nhat la : " << max << endl << x << endl << y << endl << z << endl;

     char str[100];
     //strcpy (str,"./convert rose.png +level-colors 'rgb(");

     char integer_string[32];
     char other_string[64] = "convert ";
     strcat(other_string, argv1); // anh can chuyen doi
     strcat(other_string," +level-colors 'rgb(");

     //argv[1];
     sprintf(integer_string, "%d", x);
     strcat(other_string, integer_string);
     strcat(other_string, ",");
     sprintf(integer_string, "%d", y);
     strcat(other_string, integer_string);
     strcat(other_string, ",");
     sprintf(integer_string, "%d", z);
     strcat(other_string, integer_string);
     strcat(other_string, ",");

     strcat(other_string, ")', temp.png");
     system(other_string);
     cout << 	other_string  << endl;
     cout << "hoan thanh viec chuyen doi .. " << endl ;

  }

  catch( Exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }
  catch( exception &error_ )
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }

  if ( failures )
    {
      cout << failures << " failures" << endl;
      return 1;
    }

  return 0;
}



