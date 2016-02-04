#include "math\Quaternion.h"

#include "math\Math.h"

namespace CS418
{
	Quaternion::Quaternion(const Matrix &rotMatrix)
	{
		__declspec(align(16)) F32 R[4][4];
		for (U8 i = 0; i < 4; i++)
			_mm_store_ps(R[i], rotMatrix.m_cols[i]);

		F32 q[4];


		float trace = R[0][0] + R[1][1] + R[2][2];
		// check the diagonal 
		if (trace > 0.0f)
		{
			float s = sqrtf(trace + 1.0f);
			q[3] = s * 0.5f;
			float t = 0.5f / s;
			q[0] = (R[2][1] - R[1][2]) * t;
			q[1] = (R[0][2] - R[2][0]) * t;
			q[2] = (R[1][0] - R[0][1]) * t;
		}
		else
		{ // diagonal is negative 
			int i = 0;
			if (R[1][1] > R[0][0])
				i = 1;
			if (R[2][2] > R[i][i])
				i = 2;
			static const int NEXT[3] = { 1, 2, 0 };
			int j = NEXT[i];
			int k = NEXT[j];
			float s = sqrtf((R[i][j] - (R[j][j] + R[k][k])) + 1.0f);
			q[i] = s * 0.5f;
			float t;
			if (s != 0.0)
				t = 0.5f / s;
			else
				t = s;
			q[3] = (R[k][j] - R[j][k]) * t;
			q[j] = (R[j][i] + R[i][j]) * t;
			q[k] = (R[k][i] + R[i][k]) * t;
		}

		w = q[3];
		v.x = q[0];
		v.y = q[1];
		v.z = q[2];
	}


	Quaternion Quaternion::interpolate(const Quaternion & q1, const Quaternion & q2, F32 weightA, F32 weightB)const
	{
		Quaternion q;

		Vector v1(q1.v.x, q1.v.y, q1.v.z, q1.w);
		Vector v2(q2.v.x, q2.v.y, q2.v.z, q2.w);

		v1 *= weightA;
		v2 *= weightB;

		v1 += v2;

		v1.v4Normalize();

		__declspec(align(16)) F32 vector[4];
		_mm_store_ps(vector, v1.m_elems);

		q.v.x = vector[0];
		q.v.y = vector[1];
		q.v.z = vector[2];
		q.w = vector[3];

		return q;
	}
}