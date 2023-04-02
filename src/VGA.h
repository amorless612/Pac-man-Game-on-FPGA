#ifndef _VGA_H_
#define _VGA_H_

#include<stdint.h>

void VGA_print(uint16_t xchar_start,uint16_t ychar_start,uint16_t xchar_end,uint16_t ychar_end,uint32_t color);
	
typedef struct
{
    uint32_t XDATA;
    uint32_t YDATA;
    uint32_t COLOR;
}VGAStr;

#define VGA_BASE 0x30001000
#define VGA ((VGAStr *)VGA_BASE)

#endif
