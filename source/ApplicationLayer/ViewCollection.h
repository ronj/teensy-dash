#pragma once

#include "Common/List.h"

#include "ApplicationLayer/Views/GraphView.h"
#include "ApplicationLayer/Views/IconValueRow.h"
#include "ApplicationLayer/Views/LargeValueView.h"
#include "ApplicationLayer/Views/TripComputerView.h"
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
		Views::IconValueRow m_BatteryVoltage;
		Views::TwoRowView m_SpeedRPMView;
		Views::LargeValueView m_GearView;
		Views::TripComputerView m_TripComputerView;
		Views::XYScatterView m_AccelerationView;

		Common::List<Views::View> m_Views;
	};
}
