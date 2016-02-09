#pragma once

#include "RotaryEncoder.h"

//#include <Encoder.h>
//#undef PI

// Enable this to emit codes twice per step.
//#define HALF_STEP

// Enable weak pullups
#define ENABLE_PULLUPS

// Values returned by 'process'
// No complete step yet.
#define DIR_NONE 0x0
// Clockwise step.
#define DIR_CW 0x10
// Anti-clockwise step.
#define DIR_CCW 0x20

class Rotary
{
  public:
    Rotary(char, char);
    // Process pin(s)
    unsigned char process();
  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
};

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
        //Encoder m_Encoder;
        Rotary m_Encoder;
	};
}
