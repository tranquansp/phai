/*
 * histMatch.h
 *
 *  Created on: Jul 25, 2012
 *      Author: quanrock
 */

#ifndef HISTMATCH_H_
#define HISTMATCH_H_

/*
 *******************************************************************************
 * 																			   *
 *          TTTTTTT  RRRR       A     N    N   SSSS FFFFF EEEEE RRRR           *
 *             T     R   R     A A    N N  N  S     F     E     R   R          *
 *             T     RRRR     AAAAA   N   NN   SSS  FFFF  EEEE  RRRR           *
 *             T     R   R   A     A  N    N      S F     E     R   R          *
 *             T	 R    R A       A N    N  SSSS  F     EEEEE R    R         *
 *             																   *
 *             																   *
 *   			Transfer an inage by color style from another one			   *
 *   			 Method : histogram analysis and convert contract        	   *
 *   							Tran Quan									   *
 *   																		   *
 *   							July 2012									   *
 *******************************************************************************
 */
//==============================================================================
// Name        : hismatch.cpp
// Author      : tran quan
// Version     : beta
// Copyright   :
// Description : Hitogram matching in C++, Ansi-style
//============================================================================

// This may look like C code, but it is really C++ code
// This header provide a function to transfer color from source image and target image

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
extern "C" int transfer_color(char *argv1,char *argv2,char *argv3)
{
	// Parameter 1 is target image.It 's orginal image using for transfering to result image
	// Parameter 2 is a source image.It 's stylist image using for getting color style
	// Parameter 3 is a result image !!!

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
     for(int foo=begins;foo < ends;foo++)
      {
        if( ((int)p->second) > max )
		{
			max = (int)p->second;
			x = (int)p->first.redQuantum() ;
			y = (int)p->first.greenQuantum();
			z = (int)p->first.blueQuantum() ;
		}
        p++;
      }

     /*
      * The most numbers of color is get from histogram
      * This is a important color to transfer
      * RGB(x/257,y/257,z/257)
      *
      * */

     char str[100];

     char integer_string[32];
     char other_string[64] = "convert ";
     strcat(other_string, argv1); // argv1 is a target image
     strcat(other_string," +level-colors 'rgb(");

     //argv[1];
     sprintf(integer_string, "%d", x/ 257);
     strcat(other_string, integer_string);
     strcat(other_string, ",");
     sprintf(integer_string, "%d", y / 257);
     strcat(other_string, integer_string);
     strcat(other_string, ",");
     sprintf(integer_string, "%d", z / 257);
     strcat(other_string, integer_string);
     strcat(other_string, ",");

     strcat(other_string, ")', ");
     strcat(other_string,argv3); //argv3 is a result image

     system(other_string);
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


#endif /* HISTMATCH_H_ */
