#include "graphics/GraphicsManager.h"

#include <Windows.h>

#include "engine/AppWindow.h"

namespace CS418
{
	GraphicsManager::GraphicsManager()
	{
		m_hWnd = nullptr;
		m_hDC = nullptr;
		m_hRC = nullptr;

		m_isPostProcessing = false;
	}

	GraphicsManager::~GraphicsManager()
	{
		if (m_hRC)
		{
			wglMakeCurrent(nullptr, nullptr);
			wglDeleteContext(m_hRC);
		}
		if (m_hWnd && m_hDC)
		{
			ReleaseDC(m_hWnd, m_hDC);
		}

		m_hWnd = nullptr;
		m_hDC = nullptr;
		m_hRC = nullptr;
	}

	void GraphicsManager::Initialize(Engine * pEngine)
	{
		createWindow(pEngine);

		m_renderer.Initialize(this, &pEngine->GetAssetManager());
	}

	void GraphicsManager::SetScene(Scene * pScene)
	{
		m_pScene = pScene;
		m_renderer.SetScene(pScene);
	}

	void GraphicsManager::Update(const GameTimer *gameTimer)
	{
		m_pScene->Update(gameTimer);
	}

	void GraphicsManager::BeginScene()
	{
		wglMakeCurrent(m_hDC, m_hRC);
	}

	void GraphicsManager::Draw()
	{
		m_renderer.Draw();
	}

	void GraphicsManager::EndScene()
	{
		// Swap front and back buffers
		SwapBuffers(m_hDC);
	}

	void GraphicsManager::Resize()
	{
		RECT R;
		GetClientRect(m_hWnd, &R);
		Resize(R.right - R.left, R.bottom - R.top);
	}

	void GraphicsManager::Resize(U32 width, U32 height)
	{
		m_renderer.Resize(width, height);
	}

	void GraphicsManager::SetWindowWidth(U32 width)
	{
		m_wWidth = width;

		if (m_hWnd)
			SetWindowPos(m_hWnd, nullptr, m_wPosX, m_wPosY, m_wWidth, m_wHeight, 0);
	}
	void GraphicsManager::SetWindowHeight(U32 height)
	{
		m_wHeight = height;

		if (m_hWnd)
			SetWindowPos(m_hWnd, nullptr, m_wPosX, m_wPosY, m_wWidth, m_wHeight, 0);
	}
	void GraphicsManager::SetWindowDimensions(U32 width, U32 height)
	{
		m_wWidth = width;
		m_wHeight = height;

		if (m_hWnd)
			SetWindowPos(m_hWnd, nullptr, m_wPosX, m_wPosY, m_wWidth, m_wHeight, 0);
	}
	Vector2<U32> GraphicsManager::GetWindowDimensions()const
	{
		return Vector2<U32>(m_wWidth, m_wHeight);
	}

	void GraphicsManager::SetWindowPositionX(U32 x)
	{
		m_wPosX = x;

		if (m_hWnd)
			SetWindowPos(m_hWnd, nullptr, m_wPosX, m_wPosY, m_wWidth, m_wHeight, 0);
	}
	void GraphicsManager::SetWindowPositionY(U32 y)
	{
		m_wPosY = y;

		if (m_hWnd)
			SetWindowPos(m_hWnd, nullptr, m_wPosX, m_wPosY, m_wWidth, m_wHeight, 0);
	}
	void GraphicsManager::SetWindowPosition(U32 x, U32 y)
	{
		m_wPosX = x;
		m_wPosY = y;

		if (m_hWnd)
			SetWindowPos(m_hWnd, nullptr, m_wPosX, m_wPosY, m_wWidth, m_wHeight, 0);
	}
	Vector2<U32> GraphicsManager::GetWindowPosition()const
	{
		return Vector2<U32>(m_wPosX, m_wPosY);
	}

	void GraphicsManager::SetFullscreen(bool fullscreen)
	{

	}
	bool GraphicsManager::IsFullscreen()const
	{
		return m_fullscreen;
	}
	
	void GraphicsManager::SetWindowTitle(const std::string &title)
	{
		m_wWindowTitle = std::string(title);

		if (m_hWnd)
			SetWindowText(m_hWnd, m_wWindowTitle.c_str());
	}
	std::string GraphicsManager::GetWindowTitle()const
	{
		return m_wWindowTitle;
	}

	void GraphicsManager::SetClearColor(const VECTOR4F &color)
	{
		m_renderer.SetClearColor(color);
	}
	void GraphicsManager::SetClearColor(const std::string &color)
	{
		m_renderer.SetClearColor(color);
	}

	void GraphicsManager::EnablePostProcessing()
	{
		m_isPostProcessing = true;
	}

	bool GraphicsManager::IsPostProcessing()const
	{
		return m_isPostProcessing;
	}

	void GraphicsManager::createWindow(Engine * pEngine)
	{
		WINDOW_DESC wd;
		wd.caption = m_wWindowTitle.c_str();
		wd.position.X = m_wPosX;
		wd.position.Y = m_wPosY;
		wd.size.X = m_wWidth;
		wd.size.Y = m_wHeight;
		wd.isFullscreen = m_fullscreen;

		m_hWnd = CreateApplicationWindow(wd, pEngine);

		// get the device context (DC)
		m_hDC = GetDC(m_hWnd);

		// set the pixel format for the DC
		PIXELFORMATDESCRIPTOR pfd;
		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;
		pfd.cDepthBits = 16;
		pfd.iLayerType = PFD_MAIN_PLANE;
		int format = ChoosePixelFormat(m_hDC, &pfd);
		SetPixelFormat(m_hDC, format, &pfd);

		// create the render context (RC)
		m_hRC = wglCreateContext(m_hDC);

		// make it the current render context
		wglMakeCurrent(m_hDC, m_hRC);
	}
}