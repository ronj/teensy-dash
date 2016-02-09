#include "TeensyDigitalPin.h"

#include "Common/DisableInterruptContext.h"

#include "core_pins.h"

#include <array>
#include <functional>

namespace
{
    static std::array<std::function<void()>, CORE_NUM_DIGITAL> interruptFunctions;

    static void portc_interrupt2(void);
    static void portd_interrupt2(void);

    void attachInterruptVector2(enum IRQ_NUMBER_t irq, void (*function)(void))
    {
        _VectorsRam[irq + 16] = function;
    }

    void attachInterrupt2(uint8_t pin, std::function<void()> function, int mode)
    {
        volatile uint32_t *config;
        uint32_t cfg, mask;

        if (pin >= CORE_NUM_DIGITAL) return;
        switch (mode) {
          case CHANGE:  mask = 0x0B; break;
          case RISING:  mask = 0x09; break;
          case FALLING: mask = 0x0A; break;
          case LOW:     mask = 0x08; break;
          case HIGH:    mask = 0x0C; break;
          default: return;
        }
        mask = (mask << 16) | 0x01000000;
        config = portConfigRegister(pin);

        attachInterruptVector2(IRQ_PORTC, portc_interrupt2);
        attachInterruptVector2(IRQ_PORTD, portd_interrupt2);
        {
            Common::DisableInterruptContext interruptDisable;
            cfg = *config;
            cfg &= ~0x000F0000;     // disable any previous interrupt
            *config = cfg;
            interruptFunctions[pin] = function;    // set the function pointer
            cfg |= mask;
            *config = cfg;          // enable the new interrupt
        }
    }

    void detachInterrupt2(uint8_t pin)
    {
        volatile uint32_t *config;

        config = portConfigRegister(pin);
        {
            Common::DisableInterruptContext interruptDisable;
            *config = ((*config & ~0x000F0000) | 0x01000000);
            interruptFunctions[pin] = nullptr;
        }
    }

    static void portc_interrupt2(void)
    {
        // TODO: these are inefficent.  Use CLZ somehow....
        uint32_t isfr = PORTC_ISFR;
        PORTC_ISFR = isfr;
        if ((isfr & CORE_PIN22_BITMASK) && interruptFunctions[22]) interruptFunctions[22]();
        if ((isfr & CORE_PIN23_BITMASK) && interruptFunctions[23]) interruptFunctions[23]();
    }

    static void portd_interrupt2(void)
    {
        uint32_t isfr = PORTD_ISFR;
        PORTD_ISFR = isfr;
        if ((isfr & CORE_PIN2_BITMASK) && interruptFunctions[2]) interruptFunctions[2]();
        if ((isfr & CORE_PIN5_BITMASK) && interruptFunctions[5]) interruptFunctions[5]();
        if ((isfr & CORE_PIN6_BITMASK) && interruptFunctions[6]) interruptFunctions[6]();
        if ((isfr & CORE_PIN7_BITMASK) && interruptFunctions[7]) interruptFunctions[7]();
        if ((isfr & CORE_PIN8_BITMASK) && interruptFunctions[8]) interruptFunctions[8]();
        if ((isfr & CORE_PIN14_BITMASK) && interruptFunctions[14]) interruptFunctions[14]();
        if ((isfr & CORE_PIN20_BITMASK) && interruptFunctions[20]) interruptFunctions[20]();
        if ((isfr & CORE_PIN21_BITMASK) && interruptFunctions[21]) interruptFunctions[21]();
    }
}

HardwareLayer::TeensyDigitalPin::TeensyDigitalPin(const uint8_t pin)
    : TeensyDigitalPin(pin, PinType::Input)
{
}

HardwareLayer::TeensyDigitalPin::TeensyDigitalPin(const uint8_t pin, PinType type)
    : m_Pin(pin)
{
    switch (type)
    {
        case PinType::Input: pinMode(m_Pin, INPUT); break;
        case PinType::Output: pinMode(m_Pin, OUTPUT); break;
        case PinType::InputPullUp: pinMode(m_Pin, INPUT_PULLUP); break;
    }
}

HardwareLayer::TeensyDigitalPin::~TeensyDigitalPin()
{
	DisableInterrupt();
}

uint8_t HardwareLayer::TeensyDigitalPin::Read()
{
	return digitalRead(m_Pin);
}

void HardwareLayer::TeensyDigitalPin::EnableInterrupt(InterruptType mode)
{
    switch (mode)
    {
        case InterruptType::Rising: attachInterrupt2(m_Pin, OnInterrupt, RISING); break;
		case InterruptType::Falling: attachInterrupt2(m_Pin, OnInterrupt, FALLING); break;
		case InterruptType::Change: attachInterrupt2(m_Pin, OnInterrupt, CHANGE); break;
		case InterruptType::Low: attachInterrupt2(m_Pin, OnInterrupt, LOW); break;
		case InterruptType::High: attachInterrupt2(m_Pin, OnInterrupt, HIGH); break;
    }
}

void HardwareLayer::TeensyDigitalPin::DisableInterrupt()
{
	detachInterrupt2(m_Pin);
}
