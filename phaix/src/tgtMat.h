/*
 * tgtMat.h
 *
 *  Created on: Jul 25, 2012
 *      Author: quanrock
 */

#ifndef TGTMAT_H_
#define TGTMAT_H_

#include <math.h>
#include "svd.h"
#include "invert_mat.h"

#define M 3
#define N 3
#define LDA M
#define LDU M
#define LDVT N

using namespace Magick;
using namespace std;

int getTgtInfo(double temp2[4][4],double Ttgt[4][4],double Rtgt[4][4],double Stgt[4][4],char *filename)
{
	try {
		InitializeMagick("Magick++");
		Image img(filename);

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
		meanR = meanR/(height*width);
		meanG = meanG/(height*width);
		meanB = meanB/(height*width);

		// mean of r g b

		// Variance
		int pxlTotal = height*width;
		double var[pxlTotal][3];
		double varTrans[3][pxlTotal];

		//ri- rs
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

		// Calculate Covariance matrix 3x3

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
        }

        // SVD

        int m = M, n = N, lda = LDA, ldu = LDU, ldvt = LDVT, info, lwork;
        double wkopt;
        double* work;
        /* Local arrays */
        double s[N], u[LDU*M], vt[LDVT*N];

        /* Executable statements */
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
        /* Print singular values */

        free( (void*)work );

        //Ttgt?
        /*
         *
         1 0 0 -meanR
         0 1 0 -meanG
         0 0 1 -meanB
         0 0 0 	 1
         *
         * */

        for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(i==j)
				{
					Ttgt[i][j] = 1;
				}
				else Ttgt[i][j] = 0;
			}
		}
        Ttgt[0][3] = -meanR;
        Ttgt[1][3] = -meanG;
        Ttgt[2][3] = -meanB;

		//Rtgt
		/*
		 *
		 Rsrc = dgetri_(Usrc)
		 *
		 * */
        double result[16];
        InvertMatrix(u,u);
		//double Rtgt[4][4];
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				Rtgt[i][j] = 0;
			}
		}
		Rtgt[3][3] = 1;
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				Rtgt[j][i] = u[i*3+j];
			}
		}

		//Ssrc
		/*
		 *
		 1/sqrt(s[0])		0				0			0
		  0	    	  	 1/sqrt(s[1])		0			0
		  0					0  	   		1/sqrt(s[2])	0
		  0					0				0 			1
		 *
		 * */
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				Stgt[i][j] = 0;
			}
		}
		Stgt[0][0] =  1/sqrt(s[0]);
		Stgt[1][1] =  1/sqrt(s[1]);
		Stgt[2][2] = 1/sqrt(s[2]);
		Stgt[3][3] = 1;

		double temp[4][4];

		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					 temp[i][j] += Ttgt[i][k] * Rtgt[k][j];
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
					 temp2[i][j] += temp[i][k] * Stgt[k][j];
				}
			}
		}

		int foo=0,bar=0;
		temp2[3][0] = 0;
		temp2[3][1] = 0;
		temp2[3][2] = 0;
		temp2[3][3] = 1;
	}
	catch ( Magick::Exception & error)
	{
		cerr << "Caught Magick++ exception: " << error.what() << endl;
	}
	return 0;
}

#endif /* TGTMAT_H_ */
