#pragma once

#include "View.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class ParkDistanceModel;
	}

	namespace Views
	{
		class ParkDistanceView : public View
		{
		public:
			ParkDistanceView(const Models::ParkDistanceModel& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);
			void Query();

		private:
			const Models::ParkDistanceModel& m_Model;
		};
	}
}
