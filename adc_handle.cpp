#include "handles.h"

#include <unistd.h>

#include "log.h"

void* adc_handle(void*)
{
    while (1) {
        // Read ADC values
        // TODO
         
        // Write ADC values to multicast socket
        // TODO

        // Sleep 1 second
        sleep(1);

        // FIXME: After implementing this function, remove
        //        lines below
        __LOG();
    }
}
