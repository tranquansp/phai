/*
 * Mat_Display.h
 *
 *  Created on: Jul 25, 2012
 *      Author: quanrock
 */

#ifndef MAT_DISPLAY_H_
#define MAT_DISPLAY_H_


/*
 *
 * This header provide function to display Matrix by colum and row
 * By tran quan !!
 *
 * */

#include <iostream>

int getMatinfo(double Mm[4][4])
{
	std::cout << " ------------- " << std::endl;
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			std::cout << Mm[i][j] << "  ";
		}
		std::cout << std::endl;
	}
	return 0;
}



#endif /* MAT_DISPLAY_H_ */
