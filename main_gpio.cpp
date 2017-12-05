#include "handles.h"

#include <unistd.h>

#include "log.h"

void* main_gpio(void* arg)
{
    char *__flag_stop = (char*) arg;
    while (1) {
        // Read GPIO to select port
        // TODO

        // Read boolean array from network
        // TODO

        // Write values to 7-seg display
        // TODO

        sleep(1);
        
        // FIXME: After implementing this function, remove
        //        lines below
        __LOG();
        
        if (*__flag_stop) break;
    }

    std::cerr << "GPIO thread ending..." << std::endl;
}
