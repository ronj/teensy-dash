#pragma once

#include "View.h"

#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class RepresentableModel;
	}

	namespace Views
	{
		class ParkDistanceView : public View
		{
		public:
			ParkDistanceView(const Models::RepresentableModel& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);
			void Query();

		private:
			const Models::RepresentableModel& m_Model;
		};
	}
}
