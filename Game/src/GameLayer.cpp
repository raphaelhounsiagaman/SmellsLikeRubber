#include "GameLayer.h"

#include "Meshes/BoxMesh.h"

#include <format>

namespace
{
	constexpr float FpsSampleDurationSeconds = 0.25f;

	bool IsEitherKeyDown(
		Slate::KeyCode primary,
		Slate::KeyCode alternate)
	{
		return Slate::Input::IsKeyDown(primary) ||
			Slate::Input::IsKeyDown(alternate);
	}
}

GameLayer::GameLayer()
	: m_BoxMesh(CreateBoxMesh(m_Renderer)),
	  m_DebugDrivingCourse(m_Renderer, m_BoxMesh)
{
	// CreateBoxMesh is a one-metre cube. Scale therefore represents the car's
	// real dimensions: 1.8 m wide, 1.4 m tall, and 4.2 m long.
	m_Car.Mesh = m_BoxMesh;
	m_Car.Material =
		m_Renderer.CreateMaterial(Slate::Color(230, 90, 25));
	m_Car.Transform.Position = { 0.0f, 0.7f, 0.0f };
	m_Car.Transform.Scale = { 1.8f, 1.4f, 4.2f };

	m_Camera.NearPlaneMetres = 0.1f;
	m_Camera.FarPlaneMetres = 500.0f;

	Slate::TextStyle frameRateStyle;
	frameRateStyle.FontSizePixels = 18.0f;
	frameRateStyle.IsBold = true;
	frameRateStyle.HorizontalAlignment =
		Slate::HorizontalTextAlignment::Right;
	frameRateStyle.VerticalAlignment =
		Slate::VerticalTextAlignment::Center;

	m_FrameRateLabel = &m_HudCanvas.AddLabel(
		L"FPS: --",
		{},
		frameRateStyle
	);
	UpdateHudLayout();
}

void GameLayer::OnEvent(Slate::Event& event)
{
	m_HudCanvas.OnEvent(event);

	Slate::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Slate::WindowResizeEvent>(
		[this](Slate::WindowResizeEvent&)
		{
			UpdateHudLayout();
			return false;
		}
	);
}

void GameLayer::OnUpdate(float deltaTimeSeconds)
{
	m_FpsSampleElapsedSeconds += deltaTimeSeconds;
	++m_FramesInFpsSample;
	if (m_FpsSampleElapsedSeconds >= FpsSampleDurationSeconds)
	{
		const float framesPerSecond =
			static_cast<float>(m_FramesInFpsSample) /
			m_FpsSampleElapsedSeconds;
		m_FrameRateLabel->SetText(
			std::format(L"FPS: {:.0f}", framesPerSecond)
		);
		m_FpsSampleElapsedSeconds = 0.0f;
		m_FramesInFpsSample = 0;
	}

	ArcadeCarInput carInput;
	const float forwardInput =
		IsEitherKeyDown(Slate::KeyCode::W, Slate::KeyCode::Up)
			? 1.0f
			: 0.0f;
	const float reverseInput =
		IsEitherKeyDown(Slate::KeyCode::S, Slate::KeyCode::Down)
			? 1.0f
			: 0.0f;
	const float rightInput =
		IsEitherKeyDown(Slate::KeyCode::D, Slate::KeyCode::Right)
			? 1.0f
			: 0.0f;
	const float leftInput =
		IsEitherKeyDown(Slate::KeyCode::A, Slate::KeyCode::Left)
			? 1.0f
			: 0.0f;

	carInput.Throttle = forwardInput - reverseInput;
	carInput.Steering = rightInput - leftInput;

	m_CarController.Update(
		m_Car.Transform,
		carInput,
		deltaTimeSeconds
	);

	ChaseCameraInput cameraInput;
	if (Slate::Input::IsMouseButtonDown(Slate::MouseButton::Right))
	{
		cameraInput.OrbitDeltaPixels = Slate::Input::GetMouseDelta();
	}
	cameraInput.ZoomWheelSteps = Slate::Input::GetScrollDelta().Y;

	m_ChaseCameraController.Update(
		m_Camera,
		m_Car.Transform.Position,
		m_CarController.GetHeadingRadians(),
		cameraInput,
		deltaTimeSeconds
	);
}

void GameLayer::OnRender()
{
	m_Renderer.SetCamera3D(m_Camera);
	m_DebugDrivingCourse.Render(m_Renderer);
	m_Renderer.DrawMesh3D(
		m_Car.Mesh,
		m_Car.Material,
		m_Car.Transform
	);
	m_Renderer.DrawCanvas(m_HudCanvas);
}

void GameLayer::UpdateHudLayout()
{
	const float viewportWidthPixels =
		static_cast<float>(
			m_Application.GetWindow().GetWindowSize().X
		);
	m_FrameRateLabel->SetBounds(
		{ viewportWidthPixels - 176.0f, 12.0f, 160.0f, 32.0f }
	);
}
