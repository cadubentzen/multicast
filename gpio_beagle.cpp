#include "gpio.h"

#define GPIO_01 68
#define GPIO_02 67
#define GPIO_03 66
#define GPIO_04 69

void GPIO::initialize()
{
    // TODO: necessary initializations
    gpio_export(GPIO_01);
    gpio_set_dir(GPIO_01, 0);

    gpio_export(GPIO_02);
    gpio_set_dir(GPIO_02, 0);

    gpio_export(GPIO_03);
    gpio_set_dir(GPIO_03, 0);

    gpio_export(GPIO_04);
    gpio_set_dir(GPIO_04, 0);
}

void GPIO::finalize()
{
    // TODO: necessary finalizations
}

bool GPIO::getGPIO1()
{
    // TODO: Read GPIO from beagle
    int gpio01_value;
    gpio_get_value(GPIO_01, &gpio01_value);
    return (bool) gpio01_value;
}

bool GPIO::getGPIO2()
{
    // TODO: Read GPIO from beagle
    int gpio02_value;
    gpio_get_value(GPIO_02, &gpio02_value);
    return (bool) gpio02_value;
}

bool GPIO::getGPIO3()
{
    // TODO: Read GPIO from beagle
    int gpio03_value;
    gpio_get_value(GPIO_03, &gpio03_value);
    return (bool) gpio03_value;
}

bool GPIO::getGPIO4()
{
    // TODO: Read GPIO from beagle
    int gpio04_value;
    gpio_get_value(GPIO_04, &gpio04_value);
    return (bool) gpio04_value;
}
