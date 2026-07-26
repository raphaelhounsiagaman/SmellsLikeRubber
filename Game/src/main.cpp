
#include "MainMenuLayer.h"

#include "Slate/EntryPoint.h"
#include "Slate/Slate.h"

#include <memory>

class SmellsLikeRubberApplication final : public Slate::Application
{
public:
	SmellsLikeRubberApplication(const Slate::WindowInformation& windowInfo)
		: Slate::Application(windowInfo)
	{
		m_Renderer.SetClearColor(m_ClearColor);

		PushLayer<MainMenuLayer>();
	}

private:
	Slate::Color m_ClearColor{ 60, 0, 160, 255 };
};

std::unique_ptr<Slate::Application> Slate::CreateApplication(
	Slate::WindowInformation windowInfo)
{
	windowInfo.Name = L"Smells Like Rubber";
	windowInfo.WidthPixels = 1280;
	windowInfo.HeightPixels = 720;

	return std::make_unique<SmellsLikeRubberApplication>(windowInfo);
}

