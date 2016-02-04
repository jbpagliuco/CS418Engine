#pragma once

#pragma once

#include <xmmintrin.h>
#include "Util.h"

#ifndef _MM_SHUFFLE_PARAM
#define _MM_SHUFFLE_PARAM(x, y, z, w) ((x) | (y << 2) | (z << 4) | (w << 6))
#endif // _MM_SHUFFLE_PARAM

#ifndef _MM_REPLICATE_X_PS
#define _MM_REPLICATE_X_PS(v) _mm_shuffle_ps((v), (v), _MM_SHUFFLE_PARAM(0, 0, 0, 0))
#endif // _MM_REPLICATE_X_PS

#ifndef _MM_REPLICATE_Y_PS
#define _MM_REPLICATE_Y_PS(v) _mm_shuffle_ps((v), (v), _MM_SHUFFLE_PARAM(1, 1, 1, 1))
#endif // _MM_REPLICATE_Y_PS

#ifndef _MM_REPLICATE_Z_PS
#define _MM_REPLICATE_Z_PS(v) _mm_shuffle_ps((v), (v), _MM_SHUFFLE_PARAM(2, 2, 2, 2))
#endif // _MM_REPLICATE_Z_PS

#ifndef _MM_REPLICATE_W_PS
#define _MM_REPLICATE_W_PS(v) _mm_shuffle_ps((v), (v), _MM_SHUFFLE_PARAM(3, 3, 3, 3))
#endif // _MM_REPLICATE_W_PS

#ifndef _MM_MADD_PS
#define _MM_MADD_PS(v1, v2, v3) _mm_add_ps(_mm_mul_ps((v1), (v2)), (v3))
#endif // _MM_MADD_PS

namespace CS418
{
	// Compares first and second for equality.
	void m128cmp(const __m128 &first, const __m128 &second, F32 epsilon, F32 pOutData[4]);

	// Computes the absolute value of the __m128 vector.
	void m128abs(__m128 &vector);
}