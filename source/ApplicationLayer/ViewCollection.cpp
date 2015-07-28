#include "ViewCollection.h"

#include "PeripheralLayer/Bitmaps.h"
#include "ModelCollection.h"

ApplicationLayer::ViewCollection::ViewCollection(ModelCollection& models)
	: m_BatteryVoltage(0, 0, PeripheralLayer::Bitmaps::Battery, "Volt", models.GetBatteryVoltageModel())
	, m_SpeedRPMView(0, 0, "KM/H", models.GetSpeedModel(), "RPM", models.GetRPMModel())
	, m_GearView(0, 0, "Gear", models.GetGearModel())
	, m_TripComputerView(models.GetTripComputerModel())
	, m_AccelerationView(0, 0, models.GetXAccelerationModel(), models.GetYAccelerationModel())
{
	m_Views.Add(m_SpeedRPMView);
	m_Views.Add(m_BatteryVoltage);
	m_Views.Add(m_GearView);
	m_Views.Add(m_TripComputerView);
	m_Views.Add(m_AccelerationView);
}

Common::List<ApplicationLayer::Views::View>& ApplicationLayer::ViewCollection::GetViews()
{
	return m_Views;
}
