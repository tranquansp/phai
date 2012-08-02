//============================================================================
// Name        : transfer_color.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
// By tran quan
// tranquansp@gmail.com




#include <iostream>
#include <stdlib.h>
#include <Magick++.h>
#include <list>

#include "histMatch.h"
#include "srcMat.h"
#include "tgtMat.h"
#include "Mat_Display.h"

using namespace Magick;
using namespace std;

extern "C" int trans(char *argv1,char *argv2,char *argv3){
	if(!strcmp(argv1,"--help"))
	{
		cout << "Transfer Color Library  \n";
		cout << "Version: TransColor beta http://www.code.google.com/p/phai \n";
		cout << "Copyright : MHST12  \n";
		cout << "Develope from ImageMagick 6.5.7-8 2012-04-30 Q16 http://www.imagemagick.org  \n";
		cout << "Usage: ./phai.bin [+/-H][-t][-o option] filename1 filename2 filename3 \n";
		cout << "-------------------------------------- \n";
		cout << "Description : \n";
		cout << "Option : \n";
		cout << "+H  :  Increase level constract image " << endl;
		cout << "+H  :  Descrease level constract image " << endl;
		cout << "-t  :  Transfer color image on RGB space " << endl;
		cout << "-o  :  Image Effect include :" << endl;
		cout << "-blur" << endl;
		cout << "-backgroundcolor" << endl;
		cout << "-border" << endl;
		cout << "-gray" << endl;
		cout << "filename1 : Source image \n";
		cout << "filename2 : Target image \n";
		cout << "filename2 : Result image \n";
		return 0;
	}

	if(!strcmp(argv1,"+H"))
	{
		/*
		//Phuong phap histogram Matching :
		*/
		transfer_color(argv1,argv2,argv3);
		cout << "match successfully" ;
		return 0;
	}
	if(!strcmp(argv1,"-t"))
	{
	//
	// I = Tsrc ·Rsrc ·Ssrc ·Stgt ·Rtgt ·Ttgt ·Itgt
	// I is a result Image
	// Itgt is a target Image
	// Tsrc ·Rsrc ·Ssrc ·Stgt ·Rtgt ·Ttgt is rotation matrix
	// I = (R,G,B,1)
	// Itgt = (R,G,B,1)^T
	//

	double srcMat[4][4],tgtMat[4][4],Tsrc[4][4],Rsrc[4][4],Ssrc[4][4],Ttgt[4][4],Rtgt[4][4],Stgt[4][4];
	double resultSRC[4][4],resultTGT[4][4],resultMul[4][4];

	// Get Tsrc ·Rsrc ·Ssrc from Source Image
	getSrcInfo(resultSRC,Tsrc,Rsrc,Ssrc,argv1);

	// Get Stgt ·Rtgt ·Ttgt from Target Image
	getTgtInfo(resultTGT,Ttgt,Rtgt,Stgt,argv2);

	getMatinfo(Tsrc);
	getMatinfo(Rsrc);
	getMatinfo(Ssrc);
	getMatinfo(Ttgt);
	getMatinfo(Rtgt);
	getMatinfo(Stgt);
	getMatinfo(resultSRC);
	getMatinfo(resultTGT);

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			for(int k=0;k<4;k++)
			{
				resultMul[i][j] += resultSRC[i][k] * resultTGT[k][j];
			}
		}
	}
	int foo=0,bar=0;
	resultMul[3][0] = 0;
	resultMul[3][1] = 0;
	resultMul[3][2] = 0;
	resultMul[3][3] = 1;

	// Result of MulMat Tsrc ·Rsrc ·Ssrc ·Stgt ·Rtgt ·Ttgt
	getMatinfo(resultMul);
	Image img("target.png");

	Geometry k;
	k= img.size();
	int height = k.height();
	int width = k.width();

	Image image( Geometry(width,height),Color("white"));
	image.strokeWidth(1);

	// Itgt
	/*
	 *
	----------------------
	 R1    G1 	B1		1
	 R2    G2 	B2		1
	 R3    G3 	B3		1
	 .		.	.		.
	 .		.	.		.
	 Rmxn Gmxn Bmxn	    1
	----------------------
	 *
	 * */

	//I
	/*
	 * | R1	R2  ... Rmxn |
	 * | G1	G2	... Gmxn |
	 * | B1	B2	... Bmxn |
	 * | 1	1	...	  1	 |
	 *
	 * */

	double R,G,B,Rnew,Gnew,Bnew;
	for(int foo=0;foo < width;foo++ )
	{
		for(int bar = 0;bar < height;bar++)
		{
			ColorRGB rgb(img.pixelColor(foo, bar));
			R = rgb.red();
			G = rgb.green();
			B = rgb.blue();

			Rnew = resultMul[0][0]*R + resultMul[0][1]*G + resultMul[0][2]*B + resultMul[0][3];
			Gnew = resultMul[1][0]*R + resultMul[1][1]*G + resultMul[1][2]*B + resultMul[1][3];
			Bnew = resultMul[2][0]*R + resultMul[2][1]*G + resultMul[2][2]*B + resultMul[2][3];

			Color c = ColorRGB(Rnew,Gnew,Bnew);
			image.pixelColor( foo, bar, c);

		}
	}
	image.write(argv3);
	return 0;
	}


	return 0;
}
