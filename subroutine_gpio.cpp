#include "beagle_subroutines.h"

#include <unistd.h>
#include <iostream>

using std::cerr;
using std::endl;

void* subroutine_gpio(void* arg)
{
    cerr << "Starting GPIO thread..." << endl;
    
    int *flag_stop = static_cast<int*>(arg);

    while (1) {
        // Read GPIO to select port
        // TODO

        // Read boolean array from network
        // TODO

        // Write values to 7-seg display
        // TODO

        sleep(1);

        if (*flag_stop) break;
    }

    cerr << "GPIO thread ending..." << endl;
}
