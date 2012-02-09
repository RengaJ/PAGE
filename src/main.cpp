#include "page_vector.h"

int main(int argc, char* argv[])
{
	PAGE::Vector2 vector2_1(1,1);
	PAGE::Vector2 vector2_2(4,5);
	
	std::cout << "vector2_1: " << vector2_1 << std::endl;
	std::cout << "vector2_2: " << vector2_2 << std::endl;
	
	std::cout << "Addition: " << (vector2_1 + vector2_2) << std::endl;
	std::cout << "Subtraction: " << (vector2_1 - vector2_2) << std::endl;

	return 0;
}
