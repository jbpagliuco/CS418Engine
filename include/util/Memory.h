#pragma once

namespace CS418
{
	/*
	* Allocates "sizeInBytes" amount of bytes in memory,
	* and returns a pointer to the beginning of the
	* memory.
	*/
	void * AllocateUnalignedMemory(size_t sizeInBytes);

	/*
	* Frees a chunk of unaligned memory.
	*/
	void FreeUnalignedMemory(void * pMem);

	/*
	* Allocates "sizeInBytes" amount of bytes with an address
	* alignment of "alignment". The resulting offset is packed
	* into the last byte.
	*
	* "alignment" must be a power of two.
	*
	* Returns a pointer to the beginning of the *aligned* memory.
	*/
	void * AllocateAligned(size_t sizeInBytes, size_t alignment);

	/*
	* Frees a chunk of aligned memory. You must use
	* this method if you allocate aligned memory with the
	* function KPAllocateAligned(...) in order to free all
	* associated memory.
	*/
	void FreeAlignedMemory(void * pMem);
}