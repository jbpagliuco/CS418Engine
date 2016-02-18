#include "engine/Engine.h"

#include "util/ConfigFileReader.h"

namespace CS418
{
	Engine::~Engine()
	{
	}

	void Engine::Initialize()
	{
		m_gfx.Initialize();
		readConfigFile();
	}

	int Engine::Update()
	{
		return 0;
	}

	void Engine::Draw()
	{
		m_gfx.BeginScene();
		m_gfx.Draw();
		m_gfx.EndScene();
	}

	void Engine::readConfigFile()
	{
		ConfigFileReader reader;
		reader.Open("startup.config");

		std::string line;
		while (!reader.EndOfFile())
		{
			std::string key, value;
			reader.ReadKeyAndValue(key, value);

			dispatchKeyAndValue(key, value);
		}

		reader.Close();
	}

	void Engine::dispatchKeyAndValue(const std::string &key, const std::string &value)
	{
		if (key == "Window Title")
			m_gfx.SetWindowTitle(value);
		else if (key == "Window Width")
			m_gfx.SetWindowWidth(std::stoul(value));
		else if (key == "Window Height")
			m_gfx.SetWindowHeight(std::stoul(value));
		else if (key == "Window Position X")
			m_gfx.SetWindowPositionX(std::stoul(value));
		else if (key == "Window Position Y")
			m_gfx.SetWindowPositionY(std::stoul(value));
		else if (key == "Fullscreen")
			m_gfx.SetFullscreen((value == "true"));
		else if (key == "Background Color")
			m_gfx.SetClearColor(value);
		else if (key == "Target FPS")
		{

		}
		else if (key == "Default Scene")
		{
			Scene * pScene = m_assetManager.LoadScene(value);
			m_gfx.SetScene(pScene);
		}
	}
}