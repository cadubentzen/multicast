#include "lcd.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using std::cerr;
using std::endl;

void LCD::initialize()
{
    m_lcd_fd = open("/dev/lcd0", O_WRONLY);
    if (m_lcd_fd < 0) {
        perror("Error on opening LCD: ");
        exit(1);
    }
}

void LCD::finalize()
{
    close(m_lcd_fd);
}

void LCD::lcd_message(const char* fmt, ...)
{
    va_list vl; 
    va_start(vl, fmt);
    m_lcd_len = vsnprintf(m_lcd_buf, sizeof(m_lcd_buf), fmt, vl);
    va_end(vl);
    write(m_lcd_fd, m_lcd_buf, m_lcd_len);
}

void LCD::lcd_clear_screen()
{
    lcd_message("\033[2J");
}

void LCD::lcd_go_home()
{
    lcd_message("\033[H");
}

void LCD::lcd_clear_and_home()
{
    lcd_clear_screen();
    lcd_go_home();
}

void LCD::displayBoolArray8(bool *values)
{
    lcd_clear_and_home();

    for (int i = 0; i < 8; ++i){
        lcd_message("%d", (int)values[i]);
    }
}
