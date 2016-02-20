#pragma once

#include "util\Util.h"

namespace CS418
{
	class GameTimer
	{
	public:
		GameTimer();
		~GameTimer();

	public:
		/*
		Reset's the game timer. Calling this method does not make the timer run again; in order for
		the timer to run GameTimer.resume() must be called, and GameTimer.tick() must be
		update the timer.
		*/
		void Reset();

		/*
		Pauses the GameTimer. Does nothing if the GameTimer was already in a paused state.
		*/
		void Pause();

		/*
		Either resume's the timer from a paused state, or starts the timer from a dead state (GameTimer.reset() has just been called).
		Does nothing if GameTimer was not in a paused state.
		*/
		void Resume();

		/*
		Updates the GameTimer and calculates elapsed time.
		*/
		void Tick();

		/*
		Returns true if this is paused.
		*/
		bool IsPaused()const;

		/*
		Calculates the time since the GameTimer was reset, not including
		time where the GameTimer was paused.
		*/
		D64 GetPlayingTime()const;

		/*
		Calculates the total amount of time since the GameTimer was reset,
		including times where the GameTimer was paused.
		*/
		D64 GetTotalGameTime()const;

		/*
		Calculated the time (in seconds) of the elapsed time between the last
		two successive GameTimer.tick() calls.
		*/
		D64 GetElapsedTimeInSeconds()const;

		/*
		Calculates the time (in milliseconds) of the elapsed time between the last
		two successive GameTimer.tick() calls.
		*/
		D64 GetElapsedTimeInMillis()const;

	private:
		bool m_isPaused;

		I64 m_startCount; // since reset()
		I64 m_pausedCounts; // pause() to resume()
		I64 m_stoppedCount; // at pause()
		I64 m_prevCount;

		I64 m_elapsedCounts;

		D64 m_secondsPerCount;
	};
}