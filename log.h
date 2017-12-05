#pragma once

#ifdef DEBUG
#include <iostream>
#define __LOG() \
    std::cerr << __FILE__ << " " \
              << __func__ << " " \
              << __LINE__ << std::endl;
#else
#define __LOG()
#endif
