#include "math/Quaternion.h"

#include "math/Math.h"
#include <assert.h>

#include "util/Util.h"

namespace CS418
{
	Quaternion::Quaternion()
	{

	}

	Quaternion::Quaternion(F32 xAxis, F32 yAxis, F32 zAxis, F32 angleInRadians)
	{
		assert(FEquals(xAxis * xAxis + yAxis * yAxis + zAxis * zAxis, 1)); // Unit length!

		w = cosf(angleInRadians / 2.0f);

		F32 sinThetaDiv2 = sinf(angleInRadians / 2.0f);
		v.x = sinThetaDiv2 * xAxis;
		v.y = sinThetaDiv2 * yAxis;
		v.z = sinThetaDiv2 * zAxis;
	}

	Quaternion::Quaternion(const VECTOR3F * pAxis, F32 angleInRadians)
	{
		assert(FEquals(pAxis->x * pAxis->x + pAxis->y * pAxis->y + pAxis->z * pAxis->z, 1)); // Unit length!

		w = cosf(angleInRadians / 2.0f);

		F32 sinThetaDiv2 = sinf(angleInRadians / 2.0f);
		v.x = sinThetaDiv2 * pAxis->x;
		v.y = sinThetaDiv2 * pAxis->y;
		v.z = sinThetaDiv2 * pAxis->z;
	}

	Quaternion & Quaternion::invert()
	{
		v.x *= -1;
		v.y *= -1;
		v.z *= -1;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion &other)const
	{
		Quaternion q;

		Vector v1(v);
		Vector v2(other.v);

		F32 dot = v1.v3Dot(v2);
		Vector cross = v1.v3Cross(v2);

		q.w = w * other.w - dot;
		q.v = ((v1 * other.w) + (v2 * w) + cross).asVector3();

		return q;
	}

	Quaternion & Quaternion::operator*=(const Quaternion &other)
	{
		Vector v1(v);
		Vector v2(other.v);

		F32 dot = v1.v3Dot(v2);
		Vector cross = v1.v3Cross(v2);

		w = w * other.w + dot;
		v = ((v1 * other.w) + (v2 * w) + cross).asVector3();

		return *this;
	}

	VECTOR3F Quaternion::operator*(const VECTOR3F &vector)const
	{
		Vector v1(v);
		Vector v2(vector);

		Vector v1Crossv2 = v1.v3Cross(v2);
		return (v2 + (v1Crossv2 * (2 * w)) + (v1.v3Cross(v1Crossv2) * 2)).asVector3();
	}

	F32 Quaternion::getX()const
	{
		return v.x;
	}

	F32 Quaternion::getY()const
	{
		return v.y;
	}

	F32 Quaternion::getZ()const
	{
		return v.z;
	}

	F32 Quaternion::getW()const
	{
		return w;
	}

	Quaternion Quaternion::lerp(const Quaternion &other, F32 t)const
	{
		return interpolate(*this, other, 1.0f - t, t);
	}

	Quaternion Quaternion::slerp(const Quaternion &other, F32 t)const
	{
		F32 theta = acosf(v.x * other.v.x + v.y * other.v.y + v.z * other.v.z + w * other.w);
		F32 sinTheta = sinf(theta);

		F32 weightA = sinf((1.0f - t) * theta) / sinTheta;
		F32 weightB = sinf((t)* theta) / sinTheta;

		return interpolate(*this, other, weightA, weightB);
	}
}