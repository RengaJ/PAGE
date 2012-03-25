#include "page_matrix.h"
#include "page_vector.h"
#include "page_utility.h"

using namespace PAGE;
/******************   MATRIX 2x2  ******************/
  //========================//
 //===   CONSTRUCTORS   ===//
//========================//
// Default Constructor
Matrix22::Matrix22() { }
// Partial Constructor
Matrix22::Matrix22(float diagonal)
{
    v1 = Vector2(diagonal,0);
    v2 = Vector2(0,diagonal);
}
// Partial Constructor
Matrix22::Matrix22(float values[4])
 : v1(values[0],values[1]), v2(values[2],values[3]) { }
// Partial Constructor
Matrix22::Matrix22(float vf1, float vf2, float vf3, float vf4)
 : v1(vf1,vf2), v2(vf3,vf4) { }
// Partial Constructor
Matrix22::Matrix22(Vector2 col1, Vector2 col2)
 : v1(col1), v2(col2) { }
// Copy Constructor
Matrix22::Matrix22(const Matrix22 &matrix) { *this = matrix; }
  //=========================//
 //===     OPERATORS     ===//
//=========================//
// Assignment Operator
Matrix22 Matrix22::operator=(const Matrix22& matrix)
{
	if (this == &matrix)
		return *this;
	v1 = matrix.v1;
	v2 = matrix.v2;
	return *this;
}
// Scalar Multiplication Operator
Matrix22 Matrix22::operator*(const float scale)
{
	return Matrix22(v1*scale, v2*scale);
}
// Friend Scalar Multiplication Operator (Defined in .h)
// Array-Subscript Operator
Vector2& Matrix22::operator[](int i)
{
	if (i%2 == 0)
		return v1;
	return v2;
}
// Equality Operator
bool Matrix22::operator==(Matrix22 &matrix)
{
	return v1 == matrix.v1 && v2 == matrix.v2;
}
// Inequality Operator
bool Matrix22::operator!=(Matrix22 &matrix)
{
	return v1 != matrix.v1 || v2 != matrix.v2;
}
// Matrix Multiplication Operator
Matrix22 Matrix22::operator*(Matrix22 &matrix)
{
	Vector2 v1_n, v2_n;
	v1_n[0] = v1[0]*matrix[0][0] + v2[0]*matrix[0][1]; v2_n[0] = v1[0]*matrix[1][0] + v2[0]*matrix[1][1];
	v1_n[1] = v1[1]*matrix[0][0] + v2[1]*matrix[0][1]; v2_n[1] = v1[1]*matrix[1][0] + v2[1]*matrix[1][1];

	return Matrix22(v1_n,v2_n);
}
// Vector Multiplication Operator
Vector2 Matrix22::operator*(Vector2 &point)
{
	float p1 = v1[0]*point[0] + v2[0]*point[1];
	float p2 = v1[1]*point[0] + v2[0]*point[1];
	return Vector2(p1,p2);
}
  //=========================//
 //===     FUNCTIONS     ===//
//=========================//
// Non-Altering Transpose ( matrix.transpose() does not alter matrix )
Matrix22 Matrix22::transpose()
{
	Vector2 v1_c(v1), v2_c(v2);
	swap(&v1_c[1],&v2_c[0]);
	return Matrix22(v1_c,v2_c);
}
// Determinant
float Matrix22::determinant()
{
	return v1[0]*v2[1] - v1[1]*v2[0];
}
// Has Inverse?
bool Matrix22::has_inverse()
{
	if (determinant() == 0.0f)
		return false;
	return true;
}
// Non-Altering Inverse ( matrix.inverse() will not alter matrix )
Matrix22 Matrix22::inverse()
{
	if (!has_inverse())
		return *this;
	float scale = 1.0f/determinant();
	return Matrix22(v2[1],-v1[1],-v2[0],v1[0]) * scale;
}
/******************   MATRIX 3x3  ******************/
  //========================//
 //===   CONSTRUCTORS   ===//
//========================//
// Default Constructor
Matrix33::Matrix33() { }
// Partial Constructor
Matrix33::Matrix33(float diagonal)
{
    v1 = Vector3(diagonal,0,0);
    v2 = Vector3(0,diagonal,0);
    v3 = Vector3(0,0,diagonal);
}
// Partial Constructor
Matrix33::Matrix33(float values[9])
 : v1(values[0],values[1],values[2]),
   v2(values[3],values[4],values[5]),
   v3(values[6],values[7],values[8]) { }
// Partial Constructor
Matrix33::Matrix33(float vf1, float vf2, float vf3,
                   float vf4, float vf5, float vf6,
                   float vf7, float vf8, float vf9)
 : v1(vf1, vf2, vf3),
   v2(vf4, vf5, vf6),
   v3(vf7, vf8, vf9) { }
// Partial Constructor
Matrix33::Matrix33(Vector3 v1_c, Vector3 v2_c, Vector3 v3_c)
 : v1(v1_c), v2(v2_c), v3(v3_c) { }
// Copy Constructor
Matrix33::Matrix33(const Matrix33 &matrix) { *this = matrix; }
  //=========================//
 //===     OPERATORS     ===//
//=========================//
// Assignment Operator
Matrix33 Matrix33::operator=(const Matrix33& matrix)
{
	if (this == &matrix)
		return *this;
	v1 = matrix.v1;
	v2 = matrix.v2;
	v3 = matrix.v3;
	return *this;
}
// Scalar Multiplication Operator
Matrix33 Matrix33::operator*(const float scale)
{
	return Matrix33(v1*scale, v2*scale, v3*scale);
}
// Friend Scalar Multiplication Operator (Defined in .h)
// Array-Subscript Operator
Vector3& Matrix33::operator[](int i)
{
	 if (i%3 == 0)
		 return v1;
	 if (i%3 == 1)
		 return v2;
	 return v3;
}
// Equality Operator
bool Matrix33::operator==(const Matrix33 &matrix)
{
	return v1 == matrix.v1 && v2 == matrix.v2 && v3 == matrix.v3;
}
// Inequality Operator
bool Matrix33::operator!=(const Matrix33 &matrix)
{
	return v1 != matrix.v1 || v2 != matrix.v2 || v3 != matrix.v3;
}
// Matrix Multiplication Operator
Matrix33 Matrix33::operator*(Matrix33 &matrix)
{
	Vector3 v1_n, v2_n, v3_n;
	v1_n[0] = v1[0]*matrix[0][0] + v2[0]*matrix[0][1] + v3[0]*matrix[0][2];
	v1_n[1] = v1[1]*matrix[0][0] + v2[1]*matrix[0][1] + v3[1]*matrix[0][2];
	v1_n[2] = v1[2]*matrix[0][0] + v2[2]*matrix[0][1] + v3[2]*matrix[0][2];

	v2_n[0] = v1[0]*matrix[1][0] + v2[0]*matrix[1][1] + v3[0]*matrix[1][2];
	v2_n[1] = v1[1]*matrix[1][0] + v2[1]*matrix[1][1] + v3[1]*matrix[1][2];
	v2_n[2] = v1[2]*matrix[1][0] + v2[2]*matrix[1][1] + v3[2]*matrix[1][2];

	v3_n[0] = v1[0]*matrix[2][0] + v2[0]*matrix[2][1] + v3[0]*matrix[2][2];
	v3_n[1] = v1[1]*matrix[2][0] + v2[1]*matrix[2][1] + v3[1]*matrix[2][2];
	v3_n[2] = v1[2]*matrix[2][0] + v2[2]*matrix[2][1] + v3[2]*matrix[2][2];
	return Matrix33(v1_n,v2_n,v3_n);
}
// Vector Multiplication Operator
Vector3 Matrix33::operator*(Vector3 &point)
{
	Vector3 v_n;
	v_n[0] = v1[0]*point[0] + v2[0]*point[1] + v3[0]*point[2];
	v_n[1] = v1[1]*point[0] + v2[1]*point[1] + v3[1]*point[2];
	v_n[2] = v1[2]*point[0] + v2[1]*point[1] + v3[2]*point[2];
	return v_n;
}
  //=========================//
 //===     FUNCTIONS     ===//
//=========================//
// Non-Altering Transpose ( matrix.transpose() does not alter matrix )
Matrix33 Matrix33::transpose()
{
	Vector3 v1_c(v1), v2_c(v2), v3_c(v3);
	swap(&v1_c[1],&v2_c[0]); swap(&v1_c[2],&v3_c[0]); swap(&v2_c[2],&v3_c[1]);
	return Matrix33(v1_c,v2_c,v3_c);
}
// Determinant
float Matrix33::determinant()
{
	return (v1[0]*v2[1]*v3[2] + v2[0]*v3[1]*v1[2] + v3[0]*v1[1]*v2[1]) -
		   (v1[2]*v2[1]*v3[0] + v1[1]*v2[0]*v3[2] + v1[0]*v2[2]*v3[1]);
}
// Has Inverse?
bool Matrix33::has_inverse()
{
	if (determinant() == 0.0f)
		return false;
	return true;
}
// Non-Altering Inverse ( matrix.inverse() will not alter matrix )
Matrix33 Matrix33::inverse()
{
	if (!has_inverse())
		return *this;
    float scale = 1.0f/determinant();
    return (cofactor() * scale);
}
Matrix33 Matrix33::cofactor()
{
	Matrix33 cFactor;
	cFactor.v1[0] = Matrix22(v2[1],v2[2],v3[1],v3[2]).determinant();
	cFactor.v1[1] = Matrix22(v1[1],v1[2],v3[1],v3[2]).determinant();
	cFactor.v1[2] = Matrix22(v1[1],v1[2],v2[1],v2[2]).determinant();

	cFactor.v2[0] = Matrix22(v2[0],v2[2],v3[0],v3[2]).determinant();
	cFactor.v2[1] = Matrix22(v1[0],v1[2],v3[0],v3[2]).determinant();
	cFactor.v2[2] = Matrix22(v1[0],v1[2],v2[0],v2[2]).determinant();

	cFactor.v3[0] = Matrix22(v2[0],v2[1],v3[0],v3[1]).determinant();
	cFactor.v3[1] = Matrix22(v1[0],v1[1],v3[0],v3[1]).determinant();
	cFactor.v3[2] = Matrix22(v1[0],v1[1],v2[0],v2[1]).determinant();
	return cFactor;
}
/******************   MATRIX 4x4  ******************/
  //========================//
 //===   CONSTRUCTORS   ===//
//========================//
// Default Constructor
Matrix44::Matrix44() { }
// Partial Constructor
Matrix44::Matrix44(float diagonal)
{
    v1 = Vector4(diagonal,0,0,0);
    v2 = Vector4(0,diagonal,0,0);
    v3 = Vector4(0,0,diagonal,0);
    v4 = Vector4(0,0,0,diagonal);
}
// Partial Constructor
Matrix44::Matrix44(float v[16])
 : v1(v[0],v[1],v[2],v[3]),
   v2(v[4],v[5],v[6],v[7]),
   v3(v[8],v[9],v[10],v[11]),
   v4(v[12],v[13],v[14],v[15]) { }
// Partial Constructor
Matrix44::Matrix44(float vf1, float vf2, float vf3, float vf4,
                   float vf5, float vf6, float vf7, float vf8,
                   float vf9, float vf10, float vf11, float vf12,
                   float vf13, float vf14, float vf15, float vf16)
 : v1(vf1,vf2,vf3,vf4), v2(vf5,vf6,vf7,vf8),
   v3(vf9,vf10,vf11,vf12), v4(vf13,vf14,vf15,vf16) { }
// Partial Constructor
Matrix44::Matrix44(Vector4 v1_c, Vector4 v2_c, Vector4 v3_c, Vector4 v4_c)
 : v1(v1_c), v2(v2_c), v3(v3_c), v4(v4_c) { }
// Copy Constructor
Matrix44::Matrix44(const Matrix44 &matrix) { *this = matrix; }
  //=========================//
 //===     OPERATORS     ===//
//=========================//
// Assignment Operator
Matrix44 Matrix44::operator=(const Matrix44& matrix)
{
	if (this == &matrix)
		return *this;
	v1 = matrix.v1;
	v2 = matrix.v2;
	v3 = matrix.v3;
	v4 = matrix.v4;
}
// Scalar Mutliplication Operator
Matrix44 Matrix44::operator*(const float scale)
{
	return Matrix44(v1 * scale, v2 * scale, v3 * scale, v4 * scale);
}
// Friend Scalar Multiplication Operator (Defined in .h)
// Array-Subscript Operator
Vector4& Matrix44::operator[](int i)
{
	if (i%4 == 0)
		return v1;
	if (i%4 == 1)
		return v2;
	if (i%4 == 2)
		return v3;
	return v4;
}
// Equality Operator
bool Matrix44::operator==(Matrix44 &matrix)
{
	return v1 == matrix.v1 && v2 == matrix.v2 &&
		   v3 == matrix.v3 && v4 == matrix.v4;
}
// Inequality Operator
bool Matrix44::operator!=(Matrix44 &matrix)
{
	return v1 == matrix.v1 || v2 == matrix.v2 ||
		   v3 == matrix.v3 || v4 == matrix.v4;
}
// Matrix Multiplication Operator
Matrix44 Matrix44::operator*(Matrix44 matrix)
{
	Matrix44 new_matrix;

	for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            new_matrix[i][j] = v1[j]*matrix[i][0] + v2[j]*matrix[i][1] + v3[j]*matrix[i][2] + v4[j]*matrix[i][3];
/*	new_matrix.v1[0] = v1[0]*matrix[0][0] + v2[0]*matrix[0][1] + v3[0]*matrix[0][2] + v4[0]*matrix[0][3];
	new_matrix.v1[1] = v1[1]*matrix[0][0] + v2[1]*matrix[0][1] + v3[1]*matrix[0][2] + v4[1]*matrix[0][3];
	new_matrix.v1[2] = v1[2]*matrix[0][0] + v2[2]*matrix[0][1] + v3[2]*matrix[0][2] + v4[2]*matrix[0][3];
	new_matrix.v1[3] = v1[3]*matrix[0][0] + v2[3]*matrix[0][1] + v3[3]*matrix[0][2] + v4[3]*matrix[0][3];

	new_matrix.v2[0] = v1[0]*matrix[1][0] + v2[0]*matrix[1][1] + v3[0]*matrix[1][2] + v4[0]*matrix[1][3];
	new_matrix.v2[1] = v1[1]*matrix[1][0] + v2[1]*matrix[1][1] + v3[1]*matrix[1][2] + v4[1]*matrix[1][3];
	new_matrix.v2[2] = v1[2]*matrix[1][0] + v2[2]*matrix[1][1] + v3[2]*matrix[1][2] + v4[2]*matrix[1][3];
	new_matrix.v2[3] = v1[3]*matrix[1][0] + v2[3]*matrix[1][1] + v3[3]*matrix[1][2] + v4[3]*matrix[1][3];

	new_matrix.v3[0] = v1[0]*matrix[2][0] + v2[0]*matrix[2][1] + v3[0]*matrix[2][2] + v4[0]*matrix[2][3];
	new_matrix.v3[1] = v1[1]*matrix[2][0] + v2[1]*matrix[2][1] + v3[1]*matrix[2][2] + v4[1]*matrix[2][3];
	new_matrix.v3[2] = v1[2]*matrix[2][0] + v2[2]*matrix[2][1] + v3[2]*matrix[2][2] + v4[2]*matrix[2][3];
	new_matrix.v3[3] = v1[3]*matrix[2][0] + v2[3]*matrix[2][1] + v3[3]*matrix[2][2] + v4[3]*matrix[2][3];

	new_matrix.v4[0] = v1[0]*matrix[3][0] + v2[0]*matrix[3][1] + v3[0]*matrix[3][2] + v4[0]*matrix[3][3];
	new_matrix.v4[1] = v1[1]*matrix[3][0] + v2[1]*matrix[3][1] + v3[1]*matrix[3][2] + v4[1]*matrix[3][3];
	new_matrix.v4[2] = v1[2]*matrix[3][0] + v2[2]*matrix[3][1] + v3[2]*matrix[3][2] + v4[2]*matrix[3][3];
	new_matrix.v4[3] = v1[3]*matrix[3][0] + v2[3]*matrix[3][1] + v3[3]*matrix[3][2] + v4[3]*matrix[3][3]; */
	return new_matrix;
}
// Vector Multiplication Operator
Vector4 Matrix44::operator*(Vector4 &point)
{
	Vector4 v1_n;
	v1_n[0] = v1[0]*point[0] + v2[0]*point[1] + v3[0]*point[2] + v4[0]*point[3];
	v1_n[0] = v1[1]*point[0] + v2[1]*point[1] + v3[1]*point[2] + v4[1]*point[3];
	v1_n[0] = v1[2]*point[0] + v2[2]*point[1] + v3[2]*point[2] + v4[2]*point[3];
	v1_n[0] = v1[3]*point[0] + v2[3]*point[1] + v3[3]*point[2] + v4[3]*point[3];
	return v1_n;
}
  //=========================//
 //===     FUNCTIONS     ===//
//=========================//
// non-altering transpose ( matrix.transpose() will not alter matrix )
Matrix44 Matrix44::transpose()
{
    Vector4 v1_n(v1), v2_n(v2), v3_n(v3), v4_n(v4);
    swap(&v1_n[1],&v2_n[0]); swap(&v1_n[2],&v3_n[0]); swap(&v1_n[3],&v4_n[0]);
    swap(&v2_n[2],&v3_n[1]); swap(&v2_n[3],&v4_n[1]); swap(&v3_n[3],&v4_n[2]);
    return Matrix44(v1_n,v2_n,v3_n,v4_n);
}
float Matrix44::determinant()
{
    return (v1[0]*v2[1]*v3[2]*v4[3] + v1[0]*v3[1]*v4[2]*v2[3] + v1[0]*v4[1]*v2[2]*v3[3] +
            v2[0]*v1[1]*v4[2]*v3[3] + v2[0]*v3[1]*v1[2]*v4[3] + v2[0]*v4[1]*v3[2]*v1[3] +
            v3[0]*v1[1]*v2[2]*v4[3] + v3[0]*v2[1]*v4[2]*v1[3] + v3[0]*v4[1]*v1[2]*v2[3] +
            v4[0]*v1[1]*v3[2]*v2[3] + v4[0]*v2[1]*v1[2]*v3[3] + v4[0]*v3[1]*v2[2]*v1[3] -
            v1[0]*v2[1]*v4[2]*v3[3] - v1[0]*v3[1]*v2[2]*v4[3] - v1[0]*v4[1]*v3[2]*v2[3] -
            v2[0]*v1[1]*v3[2]*v4[3] - v2[0]*v3[1]*v4[2]*v1[3] - v2[0]*v4[1]*v1[2]*v3[3] -
            v3[0]*v1[1]*v4[2]*v2[3] - v3[0]*v2[1]*v1[2]*v4[3] - v3[0]*v4[1]*v2[2]*v1[3] -
            v4[0]*v1[1]*v2[2]*v3[3] - v4[0]*v2[1]*v3[2]*v1[3] - v4[0]*v3[1]*v1[2]*v2[3]);
}
bool Matrix44::has_inverse()
{
    return determinant() != 0.0f;
}
// non-altering inverse ( matrix.inverse() will not alter matrix )
Matrix44 Matrix44::inverse()
{
    if (!has_inverse())
        return *this;
    float scale = 1.0f/determinant();
    return (cofactor() * scale);
}
Matrix44 Matrix44::cofactor()
{
    Matrix44 new_matrix;
    new_matrix.v1[0] = Matrix33(v2[1],v2[2],v2[3],v3[1],v3[2],v3[3],v4[1],v4[2],v4[3]).determinant();
    new_matrix.v2[0] = Matrix33(v1[1],v1[2],v1[3],v3[1],v3[2],v3[3],v4[1],v4[2],v4[3]).determinant();
    new_matrix.v3[0] = Matrix33(v1[1],v1[2],v1[3],v2[1],v2[2],v2[3],v4[1],v4[2],v4[3]).determinant();
    new_matrix.v4[0] = Matrix33(v1[1],v1[2],v1[3],v2[1],v2[2],v2[3],v3[1],v3[2],v3[3]).determinant();

    new_matrix.v1[1] = Matrix33(v2[0],v2[2],v2[3],v3[0],v3[2],v3[3],v4[0],v4[2],v4[3]).determinant();
    new_matrix.v2[1] = Matrix33(v1[0],v1[2],v1[3],v3[0],v3[2],v3[3],v4[0],v4[2],v4[3]).determinant();
    new_matrix.v3[1] = Matrix33(v1[0],v1[2],v1[3],v2[0],v2[2],v2[3],v4[0],v4[2],v4[3]).determinant();
    new_matrix.v4[1] = Matrix33(v1[0],v1[2],v1[3],v2[0],v2[2],v2[3],v3[0],v3[2],v3[3]).determinant();

    new_matrix.v1[2] = Matrix33(v2[0],v2[1],v2[3],v3[0],v3[1],v3[3],v4[0],v4[1],v4[3]).determinant();
    new_matrix.v2[2] = Matrix33(v1[0],v1[1],v1[3],v3[0],v3[1],v3[3],v4[0],v4[1],v4[3]).determinant();
    new_matrix.v3[2] = Matrix33(v1[0],v1[1],v1[3],v2[0],v2[1],v2[3],v4[0],v4[1],v4[3]).determinant();
    new_matrix.v4[2] = Matrix33(v1[0],v1[1],v1[3],v2[0],v2[1],v2[3],v3[0],v3[1],v3[3]).determinant();

    new_matrix.v1[2] = Matrix33(v2[0],v2[1],v2[2],v3[0],v3[1],v3[2],v4[0],v4[1],v4[2]).determinant();
    new_matrix.v2[2] = Matrix33(v1[0],v1[1],v1[2],v3[0],v3[1],v3[2],v4[0],v4[1],v4[2]).determinant();
    new_matrix.v3[2] = Matrix33(v1[0],v1[1],v1[2],v2[0],v2[1],v2[2],v4[0],v4[1],v4[2]).determinant();
    new_matrix.v4[2] = Matrix33(v1[0],v1[1],v1[2],v2[0],v2[1],v2[2],v3[0],v3[1],v3[2]).determinant();

    return new_matrix;
}

Matrix44f Matrix44::toArray()
{
    Matrix44f new_mat = Matrix44f();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            new_mat.mat[(i*4)+j] = (*this)[i][j];

    return new_mat;
}
