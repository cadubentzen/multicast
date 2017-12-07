#pragma once

#ifdef BEAGLE
    #define LCD_BUF_SIZE 100
#endif

class LCD {
public:
    static LCD* singleton() {
        if (!m_lcd) m_lcd = new LCD();
        return m_lcd;
    }

    void initialize();
    void finalize();

    void displayBoolArray8(bool *values);

private:
    static LCD *m_lcd;
    LCD() {}
#ifdef BEAGLE
    char m_lcd_buf[LCD_BUF_SIZE];
    int m_lcd_len;
    int m_lcd_fd;

    void lcd_message(const char *fmt, ...);
    void lcd_clear_screen();
    void lcd_go_home();
    void lcd_clear_and_home();
#endif
};
