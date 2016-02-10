#pragma once

#include <cstdint>

namespace PeripheralLayer
{
    class PatternPlayer;
}

namespace ApplicationLayer
{
    namespace Models
    {
        class Model;
    }

    class Shiftlight
    {
    public:
        Shiftlight(PeripheralLayer::PatternPlayer& patternPlayer, const ApplicationLayer::Models::Model& rpmModel);

        void Update(uint32_t now);

    private:
        void ClearFrom(int n);

    private:
        const ApplicationLayer::Models::Model& m_RpmModel;
        PeripheralLayer::PatternPlayer& m_PatternPlayer;
        bool m_BlinkState = false;
        uint32_t m_PreviousBlink = 0;
    };
}
