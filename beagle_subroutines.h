#pragma once

#include <string>

using std::string;

struct ThreadData {
    char flag_stop;
    string ip;
    string adc_port;
    string gpio_port;
};

void* subroutine_adc(void*);
void* subroutine_gpio(void*);
