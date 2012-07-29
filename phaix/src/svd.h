/*
 * svd.h
 *
 *  Created on: Jul 25, 2012
 *      Author: quanrock
 */

#ifndef SVD_H_
#define SVD_H_

/*******************************************************************************
* color_transfer.cpp
*

*
*  Copyright (C) 2009-2012 Intel Corporation. All Rights Reserved.
*  The information and material ("Material") provided below is owned by Intel
*  Corporation or its suppliers or licensors, and title to such Material remains
*  with Intel Corporation or its suppliers or licensors. The Material contains
*  proprietary information of Intel or its suppliers and licensors. The Material
*  is protected by worldwide copyright laws and treaty provisions. No part of
*  the Material may be copied, reproduced, published, uploaded, posted,
*  transmitted, or distributed in any way without Intel's prior express written
*  permission. No license under any patent, copyright or other intellectual
*  property rights in the Material is granted to or conferred upon you, either
*  expressly, by implication, inducement, estoppel or otherwise. Any license
*  under such intellectual property rights must be express and approved by Intel
*  in writing.
*
*
*  Created on: Jul 16, 2012
*  Develope by : quanrock
********************************************************************************
*********************************************************************************/
#include <iostream>

extern "C" void dgesvd_( char* jobu, char* jobvt, int* m, int* n, double* a,
                int* lda, double* s, double* u, int* ldu, double* vt, int* ldvt,
                double* work, int* lwork, int* info );
/* Auxiliary routines prototypes */
static void dgesvd( char* jobu, char* jobvt, int* m, int* n, double* a,
                int* lda, double* s, double* u, int* ldu, double* vt, int* ldvt,
                double* work, int* lwork, int* info )
                {
					dgesvd_(jobu,jobvt,m,n,a,lda,s,u,ldu,vt,ldvt,work,lwork,info);
                	return;
				}

#endif /* SVD_H_ */
