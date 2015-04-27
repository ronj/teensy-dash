#include "UserInterfaceTask.h"
#include "DrawEventArgs.h"

#include "Common/Logger.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"

#include "ApplicationLayer/Images.h"
#include "ApplicationLayer/Fonts.h"

#include "ApplicationLayer/ModelCollection.h"

#include "ApplicationLayer/Views/IconValueRow.h"
#include "ApplicationLayer/Views/LargeValueView.h"
#include "ApplicationLayer/Views/GraphView.h"
#include "ApplicationLayer/Views/XYScatterView.h"

ApplicationLayer::UserInterfaceTask::UserInterfaceTask(PeripheralLayer::GraphicContext& context, ApplicationLayer::ModelCollection& models, uint32_t now)
	: TimedTask(now)
	, m_GraphicContext(context)
	, m_Models(models)
	, m_Palette(Palette::Default)
	, m_CurrentScreen(0)
{
	m_GraphicContext.FillScreen(m_Palette.Background);
}

void ApplicationLayer::UserInterfaceTask::NextScreen()
{
	//Common::Logger::Get().Log("ApplicationLayer::UserInterfaceTask::NextScreen Called");

	m_GraphicContext.FillScreen(m_Palette.Background);
	m_CurrentScreen++;
}

void ApplicationLayer::UserInterfaceTask::PreviousScreen()
{
	//Common::Logger::Get().Log("ApplicationLayer::UserInterfaceTask::PreviousScreen Called");

	m_GraphicContext.FillScreen(m_Palette.Background);
	m_CurrentScreen--;
}

void ApplicationLayer::UserInterfaceTask::Run(uint32_t now)
{
	DrawEventArgs eventArgs(m_GraphicContext, m_Palette);

	Views::IconValueRow batteryVoltage(0, 0, Images::Battery, "Volt", m_Models.GetBatteryVoltageModel());
	Views::IconValueRow oilPressure(0, 32 + 5 + 12, Images::Oilcan, "Bar", m_Models.GetOilPressureModel());
	Views::IconValueRow oilTemp(0, (32 + 5 + 12) * 2, Images::Temperature, "degC", m_Models.GetOilTemperatureModel());

	static Views::GraphView oilTempGraph(0, 0, m_GraphicContext.Width(), m_GraphicContext.Height(), m_Models.GetOilPressureModel());
	Views::LargeValueView gear(0, 0, "Gear", m_Models.GetGearModel());

	Views::IconValueRow speed(0, 0, Images::Battery, "KM/H", m_Models.GetSpeedModel());

	static Views::XYScatterView acceleration(0, 0, m_Models.GetXAccelerationModel(), m_Models.GetYAccelerationModel());

	Views::IconValueRow pitch(0, 0, Images::Oilcan, "Pitch (Deg)", m_Models.GetPitchModel());
	Views::IconValueRow roll(0, 32 + 5 + 12, Images::Oilcan, "Roll (Deg)", m_Models.GetRollModel());

	switch (m_CurrentScreen)
	{
		case 0:
			batteryVoltage.OnDraw(eventArgs);
			oilPressure.OnDraw(eventArgs);
			oilTemp.OnDraw(eventArgs);
			break;

		case 1:
			gear.OnDraw(eventArgs);
			break;

		case 2:
			acceleration.OnDraw(eventArgs);
			break;

		case 3:
			pitch.OnDraw(eventArgs);
			roll.OnDraw(eventArgs);
			break;

		case 4:
			speed.OnDraw(eventArgs);
			break;

		case 5:
			oilTempGraph.OnDraw(eventArgs);
			break;

		default:
			break;
	}

	m_GraphicContext.Update();

	IncrementRunTime(125);
}
