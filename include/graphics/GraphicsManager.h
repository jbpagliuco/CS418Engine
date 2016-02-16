#pragma once

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

#include "graphics\Renderer.h"

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

		/* Sets the scene to render */
		void SetScene(Scene * pScene);

		/* Prepares the scene for drawing */
		void BeginScene();
		/* Presents the rendering result */
		void EndScene();

		void Draw();

	private:
		void createWindow();

	private:
#if defined(WIN32) || defined(_WIN32)
		HWND m_hWnd;
		HDC m_hDC;
		HGLRC m_hRC;
#endif

		Renderer m_renderer;
	};

}