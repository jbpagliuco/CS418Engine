/* A graphics manager for OpenGL. */
#include "GraphicsManager.h"

#include <GL\GL.h>
#include <Windows.h>

#include "AppWindow.h"

CS418::GraphicsManager::GraphicsManager()
{
	m_hWnd = nullptr;
	m_hDC = nullptr;
	m_hRC = nullptr;
}

CS418::GraphicsManager::~GraphicsManager()
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

void CS418::GraphicsManager::Initialize()
{
	createWindow();

	// Set clear color to cornflower blue
	glClearColor(0.396f, 0.612f, .937f, 1.0f);
	// Set polygon mode to fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Set line point size
	glPointSize(4.0f);
}

void CS418::GraphicsManager::BeginScene()
{
	wglMakeCurrent(m_hDC, m_hRC);

	// Clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CS418::GraphicsManager::EndScene()
{
	// Swap front and back buffers
	SwapBuffers(m_hDC);
}

void CS418::GraphicsManager::createWindow()
{
	CS418::WINDOW_DESC wd;
	wd.caption = "Window Title";
	wd.position.X = wd.position.Y = 100;
	wd.size.X = 800;
	wd.size.Y = 600;

	m_hWnd = CreateApplicationWindow(wd);

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