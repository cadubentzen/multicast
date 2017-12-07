#include <stdio.h> // for snprintf
#include <fcntl.h>  // for open and O_RDONLY
#include <unistd.h> // for read and close
#include <stdlib.h> // for atoi
#include "adc.h"

#define ADC4 "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define ADC6 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define MAX_BUFF 64

ADC *ADC::m_adc = 0;

void ADC::initialize()
{
    // TODO: implement required initialization for Beagle ADC
}

void ADC::finalize()
{
    // TODO: implement required finalization for Beagle ADC
}

float ADC::getADC1()
{
    // TODO: implement reading ADC1 value for Beagle

    int fd = 0;
    char buf_ADC4[MAX_BUFF] = {0};
    snprintf(buf_ADC4, sizeof(buf_ADC4), ADC4);
    char adc4[5] = {0,0,0,0,0}; // four digits and null terminator \0

    fd = open(buf_ADC4, O_RDONLY | O_NONBLOCK);
    read(fd, adc4, 4); // reads 4 bytes from file FD to adc4
    close(fd);

    return atoi(adc4)/4000.0;
}

float ADC::getADC2()
{
    // TODO: implement reading ADC2 value for Beagle

    int fd = 0;
    char buf_ADC6[MAX_BUFF] = {0};
    snprintf(buf_ADC6, sizeof(buf_ADC6), ADC6);
    char adc6[5] = {0,0,0,0,0}; // four digits and null terminator \0

    fd = open(buf_ADC6, O_RDONLY | O_NONBLOCK);
    read(fd, adc6, 4); // reads 4 bytes from file FD to adc4
    close(fd);

    return atoi(adc6)/4000.0;
}
