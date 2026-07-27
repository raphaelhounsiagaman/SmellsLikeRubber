#pragma once

#include "Slate/Slate.h"

class MainMenuLayer : public Slate::ApplicationLayer
{
public:
	MainMenuLayer();

	void OnEvent(Slate::Event& event) override;
	void OnRender() override;

private:
	void UpdateLayout();

	Slate::Application& m_Application = Slate::Application::Get();
	Slate::Renderer& m_Renderer = m_Application.GetRenderer();

	Slate::UICanvas m_Canvas;
	Slate::Label* m_TitleLabel = nullptr;
	Slate::Label* m_SubtitleLabel = nullptr;
	Slate::Button* m_StartButton = nullptr;
};
