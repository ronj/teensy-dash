#include "TeensyDigitalPin.h"

#include "Common/DisableInterruptContext.h"

#include "core_pins.h"

#include <array>
#include <functional>

namespace
{
    static std::array<std::function<void()>, CORE_NUM_DIGITAL> interruptFunctions;

    static void portc_interrupt2(void);

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
          case LOW: mask = 0x08; break;
          case HIGH:    mask = 0x0C; break;
          default: return;
        }
        mask = (mask << 16) | 0x01000000;
        config = portConfigRegister(pin);

        attachInterruptVector2(IRQ_PORTC, portc_interrupt2);
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
}

HardwareLayer::TeensyDigitalPin::TeensyDigitalPin(const uint8_t pin)
    : m_Pin(pin)
{
    pinMode(m_Pin, INPUT);
}

HardwareLayer::TeensyDigitalPin::~TeensyDigitalPin()
{
    detachInterrupt2(m_Pin);
}

void HardwareLayer::TeensyDigitalPin::EnableInterrupt(InterruptType mode, std::function<void()> isr)
{
    attachInterrupt2(m_Pin, isr, RISING);
}
