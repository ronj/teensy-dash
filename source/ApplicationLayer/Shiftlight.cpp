#include "Shiftlight.h"

#include "PeripheralLayer/Color.h"
#include "PeripheralLayer/PatternPlayer.h"

#include "ApplicationLayer/Models/Model.h"

ApplicationLayer::Shiftlight::Shiftlight(PeripheralLayer::PatternPlayer& patternPlayer, const ApplicationLayer::Models::Model& rpmModel)
    : m_RpmModel(rpmModel)
    , m_PatternPlayer(patternPlayer)
{
}

void ApplicationLayer::Shiftlight::Update(uint32_t now)
{
    if (m_RpmModel.GetRawValue() < 6000)
    {
        m_PatternPlayer.Clear();
    }
    else if (m_RpmModel.GetRawValue() > 7000)
    {
        if (now - m_PreviousBlink > 125)
        {
            for (int i = 0; i < 8; i++)
            {
                m_PatternPlayer.DrawPixel(i, m_BlinkState ? PeripheralLayer::Color::RGB(50, 0, 0).ToRGB() : 0);
            }

            m_BlinkState = !m_BlinkState;
            m_PreviousBlink = now;
        }
    }
    else
    {
        if (m_RpmModel.GetRawValue() > 6000)
        {
            m_PatternPlayer.DrawPixel(0, PeripheralLayer::Color::RGB(0, 20, 0).ToRGB());
            ClearFrom(1);
        }

        if (m_RpmModel.GetRawValue() > 6200)
        {
            m_PatternPlayer.DrawPixel(1, PeripheralLayer::Color::RGB(0, 20, 0).ToRGB());
            ClearFrom(2);
        }

        if (m_RpmModel.GetRawValue() > 6400)
        {
            m_PatternPlayer.DrawPixel(2, PeripheralLayer::Color::RGB(0, 20, 0).ToRGB());
            ClearFrom(3);
        }

        if (m_RpmModel.GetRawValue() > 6500)
        {
            m_PatternPlayer.DrawPixel(3, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
            ClearFrom(4);
        }

        if (m_RpmModel.GetRawValue() > 6600)
        {
            m_PatternPlayer.DrawPixel(4, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
            ClearFrom(5);
        }

        if (m_RpmModel.GetRawValue() > 6700)
        {
            m_PatternPlayer.DrawPixel(5, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
            ClearFrom(6);
        }

        if (m_RpmModel.GetRawValue() > 6800)
        {
            m_PatternPlayer.DrawPixel(6, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
            ClearFrom(7);
        }

        if (m_RpmModel.GetRawValue() > 6900)
        {
            m_PatternPlayer.DrawPixel(7, PeripheralLayer::Color::RGB(20, 0, 0).ToRGB());
        }
    }

    m_PatternPlayer.Update();
}

void ApplicationLayer::Shiftlight::ClearFrom(int n)
{
    for (int i = n; i < 8; ++i)
    {
        m_PatternPlayer.DrawPixel(i, 0);
    }
}
