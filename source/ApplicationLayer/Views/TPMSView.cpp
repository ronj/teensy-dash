#include "TPMSView.h"

#include "Common/Logger.h"

#include "PeripheralLayer/Bitmaps.h"
#include "PeripheralLayer/Color.h"
#include "PeripheralLayer/GraphicContext.h"
#include "PeripheralLayer/TextHelper.h"
#include "PeripheralLayer/Fonts.h"

#include "ApplicationLayer/DrawEventArgs.h"
#include "ApplicationLayer/Palette.h"

#include "ApplicationLayer/Models/ConversionHelper.h"
#include "ApplicationLayer/Models/TirePressureModel.h"

#include <algorithm>
#include <array>
#include <tuple>

ApplicationLayer::Views::TPMSView::TPMSView(const Models::TirePressureModel& model)
    : m_PressureModel(model)
{
}

void ApplicationLayer::Views::TPMSView::OnDraw(ApplicationLayer::DrawEventArgs& e)
{
	const uint16_t halfWidth = e.graphicContext.Width() / 2;
	const uint16_t halfHeight = e.graphicContext.Height() / 2;

	e.graphicContext.DrawBitmap(halfWidth - PeripheralLayer::Bitmaps::BigCar.width / 2, halfHeight - PeripheralLayer::Bitmaps::BigCar.height / 2, PeripheralLayer::Bitmaps::BigCar, e.colorScheme.Foreground);

	uint16_t frontLeftPressure = 0;
	uint16_t frontRightPressure = 0;
	uint16_t rearLeftPressure = 0;
	uint16_t rearRightPressure = 0;

	Models::TirePressureModel::UnpackValues(m_PressureModel.GetRawValue(), frontLeftPressure, frontRightPressure, rearLeftPressure, rearRightPressure);

	DrawTirePressure(e, TireLocation::FrontLeft, frontLeftPressure);
	DrawTirePressure(e, TireLocation::FrontRight, frontRightPressure);
	DrawTirePressure(e, TireLocation::RearLeft, rearLeftPressure);
	DrawTirePressure(e, TireLocation::RearRight, rearRightPressure);

    DrawTireTemperature(e, TireLocation::FrontLeft, 250);
    DrawTireTemperature(e, TireLocation::FrontRight, 220);
    DrawTireTemperature(e, TireLocation::RearLeft, 200);
    DrawTireTemperature(e, TireLocation::RearRight, 206);

	DrawTireHealth(e, TireLocation::FrontLeft, frontLeftPressure, 0);
	DrawTireHealth(e, TireLocation::FrontRight, frontRightPressure, 0);
	DrawTireHealth(e, TireLocation::RearLeft, rearLeftPressure, 0);
	DrawTireHealth(e, TireLocation::RearRight, rearRightPressure, 0);
}

void ApplicationLayer::Views::TPMSView::Query()
{
	Common::Logger::Get().LogExpectation(m_PressureModel.GetRawValue());
}

template<typename E>
auto enum_cast(E e) -> typename std::underlying_type<E>::type
{
	return static_cast<typename std::underlying_type<E>::type>(e);
}

void ApplicationLayer::Views::TPMSView::DrawTirePressure(DrawEventArgs& e, TireLocation tire, uint16_t pressure)
{
	const uint8_t scratchpad_size = 5;
	char scratchpad[scratchpad_size] = { 0 };

	PeripheralLayer::TextHelper distanceText(e.graphicContext, PeripheralLayer::Fonts::Peugeot_16pt, e.colorScheme.Text, e.colorScheme.Background);
	snprintf(scratchpad, scratchpad_size, "%" PRIu32 ".%" PRIu32, pressure / 100, ((pressure % 100) / 10));

	switch (tire)
	{
	case TireLocation::FrontLeft:
		distanceText.SetCursor(5, 5);
		break;
	case TireLocation::FrontRight:
		distanceText.SetCursor(e.graphicContext.Width() - (distanceText.TextWidth(scratchpad) + 5), 5);
		break;
	case TireLocation::RearLeft:
		distanceText.SetCursor(5, e.graphicContext.Height() - (distanceText.TextHeight(scratchpad) + 5));
		break;
	case TireLocation::RearRight:
		distanceText.SetCursor(e.graphicContext.Width() - (distanceText.TextWidth(scratchpad) + 5), e.graphicContext.Height() - (distanceText.TextHeight(scratchpad) + 5));
		break;
	}

	distanceText.Write(scratchpad);
}

void ApplicationLayer::Views::TPMSView::DrawTireTemperature(DrawEventArgs & e, TireLocation tire, uint16_t temperature)
{
    const uint8_t scratchpad_size = 5;
    char scratchpad[scratchpad_size] = { 0 };

    PeripheralLayer::TextHelper temperatureText(e.graphicContext, PeripheralLayer::Fonts::LCDFont, e.colorScheme.Text, e.colorScheme.Background, 2);
    snprintf(scratchpad, scratchpad_size, "%" PRIu32 "C", temperature / 10);

    switch (tire)
    {
    case TireLocation::FrontLeft:
        temperatureText.SetCursor(5, 25);
        break;
    case TireLocation::FrontRight:
        temperatureText.SetCursor(e.graphicContext.Width() - (temperatureText.TextWidth(scratchpad) + 5), 25);
        break;
    case TireLocation::RearLeft:
        temperatureText.SetCursor(5, e.graphicContext.Height() - (temperatureText.TextHeight(scratchpad) + 25));
        break;
    case TireLocation::RearRight:
        temperatureText.SetCursor(e.graphicContext.Width() - (temperatureText.TextWidth(scratchpad) + 5), e.graphicContext.Height() - (temperatureText.TextHeight(scratchpad) + 25));
        break;
    }

    temperatureText.Write(scratchpad);
}

void ApplicationLayer::Views::TPMSView::DrawTireHealth(ApplicationLayer::DrawEventArgs& e, TireLocation tire, uint16_t pressure, uint16_t temperature)
{
	static const std::array<std::tuple<int16_t, int16_t>, 4> tireLocation = {
		std::make_tuple(38, 50),
		std::make_tuple(84, 50),
		std::make_tuple(38, 100),
		std::make_tuple(84, 100)
	};

	int16_t x;
	int16_t y;
	std::tie(x, y) = tireLocation[enum_cast(tire)];

	//e.graphicContext.FillRect(x, y, 5, 15, PeripheralLayer::Color::RGB(0, 200, 0).ToRGBA(255));
	e.graphicContext.FillRect(x, y, 5, 15, PeripheralLayer::Color::RGB(255, 102, 0).ToRGBA(255));
	//e.graphicContext.FillRect(x, y, 5, 15, PeripheralLayer::Color::RGB(200, 0, 0).ToRGBA(255));
	e.graphicContext.DrawRect(x, y, 6, 16, PeripheralLayer::Color::RGB(0, 0, 0).ToRGBA(255));
}
