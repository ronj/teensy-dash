#pragma once

#include "RepresentableModel.h"

namespace PeripheralLayer
{
    class AccelerationAxis;
}

namespace ApplicationLayer
{
    namespace Models
    {
		class AccelerationModel : public RepresentableModel
        {
        public:
            AccelerationModel(const PeripheralLayer::AccelerationAxis&);

            virtual int32_t GetRawValue() const;
            virtual const char* GetFormattedValue() const;
            virtual void Update(uint32_t);

        private:
            const PeripheralLayer::AccelerationAxis& m_Axis;
            int32_t m_AccelerationMilliG;
        };
    }
}
