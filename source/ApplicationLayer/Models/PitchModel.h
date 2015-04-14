#pragma once

#include "Model.h"

namespace PeripheralLayer
{
    class AccelerationAxis;
}

namespace ApplicationLayer
{
    namespace Models
    {
        class PitchModel : public Model
        {
        public:
            PitchModel(const PeripheralLayer::AccelerationAxis&, const PeripheralLayer::AccelerationAxis&, const PeripheralLayer::AccelerationAxis&);

            virtual int32_t GetRawValue() const;
            virtual const char* GetFormattedValue() const;
            virtual void Update(uint32_t);

        private:
            const PeripheralLayer::AccelerationAxis& m_XAxis;
            const PeripheralLayer::AccelerationAxis& m_YAxis;
            const PeripheralLayer::AccelerationAxis& m_ZAxis;

            int32_t m_PitchMilliDegrees;
        };
    }
}
