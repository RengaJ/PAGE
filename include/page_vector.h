#ifndef __PAGE_VECTOR
#define __PAGE_VECTOR

#include "page_utility.h"
#include <math.h>

namespace PAGE
{
	class Vector2
	{
		public:
			Vector2() : x(0.0f), y(0.0f) {}
			Vector2(float pX) : x(pX), y(0.0f) {}
			Vector2(float pX, float pY) : x(pX), y(pY) {}
			Vector2(const Vector2 &point) { *this = point; }
		
			Vector2 operator+(const Vector2 &point) { return Vector2(x+point.x, y+point.y); }
			Vector2 operator-(const Vector2 &point) { return Vector2(x-point.x, y-point.y); }
			Vector2 operator*(const float scale) { return Vector2(x*scale,y*scale); }
			friend Vector2 operator*(const float scale, Vector2 &point)
			{ return Vector2(point.x*scale, point.y*scale); }
			Vector2 operator=(const Vector2 &point)	{ x = point.x; y = point.y; return Vector2(x,y); }
			bool operator==(const Vector2 &point) { return x == point.x && y == point.y; }
			bool operator!=(const Vector2 &point) { return x != point.x || y != point.y; }
			float operator[](const int i) { return (i%2 == 0 ? x : y); }
			
			friend std::ostream& operator<<(std::ostream &out, Vector2 point)
			{ out << "( " << point.x << ", " << point.y << " )"; return out; }
			friend std::istream& operator>>(std::istream &in, Vector2 point)
			{ in >> point.x >> point.y; return in; }

			Vector2 normalize()	{ float length = magnitude(); return Vector2(x/length, y/length); }
			float magnitude_squared() { return pow(x,2) + pow(y,2); }
			float magnitude() { return sqrt(pow(x,2) + pow(y,2)); }
			float dot(Vector2 &point) { return x*point.x + y*point.y; }
			static float dot(Vector2 &lhs, Vector2 &rhs) { return lhs.dot(rhs); }
			
			Vector2 lerp(Vector2 &to, float weight) { weight = clampf01(weight); return ((1 - weight) * (*this)) + weight * to; }
			
			float x, y;
	}; // end Vector2
	
	class Vector3
	{
		public:
			Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
			Vector3(float pX) : x(pX), y(0.0f), z(0.0f) {}
			Vector3(float pX, float pY) : x(pX), y(pY), z(0.0f) {}
			Vector3(Vector2 &point) : x(point.x), y(point.y), z(0.0f) {}
			Vector3(Vector2 &point, float pZ) : x(point.x), y(point.y), z(pZ) {}
			Vector3(float pX, float pY, float pZ) : x(pX), y(pY), z(pZ) {}
			Vector3(const Vector3 &point) { *this = point; }
		
			Vector3 operator+(const Vector3 &point) { return Vector3(x+point.x, y+point.y, z+point.z); }
			Vector3 operator-(const Vector3 &point) { return Vector3(x-point.x, y-point.y, z-point.z); }
			Vector3 operator*(const float scale) { return Vector3(x*scale, y*scale, z*scale); }
			friend Vector3 operator*(const float scale, Vector3 &point)
			{ return Vector3(point.x*scale, point.y*scale, point.z*scale); }
			Vector3 operator=(const Vector3 &point) { x = point.x; y = point.y; z = point.z; return Vector3(x,y,z); }
			bool operator==(const Vector3 &point) { return x == point.x && y == point.y && z == point.z; }
			bool operator!=(const Vector3 &point) { return x != point.x || y != point.y || z != point.z; }
			float operator[](const int i) { return (i%3 == 0 ? x : i%3 == 1 ? y : z); }
			
			friend std::ostream& operator<<(std::ostream &out, Vector3 point)
			{ out << "( " << point.x << ", " << point.y << ", " << point.z << " )"; return out; }
			friend std::istream& operator>>(std::istream &in, Vector3 point)
			{ in >> point.x >> point.y >> point.z; return in; }

			Vector3 normalize() { float length = magnitude(); return Vector3(x/length, y/length, z/length); }
			float magnitude_squared() { return pow(x,2) + pow(y,2) + pow(z,2); }
			float magnitude() { return sqrt(pow(x,2) + pow(y,2) + pow(z,2)); }
			Vector3 cross(Vector3 &point)
			{ return Vector3(y*point.z - point.y*z, z*point.x - point.z * x, x * point.y - point.x * y); }
			float dot(Vector3 &point) { return x*point.x + y*point.y + z*point.z; }
			static Vector3 cross(Vector3 &lhs, Vector3 &rhs) { return lhs.cross(rhs); }
			static float dot(Vector3 &lhs, Vector3 &rhs) { return lhs.dot(rhs); }
		
			float x, y, z;
	}; // end Vector3
	
	class Vector4
	{
		public:
			Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
			Vector4(float pX) : x(pX), y(0.0f), z(0.0f), w(0.0f) {}
			Vector4(float pX, float pY) : x(pY), y(pY), z(0.0f), w(0.0f) {}
			Vector4(Vector2 &point) : x(point.x), y(point.y), z(0.0f), w(0.0f) {}
			Vector4(Vector2 &point, float pZ) : x(point.x), y(point.y), z(pZ), w(0.0f) {}
			Vector4(Vector2 &point, float pZ, float pW) : x(point.x), y(point.y), z(pZ), w(pW) {}
			Vector4(Vector3 &point) : x(point.x), y(point.y), z(point.z), w(0.0f) {}
			Vector4(Vector3 &point, float pW) : x(point.x), y(point.y), z(point.z), w(pW) {}
			Vector4(float pX, float pY, float pZ, float pW) : x(pX), y(pY), z(pZ), w(pW) {}
			Vector4(const Vector4 &point) { *this = point; }
		
			Vector4 operator+(const Vector4 &point) { return Vector4(x+point.x, y+point.y, z+point.z, w+point.w); }
			Vector4 operator-(const Vector4 &point) { return Vector4(x-point.x, y-point.y, z-point.z, w-point.w); }
			Vector4 operator*(const float scale) { return Vector4(x*scale, y*scale, z*scale, w*scale); }
			friend Vector4 operator*(const float scale, Vector4 point)
			{ return Vector4(point.x*scale, point.y*scale, point.z*scale, point.w*scale); }
			Vector4 operator=(const Vector4 &point) { x = point.x; y = point.y; z = point.z; w = point.w; return Vector4(x,y,z,w); }
			bool operator==(const Vector4 &point) { return x == point.x && y == point.y && z == point.z && w == point.w; }
			bool operator!=(const Vector4 &point) { return x != point.x || y != point.y || z != point.z || w != point.w; }
			float operator[](const int i) { return (i%4 == 0 ? x : i%4 == 1 ? y : i%4 == 2 ? z : w); }
			
			friend std::ostream& operator<<(std::ostream &out, Vector4 point)
			{ out << "( " << point.x << ", " << point.y << ", " << point.z << ", " << point.w << " )"; return out; }
			friend std::istream& operator>>(std::istream &in, Vector4 point)
			{ in >> point.x >> point.y >> point.z >> point.w; return in; }

			Vector4 normalize() { float length = magnitude(); return Vector4(x/length, y/length, z/length, w/length); }
			float magnitude_squared() { return pow(x,2) + pow(y,2) + pow(z,2) + pow(w,2); }
			float magnitude() { return sqrt(pow(x,2) + pow(y,2) + pow(z,2) + pow(w,2)); }
			float dot(Vector4 &point) { return x*point.x + y*point.y + z*point.z + w*point.w; }
			static float dot(Vector4 &lhs, Vector4 &rhs) { return lhs.dot(rhs); }
			
			float x, y, z, w;
	}; // end Vector4
}
#endif // __PAGE_VECTOR
