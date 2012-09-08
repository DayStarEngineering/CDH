#include "grey2bin.h"

void grey2bin(image* img)
{
	for( unsigned int i = 0; i < img->xlen; i++ )
	{
		for( unsigned int j = 0; j < img->ylen; j++ )
		{
			img->pixel[i][j] = grey2binLUT[img->pixel[i][j]];
		}
	}
}
