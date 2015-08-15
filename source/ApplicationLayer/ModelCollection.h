#pragma once

#include "Common/List.h"

#include "Models/AccelerationModel.h"
#include "Models/CalculatedGearModel.h"
#include "Models/ParkDistanceModel.h"
#include "Models/PitchModel.h"
#include "Models/RandomValueModel.h"
#include "Models/RollModel.h"
#include "Models/RPMModel.h"
#include "Models/SpeedModel.h"
#include "Models/TripComputerModel.h"
#include "Models/VoltageModel.h"
#include "Models/WheelTickModel.h"

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

		const Models::Model& GetGearModel() const;

		const Models::TripComputerModel& GetTripComputerModel() const;

		const Models::ParkDistanceModel& GetParkDistanceModel() const;

		const Models::Model& GetBatteryVoltageModel() const;
		const Models::Model& GetOilPressureModel() const;
		const Models::Model& GetOilTemperatureModel() const;

		const Models::Model& GetXAccelerationModel() const;
		const Models::Model& GetYAccelerationModel() const;
		const Models::Model& GetZAccelerationModel() const;

		const Models::Model& GetPitchModel() const;
		const Models::Model& GetRollModel() const;

		Common::List<Models::Model>& GetModels();

	private:
		Models::WheelTickModel m_WheelTickModel;
		Models::SpeedModel m_SpeedModel;
		Models::RPMModel m_RPMModel;

		Models::CalculatedGearModel m_GearModel;

		Models::TripComputerModel m_TripComputerModel;

		Models::ParkDistanceModel m_ParkDistanceModel;

		Models::VoltageModel m_BatteryVoltageModel;
		Models::RandomValueModel m_OilPressureModel;
		Models::RandomValueModel m_OilTemperatureModel;

		Models::AccelerationModel m_XAccelerationModel;
		Models::AccelerationModel m_YAccelerationModel;
		Models::AccelerationModel m_ZAccelerationModel;

		Models::PitchModel m_PitchModel;
		Models::RollModel m_RollModel;

		Common::List<Models::Model> m_ModelList;
	};
}
