#include "adc.h"

#include <stdlib.h>
#include <time.h>

void ADC::initialize()
{
    srand(time(0));
}

void ADC::finalize()
{
}

float ADC::getADC1()
{
    return (rand()%1001) / 1000.0;
}

float ADC::getADC2()
{
    return (rand()%1001) / 1000.0;
}
