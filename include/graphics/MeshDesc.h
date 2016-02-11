#pragma once

#include "math\Vector.h"

#include <vector>

namespace CS418
{
	typedef struct Vertex_t
	{
		VECTOR3F position;
		VECTOR3F normal;
		VECTOR2F texCoord;
		VECTOR3F tangent;
	} Vertex_t;

	const U8 VERTEX_ENABLE_POSITION = (1 << 0);
	const U8 VERTEX_ENABLE_NORMAL   = (1 << 1);
	const U8 VERTEX_ENABLE_TEXCOORD = (1 << 2);
	const U8 VERTEX_ENABLE_TANGENT  = (1 << 3);
	const U8 VERTEX_ENABLE_COLOR    = (1 << 4);

	typedef U32 Index_t;

	// Used to hold vertex data that will be sent to the GPU.
	class VertexBuffer
	{
	public:
		~VertexBuffer();

		// Initializes this vertex buffer.
		// - vertices: An array of vertices for this buffer.
		// - VERTEX_ENABLE_FLAG: A single or logically or'ed combination of VERTEX_ENABLE flags, that determine which parameters are part of the vertex.
		void Initialize(const std::vector<Vertex_t> &vertices, U8 VERTEX_ENABLE_FLAG);

	private:
		U32 m_VBO;
	};

	// Used to hold index data that will be sent to the GPU.
	class IndexBuffer
	{
	public:
		~IndexBuffer();

		// Initializes this index buffer.
		// - indices: An array of indices for this buffer.
		void Initialize(const std::vector<Index_t> &indices);

	private:
		U32 m_IBO;
	};

	// Used to describe how vertex data is sent to a shader.
	class InputLayout
	{
	public:
		~InputLayout();

		void Initialize(U8 VERTEX_ENABLE_FLAG);

	private:
		U32 m_inputLayout;
	};
}