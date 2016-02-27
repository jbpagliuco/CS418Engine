#pragma once

#if defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

#include "graphics/Renderer.h"
#include "util/GameTimer.h"

namespace CS418
{
	class Engine;

	/*
	* Initializes and manages the settings of the graphics state.
	*/
	class GraphicsManager
	{
	public:
		GraphicsManager();
		virtual ~GraphicsManager();

		/* Initializes the graphics device */
		void Initialize(Engine * pEngine);

		/* Sets the scene to render */
		void SetScene(Scene * pScene);

		void Update(const GameTimer *gameTimer);

		/* Prepares the scene for drawing */
		void BeginScene();
		/* Presents the rendering result */
		void EndScene();

		void Draw();

		void Resize();
		void Resize(U32 width, U32 height);

		void SetWindowWidth(U32 width);
		void SetWindowHeight(U32 height);
		void SetWindowDimensions(U32 width, U32 height);
		Vector2<U32> GetWindowDimensions()const;

		void SetWindowPositionX(U32 x);
		void SetWindowPositionY(U32 y);
		void SetWindowPosition(U32 x, U32 y);
		Vector2<U32> GetWindowPosition()const;

		void SetFullscreen(bool fullscreen);
		bool IsFullscreen()const;

		void SetWindowTitle(const std::string &title);
		std::string GetWindowTitle()const;

		void SetClearColor(const VECTOR4F &color);
		void SetClearColor(const std::string &color);

	private:
		void createWindow(Engine * pEngine);

	private:
#if defined(WIN32) || defined(_WIN32)
		HWND m_hWnd;
		HDC m_hDC;
		HGLRC m_hRC;
#endif

		U32 m_wWidth, m_wHeight;
		U32 m_wPosX, m_wPosY;
		bool m_fullscreen;
		std::string m_wWindowTitle;

		Scene * m_pScene;

		Renderer m_renderer;
	};

}