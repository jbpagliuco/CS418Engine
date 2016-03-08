#pragma once

#include "util/Util.h"
#include "Math.h"

#ifdef _MSC_VER
#include <xmmintrin.h>
#endif

namespace CS418
{
	// 2D vector of 32 bit single floating point components.
	struct VECTOR2F
	{
		F32 x;
		F32 y;

		VECTOR2F() { }
		VECTOR2F(F32 _x, F32 _y) : x(_x), y(_y) { }
		explicit VECTOR2F(const F32 * pDataArray) : x(pDataArray[0]), y(pDataArray[1]) { }

		VECTOR2F & operator=(const VECTOR2F & other) { x = other.x; y = other.y; return *this; }
	};

	// 2D vector of 32 bit single floating point components, aligned to 16 bytes.
	CS418_ALIGN_MS(16) struct VECTOR2FA : public VECTOR2F
	{
		VECTOR2FA() : VECTOR2F() { }
		VECTOR2FA(F32 _x, F32 _y) : VECTOR2F(_x, _y) { }
		explicit VECTOR2FA(const F32 * pDataArray) : VECTOR2F(pDataArray) { }

		VECTOR2FA & operator=(const VECTOR2FA & other) { x = other.x; y = other.y; return *this; }
	} CS418_ALIGN_GCC(16);

	// 3D vector of 32 bit single floating point components.
	struct VECTOR3F
	{
		F32 x;
		F32 y;
		F32 z;

		VECTOR3F() { }
		VECTOR3F(F32 _x, F32 _y, F32 _z) : x(_x), y(_y), z(_z) { }
		explicit VECTOR3F(const F32 * pDataArray) : x(pDataArray[0]), y(pDataArray[1]), z(pDataArray[2]) { }

		VECTOR3F & operator=(const VECTOR3F & other) { x = other.x; y = other.y; z = other.z; return *this; }
	};

	// 3D vector of 32 bit single floating point components, aligned to 16 bytes.
	CS418_ALIGN_MS(16) struct VECTOR3FA : public VECTOR3F
	{
		VECTOR3FA() : VECTOR3F() { }
		VECTOR3FA(F32 _x, F32 _y, F32 _z) : VECTOR3F(_x, _y, _z) { }
		explicit VECTOR3FA(const F32 * pDataArray) : VECTOR3F(pDataArray) { }

		VECTOR3FA & operator=(const VECTOR3FA & other) { x = other.x; y = other.y; z = other.z; return *this; }
	} CS418_ALIGN_GCC(16);

	// 4D vector of 32 bit single floating point components.
	struct VECTOR4F
	{
		F32 x;
		F32 y;
		F32 z;
		F32 w;

		VECTOR4F() { }
		VECTOR4F(F32 _x, F32 _y, F32 _z, F32 _w) : x(_x), y(_y), z(_z), w(_w) { }
		explicit VECTOR4F(const F32 * pDataArray) : x(pDataArray[0]), y(pDataArray[1]), z(pDataArray[2]), w(pDataArray[3]) { }

		VECTOR4F & operator=(const VECTOR4F & other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
	};

	// 4D vector of 32 bit single floating point components, aligned to 16 bytes.
	CS418_ALIGN_MS(16) struct VECTOR4FA : public VECTOR4F
	{
		VECTOR4FA() : VECTOR4F() { }
		VECTOR4FA(F32 _x, F32 _y, F32 _z, F32 _w) : VECTOR4F(_x, _y, _z, _w) { }
		explicit VECTOR4FA(const F32 * pDataArray) : VECTOR4F(pDataArray) { }

		VECTOR4FA & operator=(const VECTOR4FA & other) { x = other.x; y = other.y; z = other.z; w = other.w; return *this; }
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
		explicit Vector(const VECTOR2F &vector);
		// Creates a vector from 2D vector.
		explicit Vector(const VECTOR2FA &vector);
		// Creates a vector from 3D vector.
		explicit Vector(const VECTOR3F &vector);
		// Creates a vector from 3D vector.
		explicit Vector(const VECTOR3FA &vector);
		// Creates a vector from 4D vector.
		explicit Vector(const VECTOR4F &vector);
		// Creates a vector from 4D vector.
		explicit Vector(const VECTOR4FA &vector);
#ifdef _MSC_VER
	private:
		explicit Vector(__m128 vector);

	public:
#endif

		// Stores the data into a VECTOR2F object.
		VECTOR2F asVector2()const;
		// Stores the data into a VECTOR2FA object.
		VECTOR2FA asVector2A()const;
		// Stores the data into a VECTOR3F object.
		VECTOR3F asVector3()const;
		// Stores the data into a VECTOR3FA object.
		VECTOR3FA asVector3A()const;
		// Stores the data into a VECTOR4F object.
		VECTOR4F asVector4()const;
		// Stores the data into a VECTOR4FA object.
		VECTOR4FA asVector4A()const;


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
		Vector Lua_MultScalar(F32 scalar)const;

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
		VECTOR2F v2equals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;
		// Checks for equality (within epsilon) of the 2D vectors. Returns a 1.0f for not equals or a 0.0f for equals in the respective component.
		VECTOR2F v2notEquals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;

		// Compares the 2D vectors. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		VECTOR2F v2less(const Vector &other)const;
		// Compares the 2D vectors. Returns a 1.0f for a lesser or equal value or a 0.0f otherwise in the respective component.
		VECTOR2F v2lessEq(const Vector &other)const;
		// Compares the 2D vectors. Returns a 1.0f for a greater value or a 0.0f otherwise in the respective component.
		VECTOR2F v2greater(const Vector &other)const;
		// Compares the 2D vectors. Returns a 1.0f for a greater equal value or a 0.0f otherwise in the respective component.
		VECTOR2F v2greaterEq(const Vector &other)const;


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
		VECTOR3F v3equals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;
		// Checks for equality (within epsilon) of the 3D vectors. Returns a 1.0f for not equals or a 0.0f for equals in the respective component.
		VECTOR3F v3notEquals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;

		// Compares the 3D vectors. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		VECTOR3F v3less(const Vector &other)const;
		// Compares the 3D vectors. Returns a 1.0f for a lesser or equal value or a 0.0f otherwise in the respective component.
		VECTOR3F v3lessEq(const Vector &other)const;
		// Compares the 3D vectors. Returns a 1.0f for a greater value or a 0.0f otherwise in the respective component.
		VECTOR3F v3greater(const Vector &other)const;
		// Compares the 3D vectors. Returns a 1.0f for a greater equal value or a 0.0f otherwise in the respective component.
		VECTOR3F v3greaterEq(const Vector &other)const;


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
		VECTOR4F v4equals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;
		// Checks for equality (within epsilon) of the 4D vectors. Returns a 1.0f for not equals or a 0.0f for equals in the respective component.
		VECTOR4F v4notEquals(const Vector &other, F32 epsilon = FLOAT_EPSILON)const;

		// Compares the 4D vectors. Returns a 1.0f for a lesser value or a 0.0f otherwise in the respective component.
		VECTOR4F v4less(const Vector &other)const;
		// Compares the 4D vectors. Returns a 1.0f for a lesser or equal value or a 0.0f otherwise in the respective component.
		VECTOR4F v4lessEq(const Vector &other)const;
		// Compares the 4D vectors. Returns a 1.0f for a greater value or a 0.0f otherwise in the respective component.
		VECTOR4F v4greater(const Vector &other)const;
		// Compares the 4D vectors. Returns a 1.0f for a greater equal value or a 0.0f otherwise in the respective component.
		VECTOR4F v4greaterEq(const Vector &other)const;


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

	Vector Lua_V2(VECTOR2F v);
	Vector Lua_V3(VECTOR3F v);
	Vector Lua_V4(VECTOR4F v);
}