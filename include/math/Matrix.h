#pragma once

#include "Util.h"
#include "math/Math.h"

#ifdef _MSC_VER
#include <xmmintrin.h>
#endif

namespace CS418
{
	class Vector;
	class Quaternion;

	// A class representing a 4x4 column vector matrix.
	CS418_ALIGN_MS(16) class Matrix
	{
	public:
		Matrix();
		// Creates a 4x4 matrix with the given data.
		// pData[0..3] = Column 1.
		// pData[4..7] = Column 2.
		// pData[8..11] = Column 3.
		// pData[12..15] = Column 4.
		// WARNING: pData MUST BE ALIGNED TO A 16-BYTE BOUNDARY
		explicit Matrix(const F32 pData[16]);

		/* Creates a 4x4 matrix with the 4 row vectors.
		| col1.x col2.x col3.x col4.x |
		| col1.y col2.y col3.y col4.y |
		| col1.z col2.z col3.z col4.z |
		| col1.w col2.w col3.w col4.w | */
		Matrix(const Vector & col1, const Vector & col2, const Vector & col3, const Vector & col4);

		Matrix(const Matrix & other) = default;
		Matrix & operator=(const Matrix & other) = default;

		~Matrix() = default;

		// Returns the elements at (x, y).
		F32 operator()(U8 x, U8 y)const;

		// Checks for equality (within epsilon) in each entry of the matrix. Returns 1.0f in entry slot if equal, 0.0f otherwise.
		Matrix equals(const Matrix &other, F32 epsilon = FLOAT_EPSILON)const;
		// Checks for inequality (within epsilon) in each entry of the matrix. Returns 1.0f in entry slot if not equal, 0.0f otherwise.
		Matrix notEquals(const Matrix &other, F32 epsilon = FLOAT_EPSILON)const;

		// Compares the matrices. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		Matrix less(const Matrix &other)const;
		// Compares the matrices. Returns a 1.0f for a lesser or equal value or a 0.0f otherwise in the respective component.
		Matrix lessEq(const Matrix &other)const;
		// Compares the matrices. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		Matrix greater(const Matrix &other)const;
		// Compares the matrices. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		Matrix greaterEq(const Matrix &other)const;

		// Adds the two matrices and returns the result.
		Matrix operator+(const Matrix & rhs)const;
		// Adds the two matrices and sets the result equal to this.
		Matrix & operator+=(const Matrix & rhs);

		// Subtracts the two matrices and returns the result.
		Matrix operator-(const Matrix & rhs)const;
		// Subtracts the two matrices and sets the result equal to this.
		Matrix & operator-=(const Matrix & rhs);

		// Performs 4x4 matrix multiplication on the two matrices and returns the result.
		Matrix operator*(const Matrix &rhs)const;
		// Performs 4x4 matrix multiplication on the two matrices and sets the result equal to this.
		Matrix & operator*=(const Matrix &rhs);

		// Performs 4x4 * 4x1 matrix multplication and returns the result.
		Vector operator*(const Vector &rhs)const;

		// Multiplies each element in the matrix by the scalar value and returns the result.
		Matrix operator*(F32 scalar)const;
		// Multiplies each element in the matrix by the scalar value and sets the result equal to this.
		Matrix & operator*=(F32 scalar);

		// Attempts to invert the matrix. pOutOptDet is an optional pointer to a Vector to hold the determinant of the matrix.
		// Note: If the determinant is equal to zero, the inverse does not exist, and thus the matrix will not change.
		void invert(Vector * pOutOptDet);
		// Caculates the determinant and broadcasts the value into each component.
		Vector determinant()const;

		// Transposes this matrix.
		void transpose();

#ifdef _MSC_VER
	private:
		// Returns true if det != 0.
		bool determinantVector(__m128 & minor0, __m128 & minor1, __m128 & minor2, __m128 & minor3, __m128 & pOutDet)const;
#endif

#ifdef _MSC_VER
	private:
		__m128 m_cols[4];
#endif

		friend class Quaternion;

		friend Matrix MatrixIdentity();
		friend Matrix MatrixLookAtLH(const Vector &position, const Vector &target, const Vector &up);
		friend Matrix MatrixPerspectiveFOVLH(F32 fieldOfView, F32 aspectRatio, F32 near, F32 far);
		friend Matrix MatrixTranslation(const Vector &translation);
		friend Matrix MatrixScaling(const Vector &scaling);
		friend Matrix MatrixRotationX(F32 angle);
		friend Matrix MatrixRotationY(F32 angle);
		friend Matrix MatrixRotationZ(F32 angle);
		friend Matrix MatrixRotationQuaternion(const Quaternion & qRot);
		friend Matrix MatrixRotationEuler(F32 x, F32 y, F32 z);
	} CS418_ALIGN_GCC(16);

	// Creates a 4x4 identity matrix.
	extern Matrix MatrixIdentity();

	// Creates a left handed look at matrix.
	extern Matrix MatrixLookAtLH(const Vector &position, const Vector &target, const Vector &up);
	// Creates a left handed perspective field of view matrix.
	extern Matrix MatrixPerspectiveFOVLH(F32 fieldOfView, F32 aspectRatio, F32 near, F32 far);

	// Creates a translation matrix.
	extern Matrix MatrixTranslation(const Vector &translation);
	// Creates a scaling matrix.
	extern Matrix MatrixScaling(const Vector &scaling);
	// Creates a rotation about the x-axis matrix.
	extern Matrix MatrixRotationX(F32 angle);
	// Creates a rotation about the y-axis matrix.
	extern Matrix MatrixRotationY(F32 angle);
	// Creates a rotation about the z-axis matrix.
	extern Matrix MatrixRotationZ(F32 angle);
	// Creates a rotation matrix based off the quaternion.
	extern Matrix MatrixRotationQuaternion(const Quaternion & qRot);
	// Creates a rotation matrix based off the euler angles.
	extern Matrix MatrixRotationEuler(F32 x, F32 y, F32 z);
}