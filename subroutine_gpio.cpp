#include "beagle_subroutines.h"

#include "config.h"

#include <unistd.h>
#include <iostream>

#include "gpio.h"
#include "multicast_receiver.h"

using std::cerr;
using std::endl;

void* subroutine_gpio(void* arg)
{
    cerr << "Starting GPIO thread..." << endl;

    int *flag_stop = static_cast<int*>(arg);

    GPIO::singleton()->initialize();

    bool bool_values[8];
    size_t len_bool = sizeof(bool_values);

    while (1) {
        // Read GPIO to select port
        int port = 9800 + GPIO::singleton()->getFourSwitchValue();
#ifdef DEBUG
        cerr << "BOOL_PORT = " << port << endl;
#endif
        MulticastReceiver receiver (MULTICAST_IP, port);

        // Read boolean array from network
        receiver.receive((void*)bool_values, len_bool);
#ifdef DEBUG
        cerr << "BOOL_VALUES = ";
        for(int i = 0; i < 8; i++)
            cerr << bool_values[i] << " ";
        cerr << endl;
#endif

        // Write values to LCD display
        // TODO

        sleep(1);
    }

    GPIO::singleton()->finalize();

    cerr << "GPIO thread ending..." << endl;
}
