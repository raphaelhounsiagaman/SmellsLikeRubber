#include "GameLayer.h"

#include "Core/MetricUnits.h"
#include "Meshes/BoxMesh.h"

#include <format>

GameLayer::GameLayer()
	: m_DebugDrivingCourse(m_Renderer)
{
	// CreateBoxMesh is a one-metre cube. Scale therefore represents the car's
	// real dimensions: 1.8 m wide, 1.4 m tall, and 4.2 m long.
	m_Car.Mesh = CreateBoxMesh(m_Renderer);
	m_Car.Material =
		m_Renderer.CreateMaterial(Slate::Color(230, 90, 25));
	m_Car.Transform.Position =
		{ 0.0f, Metric::Metres(0.7f), 0.0f };
	m_Car.Transform.Scale =
		{
			Metric::Metres(1.8f),
			Metric::Metres(1.4f),
			Metric::Metres(4.2f)
		};

	m_Camera.NearPlaneMetres = Metric::Metres(0.1f);
	m_Camera.FarPlaneMetres = Metric::Metres(500.0f);

	Slate::TextStyle fpsStyle;
	fpsStyle.FontSizePixels = 18.0f;
	fpsStyle.IsBold = true;
	fpsStyle.HorizontalAlignment =
		Slate::HorizontalTextAlignment::Right;
	fpsStyle.VerticalAlignment =
		Slate::VerticalTextAlignment::Center;

	m_FpsLabel = &m_HudCanvas.AddLabel(
		L"FPS: --",
		{},
		fpsStyle
	);
}

void GameLayer::OnEvent(Slate::Event&)
{}

void GameLayer::OnUpdate(float deltaTimeSeconds)
{
	const float viewportWidthPixels =
		static_cast<float>(
			m_Application.GetWindow().GetClientWidthPixels()
		);
	m_FpsLabel->SetBounds(
		{ viewportWidthPixels - 176.0f, 12.0f, 160.0f, 32.0f }
	);

	m_FpsSampleTimeSeconds += deltaTimeSeconds;
	++m_FpsSampleFrameCount;
	if (m_FpsSampleTimeSeconds >= 0.25f)
	{
		const float framesPerSecond =
			static_cast<float>(m_FpsSampleFrameCount) /
			m_FpsSampleTimeSeconds;
		m_FpsLabel->SetText(
			std::format(L"FPS: {:.0f}", framesPerSecond)
		);
		m_FpsSampleTimeSeconds = 0.0f;
		m_FpsSampleFrameCount = 0;
	}

	const auto isKeyDown = [](Slate::KeyCode primary, Slate::KeyCode alternate)
	{
		return Slate::Input::IsKeyDown(primary) ||
			Slate::Input::IsKeyDown(alternate);
	};

	ArcadeCarInput carInput;
	carInput.Throttle =
		(isKeyDown(Slate::KeyCode::W, Slate::KeyCode::Up) ? 1.0f : 0.0f) -
		(isKeyDown(Slate::KeyCode::S, Slate::KeyCode::Down) ? 1.0f : 0.0f);
	carInput.Steering =
		(isKeyDown(Slate::KeyCode::D, Slate::KeyCode::Right) ? 1.0f : 0.0f) -
		(isKeyDown(Slate::KeyCode::A, Slate::KeyCode::Left) ? 1.0f : 0.0f);

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
	m_HudCanvas.Render(m_Renderer);
}
