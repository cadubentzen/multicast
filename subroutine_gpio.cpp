#include "beagle_subroutines.h"

#include <unistd.h>

#include "log.h"

void* subroutine_gpio(void* arg)
{
    ThreadData *data = static_cast<ThreadData*>(arg);
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

        if (data->flag_stop) break;
    }

    std::cerr << "GPIO thread ending..." << std::endl;
}
