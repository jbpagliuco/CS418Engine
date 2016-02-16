#pragma once

namespace CS418
{
	template <typename SizeType>
	class RefCount
	{
	public:
		RefCount(SizeType initialCount = 0)
		virtual ~RefCount();

		void AddRef();
		SizeType Release();

		SizeType GetCount()const;

	private:
		SizeType m_refCount;
	};
}