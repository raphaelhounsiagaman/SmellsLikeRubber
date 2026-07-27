#include "GameLayer.h"

#include "Meshes/BoxMesh.h"

#include <format>

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

	Slate::TextStyle updateRateStyle;
	updateRateStyle.FontSizePixels = 18.0f;
	updateRateStyle.IsBold = true;
	updateRateStyle.HorizontalAlignment =
		Slate::HorizontalTextAlignment::Right;
	updateRateStyle.VerticalAlignment =
		Slate::VerticalTextAlignment::Center;

	m_PerformanceLabel = &m_HudCanvas.AddLabel(
		L"UPS: -- | FPS: --",
		{},
		updateRateStyle
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
	const Slate::PerformanceStatistics& performance =
		m_Application.GetPerformanceStatistics();
	if (performance.SampleNumber != m_LastPerformanceSample)
	{
		m_PerformanceLabel->SetText(
			std::format(
				L"UPS: {:.0f} | FPS: {:.0f}",
				performance.UpdatesPerSecond,
				performance.FramesPerSecond
			)
		);
		m_LastPerformanceSample = performance.SampleNumber;
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

void GameLayer::UpdateHudLayout()
{
	const float viewportWidthPixels =
		static_cast<float>(
			m_Application.GetWindow().GetWindowSize().X
		);
	m_PerformanceLabel->SetBounds(
		{ viewportWidthPixels - 296.0f, 12.0f, 280.0f, 32.0f }
	);
}
