#include <pthread.h>
#include <signal.h>
#include <iostream>
#include <stdlib.h>

#include "config.h"

#include "beagle_subroutines.h"
#include "adc.h"

using std::cerr;
using std::endl;

pthread_t thread_adc, thread_gpio;
int flag_stop = 0;

void ctrlc_handle(int sig) {
    cerr << "Stoping threads..." << endl;
    // This flag is checked in the threads, so setting
    // it to one stops the threads.
    flag_stop = 1;
    // GPIO thread needs to be cancelled because it is blocked in socket read()
    pthread_cancel(thread_gpio);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0]
             << " <group_number>"
             << endl;
        exit(1);
    }

    int adc_port = 9700 + atoi(argv[1]);

    cerr << "IP = "        << MULTICAST_IP << endl
         << "ADC_PORT = "  << adc_port << endl
         << endl;


    signal(SIGINT, ctrlc_handle);

    ThreadDataADC dataADC;
    dataADC.port = adc_port;
    dataADC.flag_stop = &flag_stop;

    pthread_create(&thread_adc, NULL, subroutine_adc, (void*)&dataADC);
    pthread_create(&thread_gpio, NULL, subroutine_gpio, (void*)&flag_stop);

    pthread_join(thread_adc, NULL);
    pthread_join(thread_gpio, NULL);

    return 0;
}
