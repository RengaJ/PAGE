#include "page_utility.h"

// Clamping methods
float PAGE::clampf01 ( float value )
{
	return (value < 0 ? 0 : value > 1 ? 1 : value);
}
float PAGE::clampf ( float value, float min, float max )
{
	return (value < min ? min : value > max ? max : value);
}
int   PAGE::clampi ( int value,   int min,   int max )
{
	return (value < min ? min : value > max ? max : value);
}

// Swap method
void PAGE::swap( float* v1, float* v2 )
{
	float v = *v1;
	*v1 = *v2;
	*v2 = v;
}
