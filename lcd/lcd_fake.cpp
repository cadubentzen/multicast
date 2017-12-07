#include "lcd.h"

#include <iostream>

using std::cerr;
using std::endl;

void LCD::initialize()
{
}

void LCD::finalize()
{
}

void LCD::displayBoolArray8(bool *values)
{
    for(int i = 0; i < 8; i++) {
        cerr << values[i] << " ";
    }
    cerr << '\r';
}
