#pragma once

#include "Common/List.h"

#include "Models/SpeedModel.h"
#include "Models/CalculatedGearModel.h"
#include "Models/RandomValueModel.h"
#include "Models/AccelerationModel.h"

namespace PeripheralLayer
{
	class Peripherals;
}

namespace ApplicationLayer
{
	class ModelCollection
	{
	public:
		ModelCollection(PeripheralLayer::Peripherals& peripherals);

		const Models::Model& GetSpeedModel() const;
		const Models::Model& GetRPMModel() const;

		const Models::Model& GetXAccelerationModel() const;
		const Models::Model& GetYAccelerationModel() const;
		const Models::Model& GetZAccelerationModel() const;

		const Models::Model& GetGearModel() const;

		Common::List<Models::Model>& GetModels();

	private:
		Models::SpeedModel m_RoadspeedModel;
		Models::RandomValueModel m_RPMModel;

		Models::CalculatedGearModel m_GearModel;

		Models::AccelerationModel m_XAcceleration;
		Models::AccelerationModel m_YAcceleration;
		Models::AccelerationModel m_ZAcceleration;

		Common::List<Models::Model> m_ModelList;
	};
}
