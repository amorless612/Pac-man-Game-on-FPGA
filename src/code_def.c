#include "code_def.h"
#include <stdint.h>
#include <string.h>

uint32_t LCD_ini_finish;
void SYSInit(void)
{
	// IRQ enable
	NVIC_CTRL_ADDR	=	0x3;

	// Systick initial
	Set_SysTick_CTRL(0);

}

void delay(uint32_t time)
{
	Set_SysTick_CTRL(0);
	Set_SysTick_LOAD(time);
	Set_SysTick_VALUE(0);
	Set_SysTick_CTRL(0x7);
	__wfi();
}

void LCD_INI_FINISH(void)
{
	LCD_ini_finish = 1; 
}
