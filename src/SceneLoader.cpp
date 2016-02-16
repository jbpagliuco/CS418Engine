#include "content\SceneLoader.h"

#include "util\FileReader.h"
#include <sstream>

namespace CS418
{
	Scene * LoadCS418Scene(AssetManager * assetManager, const std::string &sceneData);


	Scene * LoadScene(AssetManager * assetManager, const std::string &sceneFilepath)
	{
		FileReader fileReader;
		Scene * pScene;

		fileReader.Open(sceneFilepath);
		if (fileReader.GetFileExtension() == ".cs418scene")
		{
			std::string sceneData = fileReader.FileAsString();
			pScene = LoadCS418Scene(assetManager, sceneData);
		}
		else
			pScene = nullptr;

		fileReader.Close();

		return pScene;
	}


	Scene * LoadCS418Scene(AssetManager * assetManager, const std::string &sceneData)
	{
		std::istringstream stream(sceneData);
		std::string line;


		while (std::getline(stream, line))
		{
			
		}
	}
}