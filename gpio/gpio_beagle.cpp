#include "gpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

/****************************************************************
* Constants
****************************************************************/

#define SYSFS_GPIO_DIR "/sys/class/gpio"
#define POLL_TIMEOUT (3 * 1000) /* 3 seconds */
#define MAX_BUF 64

#define GPIO_01 68
#define GPIO_02 67
#define GPIO_03 66
#define GPIO_04 69

/****************************************************************
* gpio_export
****************************************************************/
static int gpio_export(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);

    return 0;
}

/****************************************************************
* gpio_unexport
****************************************************************/
static int gpio_unexport(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
    if (fd < 0) {
        perror("gpio/export");
        return fd;
    }

    len = snprintf(buf, sizeof(buf), "%d", gpio);
    write(fd, buf, len);
    close(fd);
    return 0;
}

/****************************************************************
* gpio_set_dir
****************************************************************/
static int gpio_set_dir(unsigned int gpio, unsigned int out_flag)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/direction");
        return fd;
    }

    if (out_flag)
        write(fd, "out", 4);
    else
        write(fd, "in", 3);

    close(fd);
    return 0;
}

/****************************************************************
* gpio_set_value
****************************************************************/
static int gpio_set_value(unsigned int gpio, unsigned int value)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/set-value");
        return fd;
    }

    if (value)
        write(fd, "1", 2);
    else
        write(fd, "0", 2);

    close(fd);
    return 0;
}

/****************************************************************
* gpio_get_value
****************************************************************/
static int gpio_get_value(unsigned int gpio, unsigned int *value)
{
    int fd, len;
    char buf[MAX_BUF];
    char ch;

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY);
    if (fd < 0) {
        perror("gpio/get-value");
        return fd;
    }

    read(fd, &ch, 1);

    if (ch != '0') {
        *value = 1;
    } else {
        *value = 0;
    }

    close(fd);
    return 0;
}


/****************************************************************
* gpio_set_edge
****************************************************************/

static int gpio_set_edge(unsigned int gpio, char *edge)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);

    fd = open(buf, O_WRONLY);
    if (fd < 0) {
        perror("gpio/set-edge");
        return fd;
    }

    write(fd, edge, strlen(edge) + 1);
    close(fd);
    return 0;
}

/****************************************************************
* gpio_fd_open
****************************************************************/

static int gpio_fd_open(unsigned int gpio)
{
    int fd, len;
    char buf[MAX_BUF];

    len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);

    fd = open(buf, O_RDONLY | O_NONBLOCK );
    if (fd < 0) {
        perror("gpio/fd_open");
    }
    return fd;
}

/****************************************************************
* gpio_fd_close
****************************************************************/

static int gpio_fd_close(int fd)
{
    return close(fd);
}

// GPIO Methods

void GPIO::initialize()
{
    gpio_export(GPIO_01);
    gpio_set_dir(GPIO_01, 0);

    gpio_export(GPIO_02);
    gpio_set_dir(GPIO_02, 0);

    gpio_export(GPIO_03);
    gpio_set_dir(GPIO_03, 0);

    gpio_export(GPIO_04);
    gpio_set_dir(GPIO_04, 0);
}

void GPIO::finalize()
{
    // FIXME: should GPIOs be unexported here?
}

bool GPIO::getGPIO1()
{
    unsigned int gpio01_value;
    gpio_get_value(GPIO_01, &gpio01_value);
    return (bool) gpio01_value;
}

bool GPIO::getGPIO2()
{
    unsigned int gpio02_value;
    gpio_get_value(GPIO_02, &gpio02_value);
    return (bool) gpio02_value;
}

bool GPIO::getGPIO3()
{
    unsigned int gpio03_value;
    gpio_get_value(GPIO_03, &gpio03_value);
    return (bool) gpio03_value;
}

bool GPIO::getGPIO4()
{
    unsigned int gpio04_value;
    gpio_get_value(GPIO_04, &gpio04_value);
    return (bool) gpio04_value;
}
