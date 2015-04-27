#include "UserInterfaceTask.h"
#include "DrawEventArgs.h"

#include "Common/Logger.h"

#include "PeripheralLayer/GraphicContext.h"

#include "ApplicationLayer/ViewCollection.h"

#include <cassert>

ApplicationLayer::UserInterfaceTask::UserInterfaceTask(PeripheralLayer::GraphicContext& context, ApplicationLayer::ViewCollection& views, uint32_t now)
	: TimedTask(now)
	, m_GraphicContext(context)
	, m_Palette(Palette::Default)
	, m_Views(views)
	, m_CurrentScreen(m_Views.GetViews().GetFirst())
{
	m_GraphicContext.FillScreen(m_Palette.Background);
}

void ApplicationLayer::UserInterfaceTask::NextScreen()
{
	//Common::Logger::Get().Log("ApplicationLayer::UserInterfaceTask::NextScreen Called");

	m_GraphicContext.FillScreen(m_Palette.Background);
	m_CurrentScreen = m_Views.GetViews().GetNext();
	if (m_CurrentScreen == nullptr) m_CurrentScreen = m_Views.GetViews().GetFirst();
}

void ApplicationLayer::UserInterfaceTask::PreviousScreen()
{
	//Common::Logger::Get().Log("ApplicationLayer::UserInterfaceTask::PreviousScreen Called");

	m_GraphicContext.FillScreen(m_Palette.Background);
	m_CurrentScreen = m_Views.GetViews().GetPrevious();
	if (m_CurrentScreen == nullptr) m_CurrentScreen = m_Views.GetViews().GetLast();
}

void ApplicationLayer::UserInterfaceTask::Run(uint32_t now)
{
	assert(m_CurrentScreen);

	DrawEventArgs eventArgs(m_GraphicContext, m_Palette);

	m_CurrentScreen->OnDraw(eventArgs);

	m_GraphicContext.Update();

	IncrementRunTime(125);
}
