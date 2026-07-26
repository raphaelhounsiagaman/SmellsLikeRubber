#include "StartLayer.h"

#include "Meshes/BoxMesh.h"

StartLayer::StartLayer()
{
	m_Box.Mesh = CreateBoxMesh(m_Renderer);
	m_Box.Material = m_Renderer.CreateMaterial(Slate::Color(230, 90, 25));

	m_Box.Transform.Rotation =
		Slate::Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

	m_Camera.Transform.Position = { 0.0f, 0.0f, -3.0f };
}

void StartLayer::OnEvent(Slate::Event& event)
{

}

void StartLayer::OnUpdate(float ts)
{

	// Radians per second.
	constexpr float spinSpeed = 0.5f;

	const Slate::Quaternion rotationThisFrame =
		Slate::Quaternion::FromAxisAngle(
			{ 0.0f, 1.0f, 0.0f },
			spinSpeed * ts
		);
	
	m_Box.Transform.Rotation =
		(rotationThisFrame * m_Box.Transform.Rotation).Normalized();

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
