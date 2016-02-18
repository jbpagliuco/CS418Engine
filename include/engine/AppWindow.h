#pragma once

#include "util/Util.h"

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

namespace CS418
{

#if defined(WIN32) || defined(_WIN32)
	typedef HWND WindowHandle;
#endif

	/* Describes a window */
	typedef struct WINDOW_DESC
	{
		Vector2<unsigned int> position;
		Vector2<unsigned int> size;
		const char * caption;
		bool isFullscreen;
	} WINDOW_DESC;

	/* Creates a window and returns the handle based on platform */
	WindowHandle CreateApplicationWindow(const WINDOW_DESC &wd);

}