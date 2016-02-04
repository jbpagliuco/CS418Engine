#pragma once

#include "Util.h"
#include "Math.h"

#ifdef _MSC_VER
#include <xmmintrin.h>
#endif

namespace CS418
{
	// 2D vector of 32 bit single floating point components.
	struct VECTOR2
	{
		F32 x;
		F32 y;

		VECTOR2() { }
		VECTOR2(F32 _x, F32 _y) : x(_x), y(_y) { }
		explicit VECTOR2(const F32 * pDataArray) : x(pDataArray[0]), y(pDataArray[1]) { }

		VECTOR2 & operator=(const VECTOR2 & other) { x = other.x; y = other.y; return *this; }
	};

	// 2D vector of 32 bit single floating point components, aligned to 16 bytes.
	CS418_ALIGN_MS(16) struct VECTOR2A : public VECTOR2
	{
		VECTOR2A() : VECTOR2() { }
		VECTOR2A(F32 _x, F32 _y) : VECTOR2(_x, _y) { }
		explicit VECTOR2A(const F32 * pDataArray) : VECTOR2(pDataArray) { }

		VECTOR2A & operator=(const VECTOR2A & other) { x = other.x; y = other.y; return *this; }
	} CS418_ALIGN_GCC(16);

	// 3D vector of 32 bit single floating point components.
	struct VECTOR3
	{
		F32 x;
		F32 y;
		F32 z;

		VECTOR3() { }
		VECTOR3(F32 _x, F32 _y, F32 _z) : x(_x), y(_y), z(_z) { }
		explicit VECTOR3(const F32 * pDataArray) : x(pDataArray[0]), y(pDataArray[1]), z(pDataArray[2]) { }

		VECTOR3 & operator=(const VECTOR3 & other) { x = other.x; y = other.y; z = other.z; return *this; }
	};

	// 3D vector of 32 bit single floating point components, aligned to 16 bytes.
	CS418_ALIGN_MS(16) struct VECTOR3A : public VECTOR3
	{
		VECTOR3A() : VECTOR3() { }
		VECTOR3A(F32 _x, F32 _y, F32 _z) : VECTOR3(_x, _y, _z) { }
		explicit VECTOR3A(const F32 * pDataArray) : VECTOR3(pDataArray) { }

		VECTOR3A & operator=(const VECTOR3A & other) { x = other.x; y = other.y; z = other.z; return *this; }
	} CS418_ALIGN_GCC(16);

	// 4D vector of 32 bit single floating point components.
	struct VECTOR4
	{
		F32 x;
		F32 y;
		F32 z;
		F32 w;

		VECTOR4() { }
		VECTOR4(F32 _x, F32 _y, F32 _z, F32 _w) : x(_x), y(_y), z(_z), w(_w) { }
		explicit VECTOR4(const F32 * pDataArray) : x(pDataArray[0]), y(pDataArray[1]), z(pDataArray[2]), w(pDataArray[3]) { }

		VECTOR4 & operator=(const VECTOR4 & other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
	};

	// 4D vector of 32 bit single floating point components, aligned to 16 bytes.
	CS418_ALIGN_MS(16) struct VECTOR4A : public VECTOR4
	{
		VECTOR4A() : VECTOR4() { }
		VECTOR4A(F32 _x, F32 _y, F32 _z, F32 _w) : VECTOR4(_x, _y, _z, _w) { }
		explicit VECTOR4A(const F32 * pDataArray) : VECTOR4(pDataArray) { }

		VECTOR4A & operator=(const VECTOR4A & other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
	} CS418_ALIGN_GCC(16);

	class Vector
	{
		friend class Matrix;
		friend class Quaternion;

	public:
		Vector();
		// Creates a vector with all component set equal to "all".
		explicit Vector(F32 all);
		// Creates a vector with the four components (x, y, z, w).
		Vector(F32 x, F32 y, F32 z, F32 w);
		// Creates a vector from 2D vector.
		explicit Vector(const VECTOR2 &vector);
		// Creates a vector from 2D vector.
		explicit Vector(const VECTOR2A &vector);
		// Creates a vector from 3D vector.
		explicit Vector(const VECTOR3 &vector);
		// Creates a vector from 3D vector.
		explicit Vector(const VECTOR3A &vector);
		// Creates a vector from 4D vector.
		explicit Vector(const VECTOR4 &vector);
		// Creates a vector from 4D vector.
		explicit Vector(const VECTOR4A &vector);
#ifdef _MSC_VER
	private:
		explicit Vector(__m128 vector);

	public:
#endif

		// Stores the data into a VECTOR2 object.
		VECTOR2 asVector2()const;
		// Stores the data into a VECTOR2A object.
		VECTOR2A asVector2A()const;
		// Stores the data into a VECTOR3 object.
		VECTOR3 asVector3()const;
		// Stores the data into a VECTOR3A object.
		VECTOR3A asVector3A()const;
		// Stores the data into a VECTOR4 object.
		VECTOR4 asVector4()const;
		// Stores the data into a VECTOR4A object.
		VECTOR4A asVector4A()const;


		// Get the x component.
		F32 getX()const;
		// Get the y component.
		F32 getY()const;
		// Get the z component.
		F32 getZ()const;
		// Get the w component.
		F32 getW()const;


		// Adds the two vectors component wise.
		Vector operator+(const Vector &other)const;
		// Adds the two vectors component wise and sets the result to this.
		Vector & operator+=(const Vector &other);

		// Subtracts the two vectors component wise.
		Vector operator-(const Vector &other)const;
		// Subtracts the two vectors component wise and sets the result to this.
		Vector & operator-=(const Vector &other);

		// Multiplies the two vectors component wise.
		Vector operator*(const Vector &other)const;
		// Multiplies the two vectors component wise and sets the result to this.
		Vector operator*=(const Vector &other);

		// Multiplies each component by the scalar.
		Vector operator*(F32 scalar)const;
		// Multiplies each component by the scalar and sets the result equal to this.
		Vector operator*=(F32 scalar);

		// Divides the two vectors component wise.
		Vector operator/(const Vector &other)const;
		// Divides the two vectors component wise ands sets the result equal to this.
		Vector operator/=(const Vector &other);

		// Divides each component by the scalar.
		Vector operator/(F32 scalar)const;
		// Divides each component by the scalar and sets the result equal to this.
		Vector operator/=(F32 scalar);


		// Sets this vector to the absolute value of itself.
		// Returns a reference to this vector.
		Vector & absoluteValue();
		// Negates this vector.
		// Returns a reference to this vector.
		Vector & negate();
		// Linearly interpolates the two vectors by the amount t and returns the resulting vector.
		Vector lerp(const Vector &other, F32 t)const;




		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 2D Vector OPERATIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////// COMPARISONS ////////////////////////////////////////////////////////////////////////////

		// Checks for equality (within epsilon) of the 2D vectors. Returns a 1.0f for equals or a 0.0f for not equals in the respective component.
		VECTOR2 v2equals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;
		// Checks for equality (within epsilon) of the 2D vectors. Returns a 1.0f for not equals or a 0.0f for equals in the respective component.
		VECTOR2 v2notEquals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;

		// Compares the 2D vectors. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		VECTOR2 v2less(const Vector &other)const;
		// Compares the 2D vectors. Returns a 1.0f for a lesser or equal value or a 0.0f otherwise in the respective component.
		VECTOR2 v2lessEq(const Vector &other)const;
		// Compares the 2D vectors. Returns a 1.0f for a greater value or a 0.0f otherwise in the respective component.
		VECTOR2 v2greater(const Vector &other)const;
		// Compares the 2D vectors. Returns a 1.0f for a greater equal value or a 0.0f otherwise in the respective component.
		VECTOR2 v2greaterEq(const Vector &other)const;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////// Vector OPERATIONS //////////////////////////////////////////////////////////////////////

		// Calculates the dot product of the two 2D vectors.
		F32 v2Dot(const Vector &other)const;

		// Calculates the length of the 2D vector.
		F32 v2Length()const;
		// Calculates the squared length of the 2D vector.
		F32 v2LengthSq()const;

		// Normalizes this 2D vector.
		// Returns a reference to this vector.
		Vector & v2Normalize();

		// Calculates the angle (in radians) between the two 2D vectors. If both vectors are of unit length, use v2AngleBetweenNormals
		// for speed.
		F32 v2AngleBetween(const Vector &other)const;
		// Calculates the angle (in radians) between the two unit 2D vectors.
		F32 v2AngleBetweenNormals(const Vector &other)const;






		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 3D Vector OPERATIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////// COMPARISONS ////////////////////////////////////////////////////////////////////////////

		// Checks for equality (within epsilon) of the 3D vectors. Returns a 1.0f for equals or a 0.0f for not equals in the respective component.
		VECTOR3 v3equals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;
		// Checks for equality (within epsilon) of the 3D vectors. Returns a 1.0f for not equals or a 0.0f for equals in the respective component.
		VECTOR3 v3notEquals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;

		// Compares the 3D vectors. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		VECTOR3 v3less(const Vector &other)const;
		// Compares the 3D vectors. Returns a 1.0f for a lesser or equal value or a 0.0f otherwise in the respective component.
		VECTOR3 v3lessEq(const Vector &other)const;
		// Compares the 3D vectors. Returns a 1.0f for a greater value or a 0.0f otherwise in the respective component.
		VECTOR3 v3greater(const Vector &other)const;
		// Compares the 3D vectors. Returns a 1.0f for a greater equal value or a 0.0f otherwise in the respective component.
		VECTOR3 v3greaterEq(const Vector &other)const;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////// Vector OPERATIONS //////////////////////////////////////////////////////////////////////

		// Calculates the dot product of the two 3D vectors.
		F32 v3Dot(const Vector &other)const;

		// Calculates the length of the 3D vector.
		F32 v3Length()const;
		// Calculates the squared length of the 3D vector.
		F32 v3LengthSq()const;

		// Normalizes this 3D vector.
		// Returns a reference to this vector.
		Vector & v3Normalize();

		// Calculates a vector that is perpendicular to both vectors.
		Vector v3Cross(const Vector &other)const;

		// Calculates the angle (in radians) between the two 3D vectors. If both vectors are of unit length, use v3AngleBetweenNormals
		// for speed.
		F32 v3AngleBetween(const Vector &other)const;
		// Calculates the angle (in radians) between the two unit 3D vectors.
		F32 v3AngleBetweenNormals(const Vector &other)const;






		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 4D Vector OPERATIONS ////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////// COMPARISONS ////////////////////////////////////////////////////////////////////////////

		// Checks for equality (within epsilon) of the 4D vectors. Returns a 1.0f for equals or a 0.0f for not equals in the respective component.
		VECTOR4 v4equals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;
		// Checks for equality (within epsilon) of the 4D vectors. Returns a 1.0f for not equals or a 0.0f for equals in the respective component.
		VECTOR4 v4notEquals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;

		// Compares the 4D vectors. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		VECTOR4 v4less(const Vector &other)const;
		// Compares the 4D vectors. Returns a 1.0f for a lesser or equal value or a 0.0f otherwise in the respective component.
		VECTOR4 v4lessEq(const Vector &other)const;
		// Compares the 4D vectors. Returns a 1.0f for a greater value or a 0.0f otherwise in the respective component.
		VECTOR4 v4greater(const Vector &other)const;
		// Compares the 4D vectors. Returns a 1.0f for a greater equal value or a 0.0f otherwise in the respective component.
		VECTOR4 v4greaterEq(const Vector &other)const;


		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////// Vector OPERATIONS //////////////////////////////////////////////////////////////////////

		// Calculates the dot product of the two 4D vectors.
		F32 v4Dot(const Vector &other)const;

		// Calculates the length of the 4D vector.
		F32 v4Length()const;
		// Calculates the squared length of the 4D vector.
		F32 v4LengthSq()const;

		// Normalizes this 4D vector.
		// Returns a reference to this vector.
		Vector & v4Normalize();

		// Calculates the angle (in radians) between the two 4D vectors. If both vectors are of unit length, use v4AngleBetweenNormals
		// for speed.
		F32 v4AngleBetween(const Vector &other)const;
		// Calculates the angle (in radians) between the two unit 4D vectors.
		F32 v4AngleBetweenNormals(const Vector &other)const;





	private:
#ifdef _MSC_VER
		__m128 m_elems;
#endif

		friend Vector VectorZero();
		friend Matrix MatrixTranslation(const Vector &translation);
		friend Matrix MatrixLookAtLH(const Vector &position, const Vector &target, const Vector &up);
	};

	// Returns the zero vector.
	Vector VectorZero();
}