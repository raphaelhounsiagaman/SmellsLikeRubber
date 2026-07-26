#pragma once

#include "Gameplay/ArcadeCarController.h"
#include "Gameplay/ChaseCameraController.h"
#include "GameObject3D.h"
#include "World/DebugDrivingCourse.h"

#include "Slate/Slate.h"

class StartLayer : public Slate::ApplicationLayer
{
public:
	StartLayer();
	virtual ~StartLayer() = default;
	virtual void OnEvent(Slate::Event& event) override;
	virtual void OnUpdate(float deltaTimeSeconds) override;
	virtual void OnRender() override;

private:

	Slate::Application& m_Application = Slate::Application::Get();
	Slate::Renderer& m_Renderer = m_Application.GetRenderer();

	Slate::Camera3D m_Camera;

	GameObject3D m_Car;
	ArcadeCarController m_CarController;
	ChaseCameraController m_ChaseCameraController;
	DebugDrivingCourse m_DebugDrivingCourse;
};
