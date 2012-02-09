#include "page_vector.h"

int main(int argc, char* argv[])
{
	PAGE::Vector2 vector2_1(1,1);
	PAGE::Vector2 vector2_2(4,5);
	
	std::cout << "vector2_1: " << vector2_1 << std::endl;
	std::cout << "vector2_2: " << vector2_2 << std::endl;
	
	std::cout << "Addition: " << (vector2_1 + vector2_2) << std::endl;
	std::cout << "Subtraction: " << (vector2_1 - vector2_2) << std::endl;

	std::cout << "Multiplication: " << vector2_2 * 2 << std::endl;
	std::cout << "Multiplication: " << 2 * vector2_1 << std::endl;

	std::cout << "Elements of vector2_2: " << vector2_2[0] << " " << vector2_2[3] << std::endl;

	std::cout << "Magnitude Squared: " << vector2_2.magnitude_squared() << std::endl;
	std::cout << "Normalized: " << vector2_2.normalize() << std::endl;

	PAGE::Vector3 vector3_1(1,2,3);
	PAGE::Vector3 vector3_2(8,4,2);
	std::cout << "vector3_1: " << vector3_1 << std::endl;
	std::cout << "vector3_2: " << vector3_2 << std::endl;

	std::cout << "Addition: " << (vector3_1 + vector3_2) << std::endl;
	std::cout << "Subtraction: "  << (vector3_1 - vector3_2) << std::endl;

	std::cout << "Multiplication: " << vector3_2 * 1.5f << std::endl;

	std::cout << "Cross: " << vector3_1.cross(vector3_2) << std::endl;
	std::cout << "Cross: " << PAGE::Vector3::cross(vector3_2,vector3_1) << std::endl;

	return 0;
}
