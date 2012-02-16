#ifndef PAGE_UTILITY_H_
#define PAGE_UTILITY_H_

#include <iostream>

namespace PAGE
{
	float clampf01 ( float value );
	float clampf ( float value, float min, float max );
	int   clampi ( int value,   int min,   int max );
	// Swap method
	void swap( float* v1, float* v2 );

}

#endif /* PAGE_UTILITY_H_ */
