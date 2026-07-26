
#include "StartLayer.h"

#include "Slate/EntryPoint.h"
#include "Slate/Slate.h"

class SmellsLikeRubberApplication final : public Slate::Application
{
public:
	SmellsLikeRubberApplication(const Slate::WindowInformation& windowInfo)
		: Slate::Application(windowInfo)
	{
		m_Renderer.SetClearColor(m_ClearColor);

		PushLayer<StartLayer>();
		PushLayer<StartLayer>();
	}

	~SmellsLikeRubberApplication()
	{

	}
	
private:
	
	Slate::Color m_ClearColor{ 60, 0, 160, 255} ;




};

Slate::Application* Slate::CreateApplication(Slate::WindowInformation windowInfo)
{
	windowInfo.Name = L"Smells Like Rubber";
	windowInfo.Width = 1280;
	windowInfo.Height = 720;

	return new SmellsLikeRubberApplication(windowInfo);
}

