#include "VGA.h"
#include "code_def.h"
#include <stdint.h>
#include <stdio.h>

void VGA_print(uint16_t xchar_start,uint16_t ychar_start,uint16_t xchar_end,uint16_t ychar_end,uint32_t color)
{
	delay(500000);
  VGA->XDATA = (xchar_start<<10) + xchar_end;
	VGA->YDATA = (ychar_start<<10) + ychar_end;		
	VGA->COLOR = color;
	delay(500000);		
}