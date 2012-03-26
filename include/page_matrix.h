#ifndef __PAGE_MATRIX_H
#define __PAGE_MATRIX_H

#include "page_vector.h"
#include <iostream>

namespace PAGE
{
	struct Matrix22f { float* mat; };
	struct Matrix33f { float* mat; };
	struct Matrix44f { float* mat; };

	class Matrix22
	{
		public:
			Matrix22();
			Matrix22(float diagonal);
			Matrix22(float values[4]);
			Matrix22(float vf1, float vf2, float vf3, float vf4);
			Matrix22(Vector2 col1, Vector2 col2);
			Matrix22(const Matrix22& matrix);
			Matrix22 operator=(const Matrix22& matrix);
			Matrix22 operator*(const float scale);
			friend Matrix22 operator*(const float scale, Matrix22 matrix)
			{ return Matrix22(matrix[0] * scale, matrix[1] * scale); }
			Vector2& operator[](int i);
			bool operator==(Matrix22 &matrix);
			bool operator!=(Matrix22 &matrix);
			Matrix22 operator*(Matrix22 &matrix);
			Vector2 operator*(Vector2 &point);
			// non-altering transpose ( matrix.transpose() will not alter matrix )
			Matrix22 transpose();
			float determinant();
			bool has_inverse();
			// non-altering inverse ( matrix.inverse() will not alter matrix )
			Matrix22 inverse();
			static Matrix22 transpose(Matrix22 &matrix) { return matrix.transpose(); }
			static float determinant(Matrix22 &matrix) { return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0]; }
			static bool has_inverse(Matrix22 &matrix) { return matrix.has_inverse(); }
			static Matrix22 inverse(Matrix22 &matrix) { return matrix.inverse(); }
		private:
			Vector2 v1;
			Vector2 v2;
	};
	class Matrix33
	{
		public:
			Matrix33();
			Matrix33(float diagonal);
			Matrix33(float values[9]);
			Matrix33(float vf1, float vf2, float vf3,
			         float vf4, float vf5, float vf6,
			         float vf7, float vf8, float vf9);
			Matrix33(Vector3 col1, Vector3 col2, Vector3 col3);
			Matrix33(const Matrix33& matrix);
			Matrix33 operator=(const Matrix33& matrix);
			Matrix33 operator*(const float scale);
			friend Matrix33 operator*(const float scale, Matrix33 &matrix)
			{ return Matrix33(matrix[0]*scale, matrix[1]*scale, matrix[2]*scale); }
			Vector3& operator[](int i);
			bool operator==(const Matrix33 &matrix);
			bool operator!=(const Matrix33 &matrix);
			Matrix33 operator*(Matrix33 &matrix);
			Vector3 operator*(Vector3 &point);
			// non-altering transpose ( matrix.transpose() will not alter matrix )
			Matrix33 transpose();
			float determinant();
			bool has_inverse();
			// non-altering inverse ( matrix.inverse() will not alter matrix )
			Matrix33 inverse();
			Matrix33 cofactor();
			static Matrix33 transpose(Matrix33 &matrix) { return matrix.transpose(); }
			static float determinant(Matrix33 &matrix) { return matrix.determinant(); }
			static Matrix33 inverse(Matrix33 &matrix) { return matrix.inverse(); }
			static Matrix33 cofactor(Matrix33 &matrix) { return matrix.cofactor(); }
		private:
			Vector3 v1;
			Vector3 v2;
			Vector3 v3;
	};

	class Matrix44
	{
		public:
			Matrix44();
			Matrix44(float diagonal);
			Matrix44(float v[16]);
			Matrix44(float vf1, float vf2, float vf3, float vf4,
			         float vf5, float vf6, float vf7, float vf8,
			         float vf9, float vf10, float vf11, float vf12,
			         float vf13, float vf14, float vf15, float vf16);
			Matrix44(Vector4 v1_c, Vector4 v2_c, Vector4 v3_c, Vector4 v4_c);
			Matrix44(const Matrix44 &matrix);

			Matrix44 operator=(const Matrix44& matrix);
			Matrix44 operator*(const float scale);
			friend Matrix44 operator*(const float scale, Matrix44 &matrix)
			{ return Matrix44(matrix[0]*scale, matrix[1]*scale, matrix[2]*scale, matrix[3]*scale); }
			Vector4& operator[](int i);
			bool operator==(Matrix44 &matrix);
			bool operator!=(Matrix44 &matrix);
			Matrix44 operator*(Matrix44 matrix);
			Vector4 operator*(Vector4 &point);
			friend std::ostream& operator<<(std::ostream &out, Matrix44 matrix)
			{
			    for (int i = 0; i < 4; i++)
                {
                    out << "[ ";
                    for (int j = 0; j < 4; j++)
                        out << matrix[j][i] << " ";
                    out << "]\n";
                }
                return out;
			}
			// non-altering transpose ( matrix.transpose() will not alter matrix )
			Matrix44 transpose();
			float determinant();
			bool has_inverse();
			// non-altering inverse ( matrix.inverse() will not alter matrix )
			Matrix44 inverse();
			Matrix44 cofactor();
			Matrix44f toArray();
			static Matrix44 transpose(Matrix44 &matrix) { return matrix.transpose(); }
			static float determinant(Matrix44 &matrix) { return matrix.determinant(); }
			static Matrix44 inverse(Matrix44 &matrix) { return matrix.inverse(); }
			static Matrix44 cofactor(Matrix44 &matrix) { return matrix.cofactor(); }
			static Matrix44f toArray(Matrix44& matrix) { return matrix.toArray(); }
		private:
			Vector4 v1;
			Vector4 v2;
			Vector4 v3;
			Vector4 v4;
	};
}
#endif
