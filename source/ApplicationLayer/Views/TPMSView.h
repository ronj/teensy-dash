#pragma once

#include "View.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class TirePressureModel;
		class TireTemperatureModel;
	}

	namespace Views
	{
		class TPMSView : public View
		{
		enum class TireLocation : uint8_t { FrontLeft = 0, FrontRight = 1, RearLeft = 2, RearRight = 3 };

		public:
			TPMSView(const Models::TirePressureModel& pressureModel);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);
			void Query();

		private:
			void DrawTireHealth(DrawEventArgs& e, TireLocation tire, uint16_t pressure, uint16_t temperature);

		private:
			const Models::TirePressureModel& m_PressureModel;
		};
	}
}
