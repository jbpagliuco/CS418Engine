#pragma once

#include <stdint.h>

#ifndef CS418_ALIGN_MS
#if _MSC_VER && !__INTEL_COMPILER
#define CS418_ALIGN_MS(alignment) __declspec(align(alignment))
#else
#define CS418_ALIGN_MS(alignment)
#endif
#endif

#ifndef CS418_ALIGN_GCC
#if __GNUC__
#define CS418_ALIGN_GCC(alignment) __attribute__((aligned(alignment)))
#else
#define CS418_ALIGN_GCC(alignment)
#endif
#endif

namespace CS418
{
	typedef uint8_t byte;

	typedef int8_t I8;
	typedef uint8_t U8;

	typedef int16_t I16;
	typedef uint16_t U16;

	typedef int32_t I32;
	typedef uint32_t U32;

	typedef int64_t I64;
	typedef uint64_t U64;

	typedef float F32;
	typedef long double D64;

	/* Holds 2 components */
	template <typename T>
	struct Vector2
	{
		T X;
		T Y;
	};

	/* Holds 3 components */
	template <typename T>
	struct Vector3
	{
		T X;
		T Y;
		T Z;
	};

	/* Holds 4 components */
	template <typename T>
	struct Vector4
	{
		T X;
		T Y;
		T Z;
		T W;
	};
}