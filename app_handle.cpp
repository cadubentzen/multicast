#include "handles.h"

#include <unistd.h>

#include "log.h"

void* app_handle(void*)
{
    while (1) {
        // Read ADC values from multicast socket
        // TODO
        
        // Perform calculation
        // TODO
        
        // Write boolean array to multicast socket
        // TODO

        // FIXME: after implementing this function, remove lines below
        __LOG();
        sleep(1);
    }
}
