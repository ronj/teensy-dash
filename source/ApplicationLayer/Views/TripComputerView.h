#pragma once

#include "View.h"

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

		private:
			const Models::TripComputerModel& m_Model;
		};
	}
}
