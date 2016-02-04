#include "math/Vector.h"

#include "math/VectorUtilMSVC.h"

#include "math\Math.h"

namespace CS418
{
	Vector::Vector()
	{

	}

	Vector::Vector(F32 all)
	{
		m_elems = _mm_set_ps1(all);
	}

	Vector::Vector(F32 x, F32 y, F32 z, F32 w)
	{
		__declspec(align(16)) F32 v[4] = { x, y, z, w };
		m_elems = _mm_load_ps(v);
	}

	Vector::Vector(const VECTOR2 &vector)
	{
		__declspec(align(16)) F32 v[4] = { vector.x, vector.y, 0.0f, 0.0f };
		m_elems = _mm_load_ps(v);
	}

	Vector::Vector(const VECTOR2A &vector)
	{
		m_elems = _mm_load_ps(&vector.x);
	}

	Vector::Vector(const VECTOR3 &vector)
	{
		__declspec(align(16)) F32 v[4] = { vector.x, vector.y, vector.z, 0.0f };
		m_elems = _mm_load_ps(v);
	}

	Vector::Vector(const VECTOR3A &vector)
	{
		m_elems = _mm_load_ps(&vector.x);
	}

	Vector::Vector(const VECTOR4 &vector)
	{
		__declspec(align(16)) F32 v[4] = { vector.x, vector.y, vector.z, vector.w };
		m_elems = _mm_load_ps(v);
	}

	Vector::Vector(const VECTOR4A &vector)
	{
		m_elems = _mm_load_ps(&vector.x);
	}

	Vector::Vector(__m128 vector)
	{
		m_elems = vector;
	}





	VECTOR2 Vector::asVector2()const
	{
		__declspec(align(16)) float vector[4];
		_mm_store_ps(vector, m_elems);
		return VECTOR2(vector);
	}

	VECTOR2A Vector::asVector2A()const
	{
		__declspec(align(16)) float vector[4];
		_mm_store_ps(vector, m_elems);
		return VECTOR2A(vector);
	}

	VECTOR3 Vector::asVector3()const
	{
		__declspec(align(16)) float vector[4];
		_mm_store_ps(vector, m_elems);
		return VECTOR3(vector);
	}

	VECTOR3A Vector::asVector3A()const
	{
		__declspec(align(16)) float vector[4];
		_mm_store_ps(vector, m_elems);
		return VECTOR3A(vector);
	}

	VECTOR4 Vector::asVector4()const
	{
		__declspec(align(16)) float vector[4];
		_mm_store_ps(vector, m_elems);
		return VECTOR4(vector);
	}

	VECTOR4A Vector::asVector4A()const
	{
		__declspec(align(16)) float vector[4];
		_mm_store_ps(vector, m_elems);
		return VECTOR4A(vector);
	}





	F32 Vector::getX()const
	{
		return _mm_cvtss_f32(m_elems);
	}

	F32 Vector::getY()const
	{
		__m128 v = _mm_shuffle_ps(m_elems, m_elems, _MM_SHUFFLE(0, 0, 0, 1));
		return _mm_cvtss_f32(v);
	}

	F32 Vector::getZ()const
	{
		__declspec(align(16)) float v[4];
		_mm_store_ps(v, m_elems);

		return v[2];

		//__m128 v = _mm_shuffle_ps(m_elems, m_elems, _MM_SHUFFLE(0, 0, 0, 2));
		//return _mm_cvtss_f32(v);
	}

	F32 Vector::getW()const
	{
		__m128 v = _mm_shuffle_ps(m_elems, m_elems, _MM_SHUFFLE(0, 0, 0, 3));
		return _mm_cvtss_f32(v);
	}





	VECTOR2 Vector::v2equals(const Vector &other, F32 epsilon)const
	{
		__declspec(align(16)) F32 vResult[4];
		m128cmp(m_elems, other.m_elems, epsilon, vResult);

		return VECTOR2(vResult[0] != 0, vResult[1] != 0);
	}

	VECTOR2 Vector::v2notEquals(const Vector &other, F32 epsilon)const
	{
		__declspec(align(16)) F32 vResult[4];
		m128cmp(m_elems, other.m_elems, epsilon, vResult);

		return VECTOR2(vResult[0] == 0, vResult[1] == 0);
	}

	VECTOR3 Vector::v3equals(const Vector &other, F32 epsilon)const
	{
		__declspec(align(16)) F32 vResult[4];
		m128cmp(m_elems, other.m_elems, epsilon, vResult);

		return VECTOR3(vResult[0] != 0, vResult[1] != 0, vResult[2] != 0);
	}

	VECTOR3 Vector::v3notEquals(const Vector &other, F32 epsilon)const
	{
		__declspec(align(16)) F32 vResult[4];
		m128cmp(m_elems, other.m_elems, epsilon, vResult);

		return VECTOR3(vResult[0] == 0, vResult[1] == 0, vResult[2] == 0);
	}

	VECTOR4 Vector::v4equals(const Vector &other, F32 epsilon)const
	{
		__declspec(align(16)) F32 vResult[4];
		m128cmp(m_elems, other.m_elems, epsilon, vResult);

		return VECTOR4(vResult[0] != 0, vResult[1] != 0, vResult[2] != 0, vResult[3] != 0);
	}

	VECTOR4 Vector::v4notEquals(const Vector &other, F32 epsilon)const
	{
		__declspec(align(16)) F32 vResult[4];
		m128cmp(m_elems, other.m_elems, epsilon, vResult);

		return VECTOR4(vResult[0] == 0, vResult[1] == 0, vResult[2] == 0, vResult[3] == 0);
	}





	VECTOR2 Vector::v2less(const Vector &other)const
	{
		__m128 vResult = _mm_cmplt_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR2(f[0] != 0, f[1] != 0);
	}

	VECTOR2 Vector::v2lessEq(const Vector &other)const
	{
		__m128 vResult = _mm_cmple_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR2(f[0] != 0, f[1] != 0);
	}

	VECTOR2 Vector::v2greater(const Vector &other)const
	{
		__m128 vResult = _mm_cmpgt_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR2(f[0] != 0, f[1] != 0);
	}

	VECTOR2 Vector::v2greaterEq(const Vector &other)const
	{
		__m128 vResult = _mm_cmpge_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR2(f[0] != 0, f[1] != 0);
	}

	VECTOR3 Vector::v3less(const Vector &other)const
	{
		__m128 vResult = _mm_cmplt_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR3(f[0] != 0, f[1] != 0, f[2] != 0);
	}

	VECTOR3 Vector::v3lessEq(const Vector &other)const
	{
		__m128 vResult = _mm_cmple_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR3(f[0] != 0, f[1] != 0, f[2] != 0);
	}

	VECTOR3 Vector::v3greater(const Vector &other)const
	{
		__m128 vResult = _mm_cmpgt_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR3(f[0] != 0, f[1] != 0, f[2] != 0);
	}

	VECTOR3 Vector::v3greaterEq(const Vector &other)const
	{
		__m128 vResult = _mm_cmpge_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR3(f[0] != 0, f[1] != 0, f[2] != 0);
	}

	VECTOR4 Vector::v4less(const Vector &other)const
	{
		__m128 vResult = _mm_cmplt_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR4(f[0] != 0, f[1] != 0, f[2] != 0, f[3] != 0);
	}

	VECTOR4 Vector::v4lessEq(const Vector &other)const
	{
		__m128 vResult = _mm_cmple_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR4(f[0] != 0, f[1] != 0, f[2] != 0, f[3] != 0);
	}

	VECTOR4 Vector::v4greater(const Vector &other)const
	{
		__m128 vResult = _mm_cmpgt_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR4(f[0] != 0, f[1] != 0, f[2] != 0, f[3] != 0);
	}

	VECTOR4 Vector::v4greaterEq(const Vector &other)const
	{
		__m128 vResult = _mm_cmpge_ps(m_elems, other.m_elems);
		__declspec(align(16)) float f[4];
		_mm_store_ps(f, vResult);

		return VECTOR4(f[0] != 0, f[1] != 0, f[2] != 0, f[3] != 0);
	}





	Vector Vector::operator+(const Vector &other)const
	{
		return Vector(_mm_add_ps(m_elems, other.m_elems));
	}

	Vector & Vector::operator+=(const Vector &other)
	{
		m_elems = _mm_add_ps(m_elems, other.m_elems);
		return *this;
	}

	Vector Vector::operator-(const Vector &other)const
	{
		return Vector(_mm_sub_ps(m_elems, other.m_elems));
	}

	Vector & Vector::operator-=(const Vector &other)
	{
		m_elems = _mm_sub_ps(m_elems, other.m_elems);
		return *this;
	}
	
	Vector Vector::operator*(const Vector &other)const
	{
		return Vector(_mm_mul_ps(m_elems, other.m_elems));
	}

	Vector Vector::operator*=(const Vector &other)
	{
		m_elems = _mm_mul_ps(m_elems, other.m_elems);
		return *this;
	}

	Vector Vector::operator*(F32 scalar)const
	{
		__m128 scalarAsVector = _mm_set_ps1(scalar);
		return Vector(_mm_mul_ps(m_elems, scalarAsVector));
	}

	Vector Vector::operator*=(F32 scalar)
	{
		__m128 scalarAsVector = _mm_set_ps1(scalar);
		m_elems = _mm_mul_ps(m_elems, scalarAsVector);
		return *this;
	}

	Vector Vector::operator/(const Vector &other)const
	{
		return Vector(_mm_div_ps(m_elems, other.m_elems));
	}

	Vector Vector::operator/=(const Vector &other)
	{
		m_elems = _mm_div_ps(m_elems, other.m_elems);
		return *this;
	}

	Vector Vector::operator/(F32 scalar)const
	{
		__m128 scalarAsVector = _mm_set_ps1(scalar);
		return Vector(_mm_div_ps(m_elems, scalarAsVector));
	}

	Vector Vector::operator/=(F32 scalar)
	{
		__m128 scalarAsVector = _mm_set_ps1(scalar);
		m_elems = _mm_div_ps(m_elems, scalarAsVector);
		return *this;
	}





	Vector & Vector::absoluteValue()
	{
		m128abs(m_elems);

		return *this;
	}

	Vector & Vector::negate()
	{
		m_elems = _mm_sub_ps(_mm_set_ps1(0.0f), m_elems);

		return *this;
	}

	Vector Vector::lerp(const Vector &other, F32 t)const
	{
		Vector v1 = *this;
		Vector v2 = other;

		v1 *= (1.0f - t);
		v2 *= t;

		v1 += v2;

		return v1;
	}




	F32 Vector::v2Dot(const Vector &other)const
	{
		__m128 vMul = _mm_mul_ps(m_elems, other.m_elems);
		__m128 vMulYXZW = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(3, 2, 0, 1));
		__m128 vResult = _mm_add_ps(vMul, vMulYXZW);

		return _mm_cvtss_f32(vResult);
	}

	F32 Vector::v3Dot(const Vector &other)const
	{
		__m128 vMul = _mm_mul_ps(m_elems, other.m_elems);
		__m128 vMulYXXX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 0, 0, 1));
		__m128 vMulZXXX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 0, 0, 2));
		__m128 vResult = _mm_add_ps(vMul, vMulYXXX);
		vResult = _mm_add_ps(vResult, vMulZXXX);

		return _mm_cvtss_f32(vResult);
	}

	F32 Vector::v4Dot(const Vector &other)const
	{
		__m128 vMul = _mm_mul_ps(m_elems, other.m_elems);
		__m128 vMulWZYX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 1, 2, 3));
		__m128 vResult = _mm_add_ps(vMul, vMulWZYX);
		__m128 vResultYXXX = _mm_shuffle_ps(vResult, vResult, _MM_SHUFFLE(0, 0, 0, 1));
		vResult = _mm_add_ps(vResult, vResultYXXX);

		return _mm_cvtss_f32(vResult);
	}





	F32 Vector::v2Length()const
	{
		__m128 vMul = _mm_mul_ps(m_elems, m_elems);
		__m128 vMulYXZW = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(3, 2, 0, 1));
		__m128 vResult = _mm_add_ps(vMul, vMulYXZW);

		return _mm_cvtss_f32(_mm_sqrt_ss(vResult));
	}

	F32 Vector::v2LengthSq()const
	{
		__m128 vMul = _mm_mul_ps(m_elems, m_elems);
		__m128 vMulYXZW = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(3, 2, 0, 1));
		__m128 vResult = _mm_add_ps(vMul, vMulYXZW);

		return _mm_cvtss_f32(vResult);
	}

	F32 Vector::v3Length()const
	{
		__m128 vMul = _mm_mul_ps(m_elems, m_elems);
		__m128 vMulYXXX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 0, 0, 1));
		__m128 vMulZXXX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 0, 0, 2));
		__m128 vResult = _mm_add_ps(vMul, vMulYXXX);
		vResult = _mm_add_ps(vResult, vMulZXXX);

		return _mm_cvtss_f32(_mm_sqrt_ss(vResult));
	}

	F32 Vector::v3LengthSq()const
	{
		__m128 vMul = _mm_mul_ps(m_elems, m_elems);
		__m128 vMulYXXX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 0, 0, 1));
		__m128 vMulZXXX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 0, 0, 2));
		__m128 vResult = _mm_add_ps(vMul, vMulYXXX);
		vResult = _mm_add_ps(vResult, vMulZXXX);

		return _mm_cvtss_f32(vResult);
	}

	F32 Vector::v4Length()const
	{
		__m128 vMul = _mm_mul_ps(m_elems, m_elems);
		__m128 vMulWZYX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 1, 2, 3));
		__m128 vResult = _mm_add_ps(vMul, vMulWZYX);
		__m128 vResultYXXX = _mm_shuffle_ps(vResult, vResult, _MM_SHUFFLE(0, 0, 0, 1));
		vResult = _mm_add_ps(vResult, vResultYXXX);

		return _mm_cvtss_f32(_mm_sqrt_ss(vResult));
	}

	F32 Vector::v4LengthSq()const
	{
		__m128 vMul = _mm_mul_ps(m_elems, m_elems);
		__m128 vMulWZYX = _mm_shuffle_ps(vMul, vMul, _MM_SHUFFLE(0, 1, 2, 3));
		__m128 vResult = _mm_add_ps(vMul, vMulWZYX);
		__m128 vResultYXXX = _mm_shuffle_ps(vResult, vResult, _MM_SHUFFLE(0, 0, 0, 1));
		vResult = _mm_add_ps(vResult, vResultYXXX);

		return _mm_cvtss_f32(vResult);
	}





	Vector & Vector::v2Normalize()
	{
		F32 length = v2Length();

		__m128 vLength = _mm_set_ps1(length); // Could make reciprocal?
		m_elems = _mm_div_ps(m_elems, vLength);

		return *this;
	}

	Vector & Vector::v3Normalize()
	{
		F32 length = v3Length();

		__m128 vLength = _mm_set_ps1(length); // Could make reciprocal?
		m_elems = _mm_div_ps(m_elems, vLength);

		return *this;
	}

	Vector & Vector::v4Normalize()
	{
		F32 length = v4Length();

		__m128 vLength = _mm_set_ps1(length); // Could make reciprocal?
		m_elems = _mm_div_ps(m_elems, vLength);

		return *this;
	}






	Vector Vector::v3Cross(const Vector &other)const
	{
		__m128 result = _mm_sub_ps(
			_mm_mul_ps(m_elems, _mm_shuffle_ps(other.m_elems, other.m_elems, _MM_SHUFFLE(3, 0, 2, 1))),
			_mm_mul_ps(other.m_elems, _mm_shuffle_ps(m_elems, m_elems, _MM_SHUFFLE(3, 0, 2, 1))));

		return Vector(_mm_shuffle_ps(result, result, _MM_SHUFFLE(3, 0, 2, 1)));
	}





	F32 Vector::v2AngleBetween(const Vector &other)const
	{
		return acosf(v2Dot(other) / (v2Length() * other.v2Length()));
	}

	F32 Vector::v2AngleBetweenNormals(const Vector &other)const
	{
		return acosf(v2Dot(other));
	}

	F32 Vector::v3AngleBetween(const Vector &other)const
	{
		return acosf(v3Dot(other) / (v3Length() * other.v3Length()));
	}

	F32 Vector::v3AngleBetweenNormals(const Vector &other)const
	{
		return acosf(v3Dot(other));
	}

	F32 Vector::v4AngleBetween(const Vector &other)const
	{
		return acosf(v4Dot(other) / (v4Length() * other.v4Length()));
	}

	F32 Vector::v4AngleBetweenNormals(const Vector &other)const
	{
		return acosf(v4Dot(other));
	}





	Vector VectorZero()
	{
		Vector result;

		result.m_elems = _mm_setzero_ps();

		return result;
	}
}