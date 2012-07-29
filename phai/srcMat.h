/*
 * srcMat.h
 *
 *  Created on: Jul 25, 2012
 *      Author: quanrock
 */

#ifndef SRCMAT_H_
#define SRCMAT_H_

#include "svd.h"
#include <Magick++.h>


#define M 3
#define N 3
#define LDA M
#define LDU M
#define LDVT N

using namespace Magick;
using namespace std;

int getSrcInfo(double temp2[4][4],double Tsrc[4][4],double Rsrc[4][4],double Ssrc[4][4],char* filename)
{
	try {
		InitializeMagick("Magick++");
		Image img(filename);

		//Image imgtgt("pixel.jpg");

		// pos(x,y)   x: width   y :height
		// 1 1 1 => white
		// 0 0 0 => black

		Geometry k;
		k= img.size();
		int height = k.height();
		int width = k.width();
		double meanR,meanG,meanB;

		for(int foo=0;foo < height;foo++ )
		{
			for(int bar = 0;bar < width;bar++)
			{
				ColorRGB rgb(img.pixelColor(foo, bar));
				meanR += rgb.red();
				meanG += rgb.green();
				meanB += rgb.blue();
			}
		}
		// calculate mean of r g b
		meanR = meanR/(height*width);
		meanG = meanG/(height*width);
		meanB = meanB/(height*width);

		// calculate variance of each of pixel with mean
		int pxlTotal = height*width;
		double var[pxlTotal][3];
		double varTrans[3][pxlTotal];

		// variance = ri- rs
		int h,w;
		for(int i=0;i<pxlTotal;i++)
		{
			h = i / height;
			w = i - h*height;
			ColorRGB rgb(img.pixelColor(h, w));
			var[i][0] = rgb.red() - meanR;
			var[i][1] = rgb.green() - meanG;
			var[i][2] = rgb.blue() - meanB;
		}

		// Result is a matrix with MxN x MxN
		// calculate covariance matrix [3x3]

        double CovMat[LDA*N];
        for(int i=0;i<pxlTotal;i++)
        {
        	CovMat[0] += var[i][0]*var[i][0]; // cov(R,R)
        	CovMat[1] += var[i][0]*var[i][1]; // cov(R,G)
        	CovMat[2] += var[i][0]*var[i][2]; // cov(R,B)

        	CovMat[3] += var[i][1]*var[i][0]; // cov(G,R)
        	CovMat[4] += var[i][1]*var[i][1]; // cov(G,G)
        	CovMat[5] += var[i][1]*var[i][2]; // cov(G,B)

        	CovMat[6] += var[i][2]*var[i][0]; // cov(B,R)
        	CovMat[7] += var[i][2]*var[i][1]; // cov(B,G)
        	CovMat[8] += var[i][2]*var[i][2]; // cov(B,B)
        }

        for(int i=0;i<9;i++)
        {
        	CovMat[i] = CovMat[i]/pxlTotal;
        	//Result of covariance
        }

        // SVD
        //

        int m = M, n = N, lda = LDA, ldu = LDU, ldvt = LDVT, info, lwork;
        double wkopt;
        double* work;
        /* Local arrays */
        double s[N], u[LDU*M], vt[LDVT*N];

        /* Executable statements */
        cout << "Phan Tich SVD cho ma tran Covariance ...." << endl << endl;
        /* Query and allocate the optimal workspace */
        lwork = -1;
        dgesvd( "All", "All", &m, &n, CovMat, &lda, s, u, &ldu, vt, &ldvt, &wkopt, &lwork,
         &info );
        lwork = (int)wkopt;
        work = (double*)malloc( lwork*sizeof(double) );
        /* Compute SVD */
        dgesvd( "All", "All", &m, &n, CovMat, &lda, s, u, &ldu, vt, &ldvt, work, &lwork,
         &info );
        /* Check for convergence */
        if( info > 0 ) {
                cout << "Loi phan tich SVD ...." << endl;
                return 0;
        }

        /* Free workspace */
        free( (void*)work );

        //Calculate Tsrc?

        for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(i==j)
				{
					Tsrc[i][j] = 1;
				}
				else Tsrc[i][j] = 0;
			}
		}
        Tsrc[0][3] = meanR;
        Tsrc[1][3] = meanG;
        Tsrc[2][3] = meanB;
        /*
         *
         1 0 0 meanR
         0 1 0 meanG
         0 0 1 meanB
         0 0 0 	 1
         *
         * */

		//tinh Rsrc

		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				Rsrc[i][j] = 0;
			}
		}
		Rsrc[3][3] = 1;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Rsrc[j][i] = u[i*3+j];
			}
		}

		/*
		 *
		 Rsrc = (Usrc,1)
		 *
		 * */

		// calculate Ssrc
		/*
		 *
		 s[0]	0		0	0
		  0	   s[1]		0	0
		  0		0  	   s[2]	0
		  0		0		0 	1
		 *
		 * */
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				Ssrc[i][j] = 0;
			}
		}
		Ssrc[0][0] = s[0];
		Ssrc[1][1] = s[1];
		Ssrc[2][2] = s[2];
		Ssrc[3][3] = 1;

		double temp[4][4];

		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					 temp[i][j] += Tsrc[i][k] * Rsrc[k][j];
				}
			}
		}

		temp[3][0] = 0;
		temp[3][1] = 0;
		temp[3][2] = 0;

		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					 temp2[i][j] += temp[i][k] * Ssrc[k][j];
				}
			}
		}

		int foo=0,bar=0;
		temp2[3][0] = 0;
		temp2[3][1] = 0;
		temp2[3][2] = 0;
	}
	catch ( Magick::Exception & error)
	{
		cerr << "Caught Magick++ exception: " << error.what() << endl;
	}
	return 0;
}
#endif /* SRCMAT_H_ */
