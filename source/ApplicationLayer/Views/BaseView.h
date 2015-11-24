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
		class BaseView : public View
		{
		public:
			BaseView(int16_t x, int16_t y, const Models::RepresentableModel& model)
				: m_X(x)
				, m_Y(y)
				, m_Model(model)
			{
			}

			void Query() {}

		protected:
			int16_t GetX() const { return m_X; }
			int16_t GetY() const { return m_Y; }
			const Models::RepresentableModel& GetModel() const { return m_Model; }

		private:
			int16_t m_X;
			int16_t m_Y;
			const Models::RepresentableModel& m_Model;
		};
	}
}
