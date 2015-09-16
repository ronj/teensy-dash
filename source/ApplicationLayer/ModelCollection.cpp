#include "ModelCollection.h"

#include "PeripheralLayer/Peripherals.h"

ApplicationLayer::ModelCollection::ModelCollection(PeripheralLayer::Peripherals& peripherals)
	: m_WheelTickModel(peripherals.GetVSSPulseCounter())
	, m_InjectorModel(peripherals.GetInjectorPulseDurationCounter())
	, m_SpeedModel(peripherals.GetConfiguration(), m_WheelTickModel)
	, m_RPMModel(peripherals.GetRPMFrequencyCounter())
	, m_GearModel(peripherals.GetConfiguration(), m_SpeedModel, m_RPMModel)
	, m_TripComputerModel(peripherals.GetConfiguration(), m_WheelTickModel)
	, m_ParkDistanceModel(peripherals.GetParkDistanceDecoder())
	, m_BatteryVoltageModel(peripherals.GetBatteryVoltageMeter())
	, m_OilPressureModel(4, 6)
	, m_OilTemperatureModel(25, 125)
	, m_XAccelerationModel(peripherals.GetXAcceleration())
	, m_YAccelerationModel(peripherals.GetYAcceleration())
	, m_ZAccelerationModel(peripherals.GetZAcceleration())
	, m_PitchModel(peripherals.GetXAcceleration(), peripherals.GetYAcceleration(), peripherals.GetZAcceleration())
	, m_RollModel(peripherals.GetYAcceleration(), peripherals.GetZAcceleration())
{
	// Please note: since there are dependencies between Models
	// the sequence of the Models in the list matter. Do not
	// change carelessly.
	m_ModelList.Add(m_WheelTickModel);
	m_ModelList.Add(m_InjectorModel);
	m_ModelList.Add(m_SpeedModel);
	m_ModelList.Add(m_RPMModel);
	m_ModelList.Add(m_GearModel);
	m_ModelList.Add(m_TripComputerModel);
	m_ModelList.Add(m_ParkDistanceModel);
	m_ModelList.Add(m_BatteryVoltageModel);
	m_ModelList.Add(m_OilPressureModel);
	m_ModelList.Add(m_OilTemperatureModel);
	m_ModelList.Add(m_XAccelerationModel);
	m_ModelList.Add(m_YAccelerationModel);
	m_ModelList.Add(m_ZAccelerationModel);
	m_ModelList.Add(m_PitchModel);
	m_ModelList.Add(m_RollModel);
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetSpeedModel() const
{
	return m_SpeedModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetRPMModel() const
{
	return m_RPMModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetGearModel() const
{
	return m_GearModel;
}

const ApplicationLayer::Models::TripComputerModel& ApplicationLayer::ModelCollection::GetTripComputerModel() const
{
	return m_TripComputerModel;
}

const ApplicationLayer::Models::ParkDistanceModel& ApplicationLayer::ModelCollection::GetParkDistanceModel() const
{
	return m_ParkDistanceModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetBatteryVoltageModel() const
{
	return m_BatteryVoltageModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetOilPressureModel() const
{
	return m_OilPressureModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetOilTemperatureModel() const
{
	return m_OilTemperatureModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetXAccelerationModel() const
{
	return m_XAccelerationModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetYAccelerationModel() const
{
	return m_YAccelerationModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetZAccelerationModel() const
{
	return m_ZAccelerationModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetPitchModel() const
{
	return m_PitchModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetRollModel() const
{
	return m_RollModel;
}

Common::List<ApplicationLayer::Models::Model>& ApplicationLayer::ModelCollection::GetModels()
{
	return m_ModelList;
}
