#pragma once

#include "PeripheralLayer/PatternPlayer.h"

namespace PeripheralLayer
{
    class PatternPlayer;

    class LedPattern
    {
    public:
        virtual void Update(PatternPlayer& player, uint32_t tickcount) = 0;
    };

    class OffPattern : public LedPattern
    {
    public:
        void Update(PatternPlayer& player, uint32_t) override;
    };

    class BlinkPattern : public LedPattern
    {
    public:
        BlinkPattern(uint32_t blinkdelay);
        void Update(PatternPlayer& player, uint32_t tickcount) override;

    private:
        bool m_BlinkState = false;
        uint32_t m_PreviousBlink = 0;
        uint32_t m_BlinkPeriod = 0;
    };

    class BarFillPattern : public LedPattern
    {
    public:
        void Update(PeripheralLayer::PatternPlayer& player, uint32_t) override;
        void SetBarLength(uint8_t length);

    private:
        uint8_t m_BarLength = 0;
    };

    class ScanPattern : public LedPattern
    {
    public:
        void Update(PatternPlayer& player, uint32_t tickcount) override;

    private:
        uint8_t m_Position = 0;
        uint8_t m_IncrementPeriod = 100;
        uint32_t m_PreviousIncrement = 0;
    };
}
