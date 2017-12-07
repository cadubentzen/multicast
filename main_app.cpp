#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <signal.h>

#include "config.h"

#include "multicast_receiver.h"
#include "multicast_sender.h"

using std::cerr;
using std::endl;

void ctrlc_handle(int sig) {
    cerr << "Stopping APP..." << endl;
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        cerr << "Usage: " << argv[0]
             << " <adc_group>" << endl;
        exit(1);
    }

    int adc_port = 9700 + atoi(argv[1]);
    int bool_port = 9800 + GROUP_NUMBER;

    cerr << "IP = " << MULTICAST_IP << endl
         << "ADC_PORT = " << adc_port << endl
         << "BOOL_PORT = " << bool_port << endl << endl;

    MulticastReceiver receiver (MULTICAST_IP, adc_port);
    MulticastSender sender (MULTICAST_IP, bool_port);

    float adc_values[2];
    size_t len_adc = sizeof(adc_values);

    bool bool_values[8];
    size_t len_bool = sizeof(bool_values);

#ifdef DEBUG
    cerr << "LEN_ADC = " << len_adc << endl
         << "LEN_BOOL = " << len_bool << endl << endl;
#endif

    signal(SIGINT, ctrlc_handle);

    while (1) {
        // Read ADC values from multicast socket
        receiver.receive((void*)adc_values, sizeof(adc_values));

#ifdef DEBUG
        cerr << "ADC1 = " << adc_values[0] << endl
             << "ADC2 = " << adc_values[1] << endl << endl;
#endif

        // Perform calculation:
        // The calculation used here is pretty simple,
        //    value = (int) (4 + (adc1 - adc2) * 4)
        // so value goes from 0 to 8, which makes
        // a progress bar if the bool values are showed in a line
        int value = (int) (4 * (adc_values[0] - adc_values[1]) + 4);
#ifdef DEBUG
        cerr << "VALUE = " << value << endl;
        cerr << "BOOL = ";
#endif
        for(int i = 0; i < 8; i++) {
            if (i < value) bool_values[i] = 1;
            else bool_values[i] = 0;
#ifdef DEBUG
            cerr << bool_values[i] << " ";
#endif
        }
#ifdef DEBUG
        cerr << endl << endl;
#endif
        // Write boolean array to multicast socket
        sender.send((void*)bool_values, len_bool);
    }
}
