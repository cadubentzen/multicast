#pragma once

class ADC {
public:
    static ADC* singleton() {
        return 0;    
    };
    virtual void initialize() {};

    virtual float getADC1() = 0;
    virtual float getADC2() = 0;

protected:
    static ADC *m_adc;
};


class FakeADC : public ADC {
public:
    static ADC* singleton() {
        if (!m_adc) m_adc = new FakeADC();
        return m_adc;
    }

    float getADC1();
    float getADC2();

private:
    FakeADC() {}
};

class BeagleADC : public ADC {
public:
    static ADC* singleton() {
        if (!m_adc) m_adc = new BeagleADC();
        return m_adc;
    }

    float getADC1(); // TODO
    float getADC2(); // TODO

private:
    BeagleADC() {}
};
