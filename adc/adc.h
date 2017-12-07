#pragma once

class ADC {
public:
    static ADC* singleton() {
        if (!m_adc) m_adc = new ADC();
        return m_adc;
    };

    void initialize();
    void finalize();

    float getADC1();
    float getADC2();

private:
    ADC() {}
    static ADC *m_adc;
};

// Struct to pass data to thread
struct ThreadDataADC {
    int port;
    int *flag_stop;
};
