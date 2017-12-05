#include <pthread.h>
#include <signal.h>

#include "handles.h"

char __flag_stop = 0;

void ctrlc_handle(int sig) {
    std::cerr << "Stoping threads..." << std::endl;
    __flag_stop = 1;
}

int main(int argc, char **argv)
{
    pthread_t thread_adc, thread_gpio, thread_app;

    signal(SIGINT, ctrlc_handle); 

    pthread_create(&thread_adc, NULL, main_adc, (void*)&__flag_stop);
    pthread_create(&thread_gpio, NULL, main_gpio, (void*)&__flag_stop);
    pthread_create(&thread_app, NULL, main_app, (void*)&__flag_stop);

    pthread_join(thread_adc, NULL);
    pthread_join(thread_gpio, NULL);
    pthread_join(thread_app, NULL);

    return 0;
}
