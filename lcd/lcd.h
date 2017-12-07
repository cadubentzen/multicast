#pragma once

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
};
