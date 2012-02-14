#ifndef __PAGE_UTILITY
#define __PAGE_UTILITY

#include <iostream>

namespace PAGE
{
	// Clamping methods
	float clampf01 ( float value ) { return (value < 0 ? 0 : value > 1 ? 1 : value); }
	float clampf ( float value, float min, float max ) { return (value < min ? min : value > max ? max : value); }
	int   clampi ( int value,   int min,   int max ) { return (value < min ? min : value > max ? max : value); }

	// Swap method
	void swap( float* v1, float* v2 ) { float v = *v1; *v1 = *v2; *v2 = v; }
}
#endif
