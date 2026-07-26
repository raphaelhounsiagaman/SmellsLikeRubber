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
	Slate::Application& m_Application = Slate::Application::Get();
	Slate::Renderer& m_Renderer = m_Application.GetRenderer();

	Slate::Camera3D m_Camera;
	GameObject3D m_Car;
	ArcadeCarController m_CarController;
	ChaseCameraController m_ChaseCameraController;
	DebugDrivingCourse m_DebugDrivingCourse;

	Slate::UICanvas m_HudCanvas;
	Slate::Label* m_FpsLabel = nullptr;
	float m_FpsSampleTimeSeconds = 0.0f;
	unsigned int m_FpsSampleFrameCount = 0;
};
