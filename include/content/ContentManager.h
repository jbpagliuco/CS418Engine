#pragma once

/*
* ALLOWED FILE EXTENSIONS:
* Shaders:
*	- .vert (GLSL vertex shader)
*	- .frag (GLSL fragment shader)
*/

#include <string.h>
#include <vector>
#include <map>

#include "Util.h"

#include "FileSystem.h"

#include "graphics\ShaderProgram.h"
#include "graphics\Model.h"

namespace CS418
{
	class ContentManager
	{
	public:
		virtual ~ContentManager();
		
		// Processes and loads an asset.
		// - vertexShaderFilepath: The file path to the vertex shader.
		// - fragShaderFilepath:   The file path to the fragment shader.
		virtual ShaderProgram LoadShader(const std::string &vertexShaderFilepath, const std::string fragShaderFilepath);

		virtual 

		// Disposes all data that has been loaded by this content manager.
		virtual void UnloadContent();

	protected:
		ShaderProgram loadGLSL(const char *vertexShaderData, const char *fragShaderData);

	private:
		FileSystem m_fileReader;

		typedef std::map<Vector2<std::string>, ShaderProgram> ShaderArray_t;

		ShaderArray_t m_shaders;
	};
}