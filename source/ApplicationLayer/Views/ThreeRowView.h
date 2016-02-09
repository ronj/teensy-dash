#pragma once

#include "View.h"

#include "IconValueRow.h"

#include <array>
#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class RepresentableModel;
	}

	namespace Views
	{
		class ThreeRowView : public View
		{
		public:
			ThreeRowView(const Models::RepresentableModel& model);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);
			void Query();

		private:
			const Models::RepresentableModel& m_Model;

			IconValueRow m_RowOne;
			IconValueRow m_RowTwo;
			IconValueRow m_RowThree;
		};
	}
}
