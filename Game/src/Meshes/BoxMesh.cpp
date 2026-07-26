#include "BoxMesh.h"

#include "Slate/Graphics/Renderer.h"
#include "Slate/Graphics/Vertex.h"

#include <vector>

Slate::Mesh3DHandle CreateBoxMesh(Slate::Renderer& renderer)
{
	const std::vector<Slate::Vertex3D> vertices
	{
		// Front
		{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f } },
		{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f } },
		{ {  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f } },
		{ { -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f } },

		// Back
		{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f } },
		{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f } },
		{ {  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f } },
		{ { -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f } },

		// Top
		{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f } },
		{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f } },
		{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f } },
		{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f } },

		// Bottom
		{ { -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f } },
		{ {  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f } },
		{ {  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f } },
		{ { -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f } },

		// Right
		{ {  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f } },
		{ {  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f } },
		{ {  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f } },
		{ {  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f } },

		// Left
		{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f } },
		{ { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f } },
		{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f } },
		{ { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f } }
	};

	const std::vector<unsigned int> indices
	{
		 0,  1,  2,  0,  2,  3,
		 4,  6,  5,  4,  7,  6,
		 8,  9, 10,  8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	return renderer.CreateMesh3D(vertices, indices);
}
