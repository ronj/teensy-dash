#include "TeensyRotaryEncoder.h"

#include "Common/Math.h"

HardwareLayer::TeensyRotaryEncoder::TeensyRotaryEncoder()
    : m_Encoder(3, 4)
{
}

bool HardwareLayer::TeensyRotaryEncoder::NewValueAvailable()
{
    m_CurrentEncoderValue = m_Encoder.read();
    return (m_CurrentEncoderValue != m_PreviousEncoderValue);
}

int8_t HardwareLayer::TeensyRotaryEncoder::GetDirection()
{
    int8_t direction = 0;

    if (m_CurrentEncoderValue % 4 == 0)
    {
        m_Encoder.write(0);
        direction = Common::Math::Sign(m_CurrentEncoderValue);
    }

    m_PreviousEncoderValue = m_CurrentEncoderValue;

    return direction;
}
