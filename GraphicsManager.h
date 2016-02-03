#pragma once

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

namespace CS418
{

	/*
	* Initializes and manages the settings of the graphics state.
	*/
	class GraphicsManager
	{
	public:
		GraphicsManager();
		virtual ~GraphicsManager();

		/* Initializes the graphics device */
		void Initialize();

		/* Prepares the scene for drawing */
		void BeginScene();
		/* Presents the rendering result */
		void EndScene();

	private:
		void createWindow();

	private:
#if defined(WIN32) || defined(_WIN32)
		HWND m_hWnd;
		HDC m_hDC;
		HGLRC m_hRC;
#endif
	};

}