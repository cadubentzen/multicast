#include "adc.h"

ADC *ADC::m_adc = 0;

float FakeADC::getADC1() {
    return 0.5;
}

float FakeADC::getADC2() {
    return 0.7;
}

float BeagleADC::getADC1() {
    // TODO
    return 0.5;
}

float BeagleADC::getADC2() {
    // TODO
    return 0.7;
}
