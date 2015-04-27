#pragma once

#include "Common/List.h"

#include "ApplicationLayer/Views/GraphView.h"
#include "ApplicationLayer/Views/IconValueRow.h"
#include "ApplicationLayer/Views/LargeValueView.h"
#include "ApplicationLayer/Views/TwoRowView.h"
#include "ApplicationLayer/Views/XYScatterView.h"

namespace ApplicationLayer
{
	class ModelCollection;

	class ViewCollection
	{
	public:
		ViewCollection(ModelCollection& models);

		Common::List<Views::View>& GetViews();

	private:
		//Views::IconValueRow batteryVoltage(0, 0, Images::Battery, "Volt", m_Models.GetBatteryVoltageModel());
		//Views::IconValueRow oilPressure(0, 32 + 5 + 12, Images::Oilcan, "Bar", m_Models.GetOilPressureModel());
		//Views::IconValueRow oilTemp(0, (32 + 5 + 12) * 2, Images::Temperature, "degC", m_Models.GetOilTemperatureModel());

		//static Views::GraphView oilTempGraph(0, 0, m_GraphicContext.Width(), m_GraphicContext.Height(), m_Models.GetOilPressureModel());
		Views::LargeValueView m_GearView;

		Views::IconValueRow m_SpeedView;

		Views::XYScatterView m_AccelerationView;

		Views::TwoRowView m_SpeedRPMView;

		//Views::IconValueRow pitch(0, 0, Images::Oilcan, "Pitch (Deg)", m_Models.GetPitchModel());
		//Views::IconValueRow roll(0, 32 + 5 + 12, Images::Oilcan, "Roll (Deg)", m_Models.GetRollModel());

		Common::List<Views::View> m_Views;
	};
}
