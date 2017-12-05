#include <pthread.h>

#include "handles.h"

int main(int argc, char **argv)
{
    pthread_t thread_adc, thread_gpio, thread_app;

    pthread_create(&thread_adc, NULL, adc_handle, NULL);
    pthread_create(&thread_gpio, NULL, gpio_handle, NULL);
    pthread_create(&thread_app, NULL, app_handle, NULL);

    pthread_join(thread_adc, NULL);
    pthread_join(thread_gpio, NULL);
    pthread_join(thread_app, NULL);

    return 0;
}
