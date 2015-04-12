#pragma once

#include "View.h"

#include <array>
#include <cinttypes>

namespace ApplicationLayer
{
	namespace Models
	{
		class Model;
	}

    namespace Views
    {
        class XYScatterView : public View
        {
            struct Point { int16_t x; int16_t y; };
        public:
			XYScatterView(int16_t, int16_t, const Models::Model& xModel, const Models::Model& yModel);

            void OnDraw(ApplicationLayer::DrawEventArgs& e);

        private:
            const Models::Model& m_XModel;
            const Models::Model& m_YModel;

            std::array<Point, 3> m_Trail;
        };
    }
}
