#pragma once

#include <string>
#include <map>

#include "util/Util.h"

#include "math/Vector.h"
#include "math/Matrix.h"
#include "graphics/textures/Texture2DGL.h"
#include "graphics/textures/TextureCube.h"
#include "graphics/lighting/Lighting.h"

namespace CS418
{
	typedef struct VertexDesc
	{
		VertexDesc()
		{
			positions = normals = texCoords = tangents = colors = false;
		}
		bool positions;
		bool normals;
		bool texCoords;
		bool tangents;
		bool colors;
	}VertexDesc;

	class ShaderProgram
	{
	public:
		~ShaderProgram();

		// Initializes this shader program. Returns false if bad vertex or fragment shader source.
		bool Initialize(std::string vertexShaderSource, std::string fragShaderSource);

		VertexDesc GetVertexDesc()const;

		void SetU32(const std::string &name, U32 value);

		void SetF32(const std::string &name, F32 value);
		void SetVec2f(const std::string &name, VECTOR2F value);
		void SetVec3f(const std::string &name, VECTOR3F value);
		void SetVec4f(const std::string &name, VECTOR4F value);

		void SetMatrix4x4(const std::string &name, const Matrix &value);

		void SetTexture2D(const std::string &name, const Texture2DGL &tex2D, U32 index);
		void SetTextureCube(const std::string &name, const TextureCube &texCube, U32 index);

		void SetLight(const std::string &name, const Light &light);

	private:
		bool compileShaders(std::string vertexShaderSource, std::string fragShaderSource);
		void createInputLayout(std::string vertexShaderSource);
		void getUniformIDs(const std::string &vertexShaderSource, const std::string &fragShaderSource);

	private:
		U32 m_shaderProgram;
		VertexDesc m_vertexDesc;

		std::map<std::string, U32> m_uniforms;

		friend class Renderer;
	};
}