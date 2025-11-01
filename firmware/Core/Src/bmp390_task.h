#ifndef BMP390_H__
#define BMP390_H__

#include <stdint.h>
#include "user_define.h"
#include "./bosch/bmp3_defs.h"
#include "main.h"


#if defined(USE_BMP390)


void StartBMP390Task(void const * argument);

#endif

#endif

