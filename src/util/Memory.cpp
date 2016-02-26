#include "util/Memory.h"

#include <assert.h>

#include "util/Util.h"

namespace CS418
{
	void * AllocateUnalignedMemory(size_t sizeInBytes)
	{
		return new byte[sizeInBytes];
	}

	void FreeUnalignedMemory(void * pMem)
	{
		delete[] pMem;
	}

	void * AllocateAligned(size_t sizeInBytes, size_t alignment)
	{
		assert(alignment >= 1);
		assert(alignment <= 128);
		assert((alignment & (alignment - 1)) == 0); // Check to see if power of 2.

		size_t totalMemoryToAllocate = sizeInBytes + alignment;

		uintptr_t rawAddress = reinterpret_cast<uintptr_t>(AllocateUnalignedMemory(totalMemoryToAllocate));

		size_t mask = (alignment - 1);
		uintptr_t offset = (rawAddress & mask);
		ptrdiff_t adjustment = alignment - offset;

		uintptr_t alignedAddress = rawAddress + adjustment;

		assert(adjustment < 256);
		byte * pAlignedMemory = reinterpret_cast<byte*>(alignedAddress);
		pAlignedMemory[-1] = static_cast<byte>(adjustment); // We will always have at least an extra 
																 // byte before the aligned address if the
																 // asserts pass.

		return static_cast<void*>(pAlignedMemory);
	}

	void FreeAlignedMemory(void * pMem)
	{
		const byte * pAlignedMem = reinterpret_cast<byte*>(pMem);
		uintptr_t pAlignedAddress = reinterpret_cast<uintptr_t>(pMem);
		ptrdiff_t adjustment = static_cast<ptrdiff_t>(pAlignedMem[-1]);

		uintptr_t rawAddress = pAlignedAddress - adjustment;
		void * pRawMem = reinterpret_cast<void*>(rawAddress);

		FreeUnalignedMemory(pRawMem);
	}
}