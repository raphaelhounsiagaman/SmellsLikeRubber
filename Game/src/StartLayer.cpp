#include "StartLayer.h"

#include <vector>

StartLayer::StartLayer()
{
	// 1m x 1m x 1m box
	std::vector<Slate::Vertex3D> boxVertices =
	{
		{ { 0.0f, 0.0f, 0.0f } },
		{ { 0.0f, 0.0f, 1.0f } },
		{ { 1.0f, 0.0f, 1.0f } },
		{ { 1.0f, 0.0f, 0.0f } },
		{ { 0.0f, 1.0f, 0.0f } },
		{ { 0.0f, 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 1.0f } },
		{ { 1.0f, 1.0f, 0.0f } },
	};

	std::vector<unsigned int> boxIndices =
	{
		// Face down
		0,2,1,
		0,3,2,

		// Face Back
		2,5,1,
		2,6,5,

		// Face Left
		1,4,0,
		1,5,4,

		// Face Right
		3,6,2,
		3,7,6,

		// Face Top
		4,6,7,
		4,5,6,

		// Face Front
		0,7,3,
		0,4,7
	};

	m_Box.Mesh = m_Renderer.CreateMesh3D();





}

void StartLayer::OnEvent(Slate::Event& event)
{
	// Hnadle cam movenet

}

void StartLayer::OnRender()
{






}
