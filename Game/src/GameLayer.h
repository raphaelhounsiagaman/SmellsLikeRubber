#pragma once

#include "Gameplay/ArcadeCarController.h"
#include "Gameplay/ChaseCameraController.h"
#include "GameObject3D.h"
#include "World/DebugDrivingCourse.h"

#include "Slate/Slate.h"

class GameLayer : public Slate::ApplicationLayer
{
public:
	GameLayer();

	void OnEvent(Slate::Event& event) override;
	void OnUpdate(float deltaTimeSeconds) override;
	void OnRender() override;

private:
	void UpdateHudLayout();

	Slate::Application& m_Application = Slate::Application::Get();
	Slate::Renderer& m_Renderer = m_Application.GetRenderer();

	Slate::Camera3D m_Camera;
	Slate::Mesh3DHandle m_BoxMesh;
	GameObject3D m_Car;
	ArcadeCarController m_CarController;
	ChaseCameraController m_ChaseCameraController;
	DebugDrivingCourse m_DebugDrivingCourse;

	Slate::UICanvas m_HudCanvas;
	Slate::Label* m_FrameRateLabel = nullptr;
	float m_FpsSampleElapsedSeconds = 0.0f;
	unsigned int m_FramesInFpsSample = 0;
};
