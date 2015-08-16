#pragma once

#include "Common/TaskScheduler.h"

#include "ModelCollection.h"
#include "ModelUpdateTask.h"
#include "UserEventsTask.h"
#include "UserInterfaceTask.h"
#include "ViewCollection.h"

namespace PeripheralLayer
{
	class Peripherals;
}

#include "PeripheralLayer/Color.h"
#include "PeripheralLayer/GraphicContext.h"

namespace ApplicationLayer
{
	class Shiftlight
	{
	public:
		Shiftlight(PeripheralLayer::GraphicContext& leds, const ApplicationLayer::Models::Model& rpmModel)
			: m_RpmModel(rpmModel)
			, m_Leds(leds)
		{
		}

		void Update(uint32_t now)
		{
			if (m_RpmModel.GetRawValue() < 6000)
			{
				for (int i = 0; i < m_Leds.Width(); i++)
				{
					m_Leds.DrawPixel(i, 0, 0);
				}
			}
			else if (m_RpmModel.GetRawValue() > 7000)
			{
				if (now - m_PreviousBlink > 250)
				{
					for (int i = 0; i < m_Leds.Width(); i++)
					{
						m_Leds.DrawPixel(i, 0, m_BlinkState ? PeripheralLayer::Color::RGB(20, 0, 0).ToRGB() : 0);
					}

					m_BlinkState = !m_BlinkState;
					m_PreviousBlink = now;
				}
			}
			else
			{
				if (m_RpmModel.GetRawValue() > 6000)
				{
					m_Leds.DrawPixel(0, 0, PeripheralLayer::Color::RGB(0, 20, 0).ToRGB());
				}

				if (m_RpmModel.GetRawValue() > 6200)
				{
					m_Leds.DrawPixel(1, 0, PeripheralLayer::Color::RGB(0, 20, 0).ToRGB());
				}

				if (m_RpmModel.GetRawValue() > 6400)
				{
					m_Leds.DrawPixel(2, 0, PeripheralLayer::Color::RGB(0, 20, 0).ToRGB());
				}

				if (m_RpmModel.GetRawValue() > 6500)
				{
					m_Leds.DrawPixel(3, 0, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
				}

				if (m_RpmModel.GetRawValue() > 6600)
				{
					m_Leds.DrawPixel(4, 0, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
				}

				if (m_RpmModel.GetRawValue() > 6700)
				{
					m_Leds.DrawPixel(5, 0, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
				}

				if (m_RpmModel.GetRawValue() > 6800)
				{
					m_Leds.DrawPixel(6, 0, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
				}

				if (m_RpmModel.GetRawValue() > 6900)
				{
					m_Leds.DrawPixel(7, 0, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
				}
			}

			m_Leds.Update();
		}

	private:
		const ApplicationLayer::Models::Model& m_RpmModel;
		PeripheralLayer::GraphicContext& m_Leds;
		bool m_BlinkState = false;
		uint32_t m_PreviousBlink;
	};
}

namespace ApplicationLayer
{
	class DashApplication
	{
	public:
		DashApplication(PeripheralLayer::Peripherals& peripherals);

		bool IsRunning();
		void Eventloop();

	private:
		void HandlePowerMode(uint32_t now);

	private:
		static const uint32_t SHUTDOWN_THRESHOLD_AFTER_RPM_LOSS = 3000;

		bool m_Running = true;
		bool m_IsPoweredDown = true;
		uint32_t m_RPMLossTimestamp = 0;

		PeripheralLayer::Peripherals& m_Peripherals;

		ModelCollection m_Models;
		ViewCollection m_Views;

		ModelUpdateTask m_ModelUpdateTask;
		UserEventsTask m_UserEventsTask;
		UserInterfaceTask m_UITask;

		Common::TaskScheduler m_Scheduler;

		Shiftlight m_Shiftlight;
	};
}
