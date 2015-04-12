#include "UserInterfaceTask.h"
#include "DrawEventArgs.h"

#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"

#include "ApplicationLayer/Images.h"
#include "ApplicationLayer/Fonts.h"

#include "ApplicationLayer/ModelCollection.h"
#include "ApplicationLayer/Models/RandomValueModel.h"
#include "ApplicationLayer/Models/AccelerationModel.h"

#include "ApplicationLayer/Views/IconValueRow.h"
#include "ApplicationLayer/Views/LargeValueView.h"
#include "ApplicationLayer/Views/GraphView.h"
#include "ApplicationLayer/Views/XYScatterView.h"

ApplicationLayer::UserInterfaceTask::UserInterfaceTask(PeripheralLayer::GraphicContext& context, ApplicationLayer::ModelCollection& models, uint32_t now)
	: TimedTask(now)
	, m_GraphicContext(context)
	, m_Models(models)
	, m_Palette(Palette::Default)
{
	m_GraphicContext.FillScreen(m_Palette.Background);
}

void ApplicationLayer::UserInterfaceTask::Run(uint32_t now)
{
	DrawEventArgs eventArgs(m_GraphicContext, m_Palette);

	Models::RandomValueModel batteryVoltageModel(110, 148);
	Models::RandomValueModel oilPressureModel(4, 6);
	Models::RandomValueModel oilTemperatureModel(25, 125);

	Views::IconValueRow batteryVoltage(0, 0, Images::Battery, "Volt", batteryVoltageModel);
	Views::IconValueRow oilPressure(0, 32 + 5 + 12, Images::Oilcan, "Bar", oilPressureModel);
	Views::IconValueRow oilTemp(0, (32 + 5 + 12) * 2, Images::Temperature, "degC", oilTemperatureModel);

	Views::GraphView oilTempGraph(0, 0, oilTemperatureModel);
	Views::LargeValueView gear(0, 0, "Gear", m_Models.GetGearModel());

	static Views::XYScatterView acceleration(0, 0, m_Models.GetXAccelerationModel(), m_Models.GetYAccelerationModel());

	batteryVoltageModel.Update();
	oilPressureModel.Update();
	oilTemperatureModel.Update();

	//batteryVoltage.OnDraw(eventArgs);
	//oilPressure.OnDraw(eventArgs);
	//oilTemp.OnDraw(eventArgs);

	//gear.OnDraw(eventArgs);

	//oilTempGraph.OnDraw(eventArgs);

	acceleration.OnDraw(eventArgs);

	m_GraphicContext.Update();

	IncrementRunTime(125);
}
