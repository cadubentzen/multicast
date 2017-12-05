#include <pthread.h>
#include <signal.h>
#include <iostream>
#include <cstdlib>

#include "beagle_subroutines.h"

#define MULTICAST_IP "225.0.0.37"

ThreadData data;

void ctrlc_handle(int sig) {
    std::cerr << "Stoping threads..." << std::endl;
    data.flag_stop = 1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0]
                  << " <group_number>"
                  << std::endl;
        exit(1);
    }

    int group = atoi(argv[1]);

    data.flag_stop = 0;
    data.ip = MULTICAST_IP;

    if (group < 10) {
        data.adc_port = "970";
        data.gpio_port = "980";
    } else {
        data.adc_port = "97";
        data.gpio_port = "98";
    }

    data.adc_port  += argv[1];
    data.gpio_port += argv[1];


    std::cerr << "IP = "        << data.ip << std::endl
              << "ADC_PORT = "  << data.adc_port << std::endl
              << "GPIO_PORT = " << data.gpio_port << std::endl
              << std::endl;

    pthread_t thread_adc, thread_gpio, thread_app;

    signal(SIGINT, ctrlc_handle);

    pthread_create(&thread_adc, NULL, subroutine_adc, (void*)&data);
    pthread_create(&thread_gpio, NULL, subroutine_gpio, (void*)&data);

    pthread_join(thread_adc, NULL);
    pthread_join(thread_gpio, NULL);

    return 0;
}
