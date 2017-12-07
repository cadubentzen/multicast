#include "gpio.h"

void GPIO::initialize()
{
}

void GPIO::finalize()
{
}

// Fake implementation always return 0001 = 1 in getFourSwitchValues()
bool GPIO::getGPIO1()
{
    return 1;
}

bool GPIO::getGPIO2()
{
    return 0;
}

bool GPIO::getGPIO3()
{
    return 0;
}

bool GPIO::getGPIO4()
{
    return 0;
}
