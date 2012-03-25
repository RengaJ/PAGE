#ifndef PAGE_UTILITY_H_
#define PAGE_UTILITY_H_

#define TEXTURE_PATH "./models/"

#include <GL/glew.h>
#include <GL/glfw.h>

#include <iostream>
#include <string.h>
#include <stdlib.h>

namespace PAGE
{

    const double PI = 3.14159265358979323846;
    const double DEG_TO_RAD = PI/180.0;
    const double RAD_TO_DEG = 180.0/PI;

    const double FULL_ANGLE_RAD = 2.0 * PI;
    const double FULL_ANGLE_DEG = 360.0;


	float clampf01 ( float value );
	float clampf ( float value, float min, float max );
	int   clampi ( int value,   int min,   int max );
	// Swap method
	void swap( float* v1, float* v2 );

}

#endif /* PAGE_UTILITY_H_ */
