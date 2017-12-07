#include "gpio.h"

GPIO *GPIO::m_gpio = 0;

int GPIO::getFourSwitchValue()
{
    return  (getGPIO1()) | (getGPIO2() << 1) | (getGPIO3() << 2) | (getGPIO4() << 3);
}
