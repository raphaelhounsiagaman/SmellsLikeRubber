#include "StartLayer.h"

#include <vector>

StartLayer::StartLayer()
{
	const std::vector<Slate::Vertex3D> boxVertices
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

	const std::vector<unsigned int> boxIndices
	{
		0,  1,  2,  0,  2,  3,
		 4,  6,  5,  4,  7,  6,
		 8,  9, 10,  8, 10, 11,
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	m_Box.Mesh = m_Renderer.CreateMesh3D(boxVertices, boxIndices);
	m_Box.Material = m_Renderer.CreateMaterial(Slate::Color(230, 90, 25));

	// A normalized quaternion that tilts the cube around both X and Y.
	m_Box.Transform.Rotation =
		Slate::Quaternion(0.2418448f, 0.2418448f, 0.0f, 0.9396926f);

	m_Camera.Transform.Position = { 0.0f, 0.0f, -3.0f };
}

void StartLayer::OnEvent(Slate::Event& event)
{
	// Handle camera movement.

}

void StartLayer::OnUpdate(float ts)
{

}


void StartLayer::OnRender()
{
	m_Renderer.SetCamera3D(m_Camera);
	m_Renderer.DrawMesh3D(
		m_Box.Mesh,
		m_Box.Material,
		m_Box.Transform
	);
}
