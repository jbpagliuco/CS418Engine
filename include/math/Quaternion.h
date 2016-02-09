#pragma once

#include "Vector.h"
#include "Matrix.h"

namespace CS418
{
	// Represents a 4D unit quaternion vector used for rotations.
	class Quaternion
	{
	public:
		Quaternion();
		// Creates a quaternion, where xAxis, yAxis, and zAxis make up the unit vector to 
		// rotate about, and angleInRadians is the amount to rotate.
		Quaternion(F32 xAxis, F32 yAxis, F32 zAxis, F32 angleInRadians);
		// Creates a quaternion, where axis is the unit vector to rotate about, and
		// angleInRadians is the amount to rotate.
		Quaternion(const VECTOR3F * pAxis, F32 angleInRadians);
		// Creates a quaternion from the rotation matrix.
		Quaternion(const Matrix &rotMatrix);

		// Inverts this quaternion.
		// Returns a reference to this.
		Quaternion & invert();

		// Multiplies the two quaternions and returns the result.
		Quaternion operator*(const Quaternion &other)const;
		// Multiplies the two quaternions and sets the result equal to this.
		// Returns a reference to this.
		Quaternion & operator*=(const Quaternion &other);

		// Rotates a vector about the quaternion and returns the resulting rotated vector.
		VECTOR3F operator*(const VECTOR3F &vector)const;

		// Linearly interpolates two quaternions by the amount t and returns the normalized quaternion.
		Quaternion lerp(const Quaternion &other, F32 t)const;
		// Spherically linearly interpolates tw quaternions by the amount t and returns the quaternion.
		Quaternion slerp(const Quaternion &other, F32 t)const;

		F32 getX()const;
		F32 getY()const;
		F32 getZ()const;
		F32 getW()const;

	private:
		Quaternion interpolate(const Quaternion & q1, const Quaternion & q2, F32 weightA, F32 weightB)const;

	private:
		VECTOR3F v;
		F32 w;

		friend Matrix MatrixRotationQuaternion(const Quaternion & qRot);
	};
}