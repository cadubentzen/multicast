#include "adc.h"

#include <stdio.h> // for snprintf
#include <fcntl.h>  // for open and O_RDONLY
#include <unistd.h> // for read and close
#include <stdlib.h> // for atoi

#define ADC4 "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define ADC6 "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define MAX_BUFF 64

void ADC::initialize()
{
}

void ADC::finalize()
{
}

float ADC::getADC1()
{
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
    int fd = 0;
    char buf_ADC6[MAX_BUFF] = {0};
    snprintf(buf_ADC6, sizeof(buf_ADC6), ADC6);
    char adc6[5] = {0,0,0,0,0}; // four digits and null terminator \0

    fd = open(buf_ADC6, O_RDONLY | O_NONBLOCK);
    read(fd, adc6, 4); // reads 4 bytes from file FD to adc4
    close(fd);

    return atoi(adc6)/4000.0;
}
