#include "handles.h"

#include <unistd.h>
#include <iostream>

#include "adc.h"

#include "log.h"

#ifdef BEAGLE
typedef BeagleADC PlatformADC;
#else
typedef FakeADC PlatformADC;
#endif

void* main_adc(void* arg)
{
    char *__flag_stop = (char*) arg;
    float adc_values[2];

    PlatformADC::singleton()->initialize();

    // MulticastSocket multicastSocket (IP, PORT);
    
    while (1) {
        // Read ADC values
        adc_values[0] =  PlatformADC::singleton()->getADC1();
        adc_values[1] =  PlatformADC::singleton()->getADC2();
         
        // Write ADC values to multicast socket
       //  multicastSocket.write((void*)adc_values, sizeof(adc_values));
        // TODO

        // Sleep 1 second
        sleep(1);

        // FIXME: After implementing this function, remove
        //        lines below
        __LOG();

        if (*__flag_stop) break;
        // TODO: Add a flag to stop the thread
    }
    
    std::cerr << "ADC thread ending..." << std::endl;
}
