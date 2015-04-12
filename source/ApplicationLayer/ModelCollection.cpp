#include "ModelCollection.h"

#include "PeripheralLayer/Peripherals.h"

ApplicationLayer::ModelCollection::ModelCollection(PeripheralLayer::Peripherals& peripherals)
	: m_RPMModel(0, 7200)
	, m_GearModel(205, 40, 17, 4.05f, m_RoadspeedModel, m_RPMModel)
	, m_XAcceleration(peripherals.GetXAcceleration())
	, m_YAcceleration(peripherals.GetYAcceleration())
	, m_ZAcceleration(peripherals.GetZAcceleration())
{
	m_ModelList.Add(m_RoadspeedModel);
	m_ModelList.Add(m_RPMModel);
	m_ModelList.Add(m_GearModel);
	m_ModelList.Add(m_XAcceleration);
	m_ModelList.Add(m_YAcceleration);
	m_ModelList.Add(m_ZAcceleration);
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetSpeedModel() const
{
	return m_RoadspeedModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetRPMModel() const
{
	return m_RPMModel;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetXAccelerationModel() const
{
	return m_XAcceleration;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetYAccelerationModel() const
{
	return m_YAcceleration;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetZAccelerationModel() const
{
	return m_ZAcceleration;
}

const ApplicationLayer::Models::Model& ApplicationLayer::ModelCollection::GetGearModel() const
{
	return m_GearModel;
}

Common::List<ApplicationLayer::Models::Model>& ApplicationLayer::ModelCollection::GetModels()
{
	return m_ModelList;
}
