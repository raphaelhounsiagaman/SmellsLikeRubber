#include "MainMenuLayer.h"

#include "GameLayer.h"

MainMenuLayer::MainMenuLayer()
{
	Slate::TextStyle titleStyle;
	titleStyle.FontSizePixels = 52.0f;
	titleStyle.IsBold = true;
	titleStyle.HorizontalAlignment =
		Slate::HorizontalTextAlignment::Center;
	titleStyle.VerticalAlignment =
		Slate::VerticalTextAlignment::Center;

	Slate::TextStyle subtitleStyle;
	subtitleStyle.FontSizePixels = 19.0f;
	subtitleStyle.TextColor = Slate::Color(210, 205, 230);
	subtitleStyle.HorizontalAlignment =
		Slate::HorizontalTextAlignment::Center;
	subtitleStyle.VerticalAlignment =
		Slate::VerticalTextAlignment::Center;

	m_TitleLabel = &m_Canvas.AddLabel(
		L"SMELLS LIKE RUBBER",
		{},
		titleStyle
	);
	m_SubtitleLabel = &m_Canvas.AddLabel(
		L"An arcade driving prototype",
		{},
		subtitleStyle
	);
	m_StartButton = &m_Canvas.AddButton(
		L"START DRIVING",
		{},
		[this]()
		{
			TransitionTo<GameLayer>();
		}
	);

	UpdateLayout();
}

void MainMenuLayer::OnEvent(Slate::Event& event)
{
	m_Canvas.OnEvent(event);
}

void MainMenuLayer::OnUpdate(float)
{
	UpdateLayout();
}

void MainMenuLayer::OnRender()
{
	m_Canvas.Render(m_Renderer);
}

void MainMenuLayer::UpdateLayout()
{
	const float viewportWidth =
		static_cast<float>(
			m_Application.GetWindow().GetClientWidthPixels()
		);
	const float viewportHeight =
		static_cast<float>(
			m_Application.GetWindow().GetClientHeightPixels()
		);
	const float centreX = viewportWidth * 0.5f;
	const float centreY = viewportHeight * 0.5f;

	m_TitleLabel->SetBounds(
		{ centreX - 360.0f, centreY - 150.0f, 720.0f, 72.0f }
	);
	m_SubtitleLabel->SetBounds(
		{ centreX - 300.0f, centreY - 80.0f, 600.0f, 40.0f }
	);
	m_StartButton->SetBounds(
		{ centreX - 150.0f, centreY + 20.0f, 300.0f, 68.0f }
	);
}
