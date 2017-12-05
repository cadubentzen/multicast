#pragma once

#ifdef DEBUG
#include <iostream>
#include <string.h>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define __LOG() \
    std::cerr << __FILENAME__ << " " \
              << __func__ << " " \
              << __LINE__ << std::endl;
#else
#define __LOG()
#endif
