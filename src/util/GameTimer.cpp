#include "util\GameTimer.h"

#include <Windows.h>

namespace CS418
{
	GameTimer::GameTimer()
	{
		m_isPaused = true;

		m_startCount = 0;
		m_pausedCounts = 0;
		m_stoppedCount = 0;
		m_prevCount = 0;

		m_elapsedCounts = 0;

		LARGE_INTEGER largeInt;
		QueryPerformanceFrequency(&largeInt); // Counts per second
		m_secondsPerCount = 1.0 / (double)largeInt.QuadPart;
	}

	GameTimer::~GameTimer()
	{

	}

	void GameTimer::Reset()
	{
		m_isPaused = true;

		LARGE_INTEGER largeInt;
		QueryPerformanceCounter(&largeInt);
		m_startCount = largeInt.QuadPart;

		m_pausedCounts = 0;
		m_stoppedCount = 0;
		m_prevCount = m_startCount;
	}

	void GameTimer::Resume()
	{
		if (m_isPaused)
		{
			LARGE_INTEGER largeInt;
			QueryPerformanceCounter(&largeInt);

			m_pausedCounts += largeInt.QuadPart - m_stoppedCount;

			m_isPaused = false;
		}
	}

	void GameTimer::Pause()
	{
		if (!m_isPaused)
		{
			LARGE_INTEGER largeInt;
			QueryPerformanceCounter(&largeInt);

			m_stoppedCount = largeInt.QuadPart;

			m_isPaused = true;
		}
	}

	void GameTimer::Tick()
	{
		if (m_isPaused)
		{
			m_elapsedCounts = 0;
			return;
		}

		LARGE_INTEGER largeInt;
		QueryPerformanceCounter(&largeInt);

		m_elapsedCounts = largeInt.QuadPart - m_prevCount;
		m_prevCount = largeInt.QuadPart;

		if (m_elapsedCounts < 0)
			m_elapsedCounts = 0;
	}

	bool GameTimer::IsPaused()const
	{
		return m_isPaused;
	}

	F32 GameTimer::GetPlayingTime()const
	{
		__int64 count;
		if (m_isPaused)
			count = m_stoppedCount;
		else
		{
			LARGE_INTEGER largeInt;
			QueryPerformanceCounter(&largeInt);
			count = largeInt.QuadPart;
		}

		return ((count - m_startCount) - m_pausedCounts) * m_secondsPerCount;
	}

	F32 GameTimer::GetTotalGameTime()const
	{
		LARGE_INTEGER largeInt;
		QueryPerformanceCounter(&largeInt);
		return (largeInt.QuadPart - m_startCount) * m_secondsPerCount;
	}

	F32 GameTimer::GetElapsedTimeInSeconds()const
	{
		return (F32)(m_elapsedCounts * m_secondsPerCount);
	}

	F32 GameTimer::GetElapsedTimeInMillis()const
	{
		return m_elapsedCounts * m_secondsPerCount * 1000;
	}
}