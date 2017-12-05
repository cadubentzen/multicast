#include "handles.h"

#include <unistd.h>

#include "log.h"

void* main_app(void* arg)
{
    char *__flag_stop = (char*) arg;
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
        
        if (*__flag_stop) break;
    }
    
    std::cerr << "APP thread ending..." << std::endl;
}
