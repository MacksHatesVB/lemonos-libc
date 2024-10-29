#pragma once

#include <stdlib.h>

static inline void assert(int expr) {
        if (!expr) {
                exit(-1);
        }
}
