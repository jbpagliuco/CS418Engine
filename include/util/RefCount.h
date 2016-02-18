#pragma once

namespace CS418
{
	template <typename SizeType>
	class RefCount
	{
	public:
		RefCount(SizeType initialCount = 0);
		virtual ~RefCount();

		void AddRef();
		SizeType Release();

		SizeType GetCount()const;

	private:
		SizeType m_refCount;
	};
}





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