#include "handles.h"

#include <unistd.h>

#include "log.h"

void* gpio_handle(void*)
{
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
    }
}
