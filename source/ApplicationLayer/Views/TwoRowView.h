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
		class TwoRowView
			: public View
		{
		public:
			TwoRowView(int16_t x, int16_t y, const char* labelOne, const Models::RepresentableModel& modelOne,
				                             const char* labelTwo, const Models::RepresentableModel& modelTwo);

			void OnDraw(ApplicationLayer::DrawEventArgs& e);
			void Query();

		private:
			void DrawLabelAndModel(int16_t x, int16_t y, ApplicationLayer::DrawEventArgs& e, const char* label, const Models::RepresentableModel& model, uint8_t textSize, uint16_t& previousWidth);

		private:
			int16_t m_X;
			int16_t m_Y;

			const char* m_LabelOne;
			const Models::RepresentableModel& m_ModelOne;
			uint16_t m_PreviousWidthOne;

			const char* m_LabelTwo;
			const Models::RepresentableModel& m_ModelTwo;
			uint16_t m_PreviousWidthTwo;
		};
	}
}
