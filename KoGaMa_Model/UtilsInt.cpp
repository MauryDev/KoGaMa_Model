#include "UtilsInt.h"

bool UtilsInt::Is8bit(int16_t val)
{
    return val>= -128 && val < 128;
}
