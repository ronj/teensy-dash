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
        const ApplicationLayer::Models::Model& m_RpmModel;
        PeripheralLayer::PatternPlayer& m_PatternPlayer;
        uint16_t m_LowerLimit = 6000;
        uint16_t m_UpperLimit = 7000;
    };
}
