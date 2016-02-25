#include "engine/Engine.h"

#include "util/ConfigFileReader.h"
#include <sstream>

namespace CS418
{
	Engine::~Engine()
	{
	}

	void Engine::Initialize()
	{
		m_luaManager.Initialize();
		m_assetManager.Initialize(&m_luaManager);
		
		readConfigFile("startup.config");
		m_gfx.Initialize();
		readConfigFile("startup.graphics.config");


		m_gameTimer.Reset();
		m_gameTimer.Resume();
	}

	int Engine::Update()
	{
		static U32 frameCount = 0;
		static F32 baseTime = 0.0f;
		frameCount++;

		m_gameTimer.Tick();

		if ((m_gameTimer.GetTotalGameTime() - baseTime) >= 1.0f)
		{
			F32 fps = (F32)frameCount;
			F32 mspf = 1000.0f / fps;

			std::string frameStats;
			std::ostringstream out;
			out << "FPS: " << fps << ", Milliseconds Per Frame: " << mspf << "\n";
			frameStats = out.str();
			printf("%s", frameStats.c_str());
			
			std::ostringstream out2;
			out2 << m_gameTimer.GetElapsedTimeInMillis();
			printf("%s\n", out2.str().c_str());
			printf("-------------------------------------------------------------\n");

			frameCount = 0;
			baseTime += 1.0f;
		}

		m_gfx.Update(m_gameTimer);

		return 0;
	}

	void Engine::Draw()
	{
		m_gfx.BeginScene();
		m_gfx.Draw();
		m_gfx.EndScene();
	}

	void Engine::readConfigFile(const std::string &file)
	{
		ConfigFileReader reader;
		reader.Open(file);

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