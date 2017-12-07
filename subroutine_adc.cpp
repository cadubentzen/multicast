#include "beagle_subroutines.h"

#include <unistd.h>
#include <iostream>

#include "config.h"

#include "adc.h"
#include "multicast_sender.h"

using std::cerr;
using std::endl;

void* subroutine_adc(void* arg)
{
    cerr << "Starting ADC thread..." << endl;

    ThreadDataADC *data = static_cast<ThreadDataADC*>(arg);
    int port = data->port;
    int *flag_stop = data->flag_stop;

    float adc_values[2];
    size_t len = sizeof(adc_values);

    ADC::singleton()->initialize();

    MulticastSender sender (MULTICAST_IP, port);

    while (1) {
        // Read ADC values
        adc_values[0] =  ADC::singleton()->getADC1();
        adc_values[1] =  ADC::singleton()->getADC2();

        // Write ADC values to multicast socket
        sender.send((void*)adc_values, len);

        // Sleep 1 second
        sleep(1);

        if (*flag_stop) break;
    }

    ADC::singleton()->finalize();

    cerr << "ADC thread ending..." << endl;
}
