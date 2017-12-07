#include <unistd.h>
#include <iostream>
#include <stdlib.h>

#include "config.h"

#include "multicast_receiver.h"

using std::cerr;
using std::endl;

char flag_stop = 0;

void ctrlc_handle(int sig) {
    flag_stop = 1;
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0]
             << " <adc_port> <bool_port>" << endl;
        exit(1);
    }

    int adc_port = atoi(argv[1]);
    int bool_port = atoi(argv[2]);

    cerr << "IP = " << MULTICAST_IP << endl
         << "ADC_PORT = " << adc_port << endl
         << "BOOL_PORT = " << bool_port << endl << endl;

    MulticastReceiver receiver (MULTICAST_IP, adc_port);
    MulticastReceiver sender (MULTICAST_IP, bool_port);

    float adc_values[2];
    size_t len_adc = sizeof(adc_values);

    bool bool_values[8];
    size_t len_bool = sizeof(bool_values);

#ifdef DEBUG
    cerr << "LEN_ADC = " << len_adc << endl
         << "LEN_BOOL = " << len_bool << endl << endl;
#endif

    while (1) {
        // Read ADC values from multicast socket
        receiver.receive((void*)adc_values, sizeof(adc_values));

#ifdef DEBUG
        cerr << "ADC1 = " << adc_values[0] << endl
             << "ADC2 = " << adc_values[1] << endl << endl;
#endif

        // Perform calculation
        // TODO
        
        // Write boolean array to multicast socket
        // TODO
        
        if (flag_stop) break;
    }

    cerr << "Stopping APP..." << endl;
}
