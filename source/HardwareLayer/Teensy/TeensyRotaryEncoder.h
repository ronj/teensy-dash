#pragma once

#include "RotaryEncoder.h"

#include <Encoder.h>
#undef PI

namespace HardwareLayer
{
	class TeensyRotaryEncoder
		: public RotaryEncoder
	{
	public:
        TeensyRotaryEncoder();

        virtual bool NewValueAvailable();
        virtual int8_t GetDirection();

    private:
        int32_t m_CurrentEncoderValue = 0;
        int32_t m_PreviousEncoderValue = 0;
        Encoder m_Encoder;
	};
}
