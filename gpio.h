#pragma once

class GPIO {
public:
    static GPIO* singleton() {
        if (!m_gpio) m_gpio = new GPIO();
        return m_gpio;
    };

    void initialize();
    void finalize();

    // Reads a integer values from 0 to 15
    int getFourSwitchValue();

    // Functions that implement reading GPIO
    // NOTICE: GPIO1..4 don't need to be exactly
    // 1 to 4 on the schematics. It is up to you
    // to choose which pins you'll use, as long
    // as you keep it consistent.
    bool getGPIO1();
    bool getGPIO2();
    bool getGPIO3();
    bool getGPIO4();

private:
    static GPIO *m_gpio;
    GPIO() {}
};
