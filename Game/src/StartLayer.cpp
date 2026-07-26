#include "StartLayer.h"

#include "Meshes/BoxMesh.h"

#include <algorithm>
#include <cmath>

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
	constexpr float mouseSensitivity = 0.0025f;
	constexpr float maximumPitch = 1.55334f; // 89 degrees.

	if (Slate::Input::IsMouseButtonDown(Slate::MouseButton::Right))
	{
		const Slate::Vector2i mouseDelta = Slate::Input::GetMouseDelta();
		m_CameraYaw += static_cast<float>(mouseDelta.X) * mouseSensitivity;
		m_CameraPitch -= static_cast<float>(mouseDelta.Y) * mouseSensitivity;
		m_CameraPitch = std::clamp(
			m_CameraPitch,
			-maximumPitch,
			maximumPitch
		);
	}

	const float cosPitch = std::cos(m_CameraPitch);
	const Slate::Vector3f forward
	{
		std::sin(m_CameraYaw) * cosPitch,
		std::sin(m_CameraPitch),
		std::cos(m_CameraYaw) * cosPitch
	};
	const Slate::Vector3f right
	{
		std::cos(m_CameraYaw),
		0.0f,
		-std::sin(m_CameraYaw)
	};

	Slate::Vector3f movement{};
	if (Slate::Input::IsKeyDown(Slate::KeyCode::W) ||
		Slate::Input::IsKeyDown(Slate::KeyCode::Up))
	{
		movement = movement + forward;
	}
	if (Slate::Input::IsKeyDown(Slate::KeyCode::S) ||
		Slate::Input::IsKeyDown(Slate::KeyCode::Down))
	{
		movement = movement - forward;
	}
	if (Slate::Input::IsKeyDown(Slate::KeyCode::D) ||
		Slate::Input::IsKeyDown(Slate::KeyCode::Right))
	{
		movement = movement + right;
	}
	if (Slate::Input::IsKeyDown(Slate::KeyCode::A) ||
		Slate::Input::IsKeyDown(Slate::KeyCode::Left))
	{
		movement = movement - right;
	}
	if (Slate::Input::IsKeyDown(Slate::KeyCode::E))
	{
		movement.Y += 1.0f;
	}
	if (Slate::Input::IsKeyDown(Slate::KeyCode::Q))
	{
		movement.Y -= 1.0f;
	}

	const float movementLengthSquared =
		movement.X * movement.X +
		movement.Y * movement.Y +
		movement.Z * movement.Z;
	if (movementLengthSquared > 0.0f)
	{
		const float speedMultiplier =
			Slate::Input::IsKeyDown(Slate::KeyCode::Shift) ? 2.5f : 1.0f;
		const float movementScale =
			m_CameraMoveSpeed * speedMultiplier * ts /
			std::sqrt(movementLengthSquared);

		m_Camera.Transform.Position =
			m_Camera.Transform.Position + movement * movementScale;
	}

	const float scroll = Slate::Input::GetScrollDelta().Y;
	m_CameraMoveSpeed = std::clamp(
		m_CameraMoveSpeed + scroll,
		1.0f,
		25.0f
	);

	const Slate::Quaternion pitchRotation =
		Slate::Quaternion::FromAxisAngle(
			{ 1.0f, 0.0f, 0.0f },
			-m_CameraPitch
		);
	const Slate::Quaternion yawRotation =
		Slate::Quaternion::FromAxisAngle(
			{ 0.0f, 1.0f, 0.0f },
			m_CameraYaw
		);
	m_Camera.Transform.Rotation =
		(pitchRotation * yawRotation).Normalized();

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
