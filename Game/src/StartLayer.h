#pragma once

#include "GameObject3D.h"

#include "Slate/Slate.h"

class StartLayer : public Slate::ApplicationLayer
{
public:
	StartLayer();
	virtual ~StartLayer() = default;
	virtual void OnEvent(Slate::Event& event) override;
	virtual void OnUpdate(float ts) override;
	virtual void OnRender() override;

private:

	Slate::Application& m_Application = Slate::Application::Get();
	Slate::Renderer& m_Renderer = m_Application.GetRenderer();

	Slate::Camera3D m_Camera;

	GameObject3D m_Box;

};