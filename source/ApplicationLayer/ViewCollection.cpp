#include "ViewCollection.h"

#include "Images.h"
#include "ModelCollection.h"

ApplicationLayer::ViewCollection::ViewCollection(ModelCollection& models)
	: m_GearView(0, 0, "Gear", models.GetGearModel())
	, m_SpeedView(0, 0, Images::Battery, "KM/H", models.GetSpeedModel())
	, m_AccelerationView(0, 0, models.GetXAccelerationModel(), models.GetYAccelerationModel())
{
	m_Views.Add(m_GearView);
	m_Views.Add(m_SpeedView);
	m_Views.Add(m_AccelerationView);
}

Common::List<ApplicationLayer::Views::View>& ApplicationLayer::ViewCollection::GetViews()
{
	return m_Views;
}
