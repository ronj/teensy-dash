#pragma once

#include "View.h"

#include "IconValueRow.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class TripComputerModel;
	}

	namespace Views
	{
		class TripComputerView : public View
		{
		public:
			TripComputerView(const Models::TripComputerModel& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);
			void Query();

		private:
			void DrawTripData(uint8_t activePage, ApplicationLayer::DrawEventArgs& e);

		private:
			const Models::TripComputerModel& m_Model;

			IconValueRow m_Distance;
			IconValueRow m_AverageFuelConsumption;
			IconValueRow m_AverageSpeed;

			uint8_t m_ActivePage = 0;
		};
	}
}
