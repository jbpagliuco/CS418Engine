#include "graphics/BasicMeshes.h"

namespace CS418
{
	Mesh CreateQuad()
	{
		Mesh m;
		std::vector<Vertex_t> vertices(4);
		std::vector<Index_t> indices;

		vertices.at(0).position = VECTOR3F(-1.0f, -1.0f, 0.0f);
		vertices.at(0).texCoord = VECTOR2F(0.0f, 0.0f);
		vertices.at(0).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		vertices.at(1).position = VECTOR3F(-1.0f, 1.0f, 0.0f);
		vertices.at(1).texCoord = VECTOR2F(0.0f, 1.0f);
		vertices.at(1).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		vertices.at(2).position = VECTOR3F(1.0f, 1.0f, 0.0f);
		vertices.at(2).texCoord = VECTOR2F(1.0f, 1.0f);
		vertices.at(2).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		vertices.at(3).position = VECTOR3F(1.0f, -1.0f, 0.0f);
		vertices.at(3).texCoord = VECTOR2F(1.0f, 0.0f);
		vertices.at(3).normal = VECTOR3F(0.0f, 0.0f, -1.0f);

		indices = { 0, 1, 2, 0, 2, 3 };

		m.Initialize(vertices, indices);

		return m;
	}

	Mesh CreateCube()
	{
		Mesh m;
		std::vector<Vertex_t> vertices(24);
		std::vector<Index_t> indices;

		VECTOR3F LBB = VECTOR3F(-1.0f, -1.0f, -1.0f);
		VECTOR3F LTB = VECTOR3F(-1.0f, +1.0f, -1.0f);
		VECTOR3F RTB = VECTOR3F(+1.0f, +1.0f, -1.0f);
		VECTOR3F RBB = VECTOR3F(+1.0f, -1.0f, -1.0f);
		VECTOR3F LBF = VECTOR3F(-1.0f, -1.0f, +1.0f);
		VECTOR3F LTF = VECTOR3F(-1.0f, +1.0f, +1.0f);
		VECTOR3F RTF = VECTOR3F(+1.0f, +1.0f, +1.0f);
		VECTOR3F RBF = VECTOR3F(+1.0f, -1.0f, +1.0f);

		// Z = -1
		vertices.at(0).position = LBB;
		vertices.at(1).position = LTB;
		vertices.at(2).position = RTB;
		vertices.at(3).position = RBB;

		// Z = +1
		vertices.at(4).position = RBF;
		vertices.at(5).position = RTF;
		vertices.at(6).position = LTF;
		vertices.at(7).position = LBF;

		// X = -1
		vertices.at(8).position = LBF;
		vertices.at(9).position = LTF;
		vertices.at(10).position = LTB;
		vertices.at(11).position = LBB;

		// X = +1
		vertices.at(12).position = RBB;
		vertices.at(13).position = RTB;
		vertices.at(14).position = RTF;
		vertices.at(15).position = RBF;

		// Y = -1
		vertices.at(16).position = LBF;
		vertices.at(17).position = LBB;
		vertices.at(18).position = RBB;
		vertices.at(19).position = RBF;

		// Y = +1
		vertices.at(20).position = LTB;
		vertices.at(21).position = LTF;
		vertices.at(22).position = RTF;
		vertices.at(23).position = RTB;

		vertices.at(0).normal = vertices.at(1).normal = vertices.at(2).normal = vertices.at(3).normal = VECTOR3F(0.0f, 0.0f, -1.0f);
		vertices.at(4).normal = vertices.at(5).normal = vertices.at(6).normal = vertices.at(7).normal = VECTOR3F(0.0f, 0.0f, 1.0f);
		vertices.at(8).normal = vertices.at(9).normal = vertices.at(10).normal = vertices.at(11).normal = VECTOR3F(-1.0f, 0.0f, 0.0f);
		vertices.at(12).normal = vertices.at(13).normal = vertices.at(14).normal = vertices.at(15).normal = VECTOR3F(1.0f, 0.0f, 0.0f);
		vertices.at(16).normal = vertices.at(17).normal = vertices.at(18).normal = vertices.at(19).normal = VECTOR3F(0.0f, -1.0f, 0.0f);
		vertices.at(20).normal = vertices.at(21).normal = vertices.at(22).normal = vertices.at(23).normal = VECTOR3F(0.0f, 1.0f, 0.0f);

		vertices.at(0).texCoord = vertices.at(4).texCoord = vertices.at(8).texCoord = vertices.at(12).texCoord = vertices.at(16).texCoord = vertices.at(20).texCoord = VECTOR2F(0.0f, 0.0f);
		vertices.at(1).texCoord = vertices.at(5).texCoord = vertices.at(9).texCoord = vertices.at(13).texCoord = vertices.at(17).texCoord = vertices.at(21).texCoord = VECTOR2F(0.0f, 1.0f);
		vertices.at(2).texCoord = vertices.at(6).texCoord = vertices.at(10).texCoord = vertices.at(14).texCoord = vertices.at(18).texCoord = vertices.at(22).texCoord = VECTOR2F(1.0f, 1.0f);
		vertices.at(3).texCoord = vertices.at(7).texCoord = vertices.at(11).texCoord = vertices.at(15).texCoord = vertices.at(19).texCoord = vertices.at(23).texCoord = VECTOR2F(1.0f, 0.0f);



		indices = { 
			0, 1, 2, 0, 2, 3,
			4, 5, 6, 4, 6, 7,
			8, 9, 10, 8, 10, 11,
			12, 13, 14, 12, 14, 15,
			16, 17, 18, 16, 18, 19,
			20, 21, 22, 20, 22, 23
		};

		m.Initialize(vertices, indices);

		return m;
	}

	Mesh CreateSphere(F32 radius, U32 slices, U32 stacks)
	{
		Mesh m;
		std::vector<Vertex_t> vertices;
		std::vector<Index_t> indices;

		F32 phiStep = PI / stacks;
		// do not count the poles as rings
		U32 rings = stacks - 1;

		// Compute vertices for each stack ring.
		for (U32 i = 1; i <= rings; ++i)
		{
			float phi = i*phiStep;

			// vertices of ring
			float thetaStep = 2.0f*PI / slices;
			for (U32 j = 0; j <= slices; ++j)
			{
				float theta = j*thetaStep;

				Vertex_t v;

				// spherical to cartesian
				v.position.x = radius*sinf(phi)*cosf(theta);
				v.position.y = radius*cosf(phi);
				v.position.z = radius*sinf(phi)*sinf(theta);

				// partial derivative of P with respect to theta
				v.tangent.x = -radius*sinf(phi)*sinf(theta);
				v.tangent.y = 0.0f;
				v.tangent.z = radius*sinf(phi)*cosf(theta);

				v.normal = Vector(v.position).v3Normalize().asVector3();

				v.texCoord.x = theta / (2.0f*PI);
				v.texCoord.y = phi / PI;

				vertices.push_back(v);
			}
		}

		// poles: note that there will be texture coordinate distortion
		Vertex_t v;
		v.position = VECTOR3F(0.0f, -radius, 0.0f);
		v.tangent = VECTOR3F(1.0f, 0.0f, 0.0f);
		v.normal = VECTOR3F(0.0f, -1.0f, 0.0f);
		v.texCoord = VECTOR2F(0.0f, 1.0f);
		vertices.push_back(v);

		v.position = VECTOR3F(0.0f, radius, 0.0f);
		v.tangent = VECTOR3F(1.0f, 0.0f, 0.0f);
		v.normal = VECTOR3F(0.0f, 1.0f, 0.0f);
		v.texCoord = VECTOR2F(0.0f, 0.0f);
		vertices.push_back(v);

		U32 northPoleIndex = (U32)vertices.size() - 1;
		U32 southPoleIndex = (U32)vertices.size() - 2;

		U32 numRingVertices = slices + 1;

		// Compute indices for inner stacks (not connected to poles).
		for (U32 i = 0; i < stacks - 2; ++i)
		{
			for (U32 j = 0; j < slices; ++j)
			{
				indices.push_back(i*numRingVertices + j);
				indices.push_back(i*numRingVertices + j + 1);
				indices.push_back((i + 1)*numRingVertices + j);

				indices.push_back((i + 1)*numRingVertices + j);
				indices.push_back(i*numRingVertices + j + 1);
				indices.push_back((i + 1)*numRingVertices + j + 1);
			}
		}

		// Compute indices for top stack.  The top stack was written 
		// first to the vertex buffer.
		for (U32 i = 0; i < slices; ++i)
		{
			indices.push_back(northPoleIndex);
			indices.push_back(i + 1);
			indices.push_back(i);
		}

		// Compute indices for bottom stack.  The bottom stack was written
		// last to the vertex buffer, so we need to offset to the index
		// of first vertex in the last ring.
		U32 baseIndex = (rings - 1)*numRingVertices;
		for (U32 i = 0; i < slices; ++i)
		{
			indices.push_back(southPoleIndex);
			indices.push_back(baseIndex + i);
			indices.push_back(baseIndex + i + 1);
		}

		m.Initialize(vertices, indices);

		return m;
	}
}