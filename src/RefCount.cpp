#include "util\RefCount.h"

namespace CS418
{
	template <typename SizeType>
	RefCount<SizeType>::RefCount(SizeType initialCount)
	{
		m_refCount = initialCount;
	}

	template <typename SizeType>
	RefCount<SizeType>::~RefCount()
	{

	}

	template <typename SizeType>
	void RefCount<SizeType>::AddRef()
	{
		m_refCount++;
	}

	template <typename SizeType>
	SizeType RefCount<SizeType>::Release()
	{
		if (m_refCount > 0)
			m_refCount--;

		return m_refCount;
	}

	template <typename SizeType>
	SizeType RefCount<SizeType>::GetCount()const
	{
		return m_refCount;
	}
}