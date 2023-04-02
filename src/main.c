#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include "code_def.h"
#include "UART.h"
#include "VGA.h"
#include <stdlib.h>
extern uint32_t key_flag;
extern uint32_t music_flag;
extern uint32_t LCD_ini_finish;
extern uint32_t uart_flag;
uint16_t x, nx;
uint16_t y, ny;
uint16_t vector=0;

const unsigned char a[32][24] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 0},
    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    { 0, 3, 1, 1, 1, 3, 1, 1, 1, 1, 3, 0, 0, 3, 1, 1, 1, 1, 3, 1, 1, 1, 3, 0},
    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    { 0, 1, 0, 0, 0, 1, 0, 2, 2, 0, 3, 1, 1, 3, 0, 2, 2, 0, 1, 0, 0, 0, 1, 0},
    { 0, 1, 1, 1, 1, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 3, 1, 1, 1, 1, 0},
    { 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    { 1, 1, 1, 1, 1, 3, 1, 3, 0, 2, 2, 2, 2, 2, 2, 0, 3, 1, 3, 1, 1, 1, 1, 1},
    { 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 3, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 2, 2, 2, 0},
    { 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
    { 0, 1, 1, 1, 1, 3, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 3, 1, 1, 1, 1, 0},
    { 0, 1, 0, 0, 0, 1, 0, 2, 2, 0, 3, 1, 1, 3, 0, 2, 2, 0, 1, 0, 0, 0, 1, 0},
    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
    { 0, 3, 1, 1, 1, 3, 1, 1, 1, 1, 3, 0, 0, 3, 1, 1, 1, 1, 3, 1, 1, 1, 3, 0},
    { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
	  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0},
	  { 0, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
void food(uint16_t n, uint16_t m){
	LCD_Fill(n*10+4, m*10+4, n*10 + 6, m*10 + 6, BLACK);
}
void pitnt_0(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_1(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n+2)*2, (m  )*2, (n+2)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_2(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n  )*2, (m+4)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_3(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);	
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_4(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+3)*2, (m  )*2, (n+3)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_5(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);	
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+2)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+4)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_6(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);	
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+5)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+4)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_7(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_8(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);	
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+5)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_9(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);	
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+3)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_A(uint16_t n, uint16_t m,int color){
		LCD_Fill((n+2)*2,  m   *2, (n+2)*2 + 2,  m   *2 + 2, color);
		LCD_Fill((n+1)*2, (m+1)*2, (n+1)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+1)*2, (n+3)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+2)*2, (n+1)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+2)*2, (n+3)*2 + 2, (m+2)*2 + 2, color);	
		LCD_Fill((n)*  2, (m+3)*2, (n)*  2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n)*  2, (m+4)*2, (n)*  2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+4)*2, (n+4)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n)*  2, (m+5)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n)*  2, (m+6)*2, (n)*  2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);		
}
void pitnt_B(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n+3)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+6)*2, (n+3)*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_C(uint16_t n, uint16_t m,int color){
		LCD_Fill((n+1)*2,  m   *2, (n+4)*2 + 2,  m   *2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);		
}
void pitnt_D(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n+3)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+3)*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);	
}	
void pitnt_E(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);	
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+2)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n  )*2, (m+4)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_F(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_G(uint16_t n, uint16_t m,int color){
		LCD_Fill((n+1)*2, (m  )*2, (n+3)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+4)*2, (n+4)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+5)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+6)*2, (n+3)*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_H(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m  )*2, (n+4)*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+3)*2, (n+3)*2 + 2, (m+3)*2 + 2, color);	
}	
void pitnt_I(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n+2)*2, (m+1)*2, (n+2)*2 + 2, (m+5)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_J(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n+2)*2, (m+1)*2, (n+2)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+5)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+6)*2, (n+1)*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_K(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n+2)*2, (m+1)*2, (n+3)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+2)*2, (n+1)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+4)*2, (n+1)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+5)*2, (n+3)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_L(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+5)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	                                                       
} 
void pitnt_M(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+1)*2, (n+2)*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_N(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m  )*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
		LCD_Fill((n+1)*2, (m+1)*2, (n+1)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+2)*2, (n+2)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+5)*2, (n+3)*2 + 2, (m+5)*2 + 2, color);	
} 
void pitnt_O(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n+1)*2, (m  )*2, (n+3)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n  )*2, (m+2)*2, (n  )*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+2)*2, (n+4)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n  )*2, (m+3)*2, (n  )*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n  )*2, (m+4)*2, (n  )*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+4)*2, (n+4)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n  )*2, (m+5)*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+5)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+6)*2, (n+3)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_P(uint16_t n, uint16_t m,int color){
		LCD_Fill((n+1)*2, (m  )*2, (n+3)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+4)*2, (n+3)*2 + 2, (m+4)*2 + 2, color);	
}
void pitnt_Q(uint16_t n, uint16_t m,int color){
		LCD_Fill((n+1)*2, (m  )*2, (n+3)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+5)*2, (n+3)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_R(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n+1)*2, (m  )*2, (n+3)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+2)*2 + 2, color);	  
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n  )*2, (m+3)*2, (n+3)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n  )*2, (m+4)*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+4)*2, (n+2)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+5)*2, (n+3)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_S(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);	
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+2)*2 + 2, color);	
		LCD_Fill((n  )*2, (m+3)*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+4)*2, (n+4)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
} 
void pitnt_T(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n+2)*2, (m+1)*2, (n+2)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_U(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+4)*2, (m  )*2, (n+4)*2 + 2, (m+5)*2 + 2, color);	
		LCD_Fill((n+1)*2, (m+6)*2, (n+3)*2 + 2, (m+6)*2 + 2, color);		                                                       
}
void pitnt_V(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+4)*2, (m  )*2, (n+4)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+3)*2, (n+1)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+3)*2, (n+3)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+6)*2, (n+2)*2 + 2, (m+6)*2 + 2, color);	
}	
void pitnt_W(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+2)*2, (m  )*2, (n+2)*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m  )*2, (n+4)*2 + 2, (m+6)*2 + 2, color);	
		LCD_Fill((n+1)*2, (m+6)*2, (n+1)*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+6)*2, (n+3)*2 + 2, (m+6)*2 + 2, color);	
}
void pitnt_X(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n  )*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+4)*2, (m  )*2, (n+4)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n  )*2, (m+5)*2, (n  )*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+5)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+2)*2, (n+1)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+4)*2, (n+1)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+3)*2, (n+2)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+2)*2, (n+3)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+4)*2, (n+3)*2 + 2, (m+4)*2 + 2, color);	
}	
void pitnt_Y(uint16_t n, uint16_t m,int color){          
		LCD_Fill((n  )*2, (m)  *2, (n  )*2 + 2, (m)  *2 + 2, color);
		LCD_Fill((n+4)*2, (m)  *2, (n+4)*2 + 2, (m)  *2 + 2, color);	
		LCD_Fill((n  )*2, (m+1)*2, (n  )*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+2)*2, (n+1)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+2)*2, (n+3)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+3)*2, (n+1)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+3)*2, (n+3)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+4)*2, (n+2)*2 + 2, (m+4)*2 + 2, color);	
		LCD_Fill((n+2)*2, (m+5)*2, (n+2)*2 + 2, (m+5)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+6)*2, (n+2)*2 + 2, (m+6)*2 + 2, color);	
}                                                                                                             
void pitnt_Z(uint16_t n, uint16_t m,int color){
		LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m  )*2 + 2, color);
		LCD_Fill((n  )*2, (m+6)*2, (n+4)*2 + 2, (m+6)*2 + 2, color);
		LCD_Fill((n+4)*2, (m+1)*2, (n+4)*2 + 2, (m+1)*2 + 2, color);
		LCD_Fill((n+3)*2, (m+2)*2, (n+3)*2 + 2, (m+2)*2 + 2, color);
		LCD_Fill((n+2)*2, (m+3)*2, (n+2)*2 + 2, (m+3)*2 + 2, color);
		LCD_Fill((n+1)*2, (m+4)*2, (n+1)*2 + 2, (m+4)*2 + 2, color);
		LCD_Fill((n  )*2, (m+5)*2, (n  )*2 + 2, (m+5)*2 + 2, color);	
}	
void pitnt_FULL(uint16_t n, uint16_t m,int color){
LCD_Fill((n  )*2, (m  )*2, (n+4)*2 + 2, (m+6)*2 + 2, color);
}
void pitnt_cnt(int cnt,uint16_t n, uint16_t m,int color1,int color2){
	int cnt1,cnt2,cnt3;
	cnt1=cnt  / 1 % 10;
	cnt2=cnt  / 10 % 10;
	cnt3=cnt  / 100 % 10;
			  switch(cnt1){
			  case 0:{pitnt_FULL(n+20,m,color1);pitnt_0(n+20,m,color2);break;}
				case 1:{pitnt_FULL(n+20,m,color1);pitnt_1(n+20,m,color2);break;}
				case 2:{pitnt_FULL(n+20,m,color1);pitnt_2(n+20,m,color2);break;}
				case 3:{pitnt_FULL(n+20,m,color1);pitnt_3(n+20,m,color2);break;}
				case 4:{pitnt_FULL(n+20,m,color1);pitnt_4(n+20,m,color2);break;}
				case 5:{pitnt_FULL(n+20,m,color1);pitnt_5(n+20,m,color2);break;}
				case 6:{pitnt_FULL(n+20,m,color1);pitnt_6(n+20,m,color2);break;}				
				case 7:{pitnt_FULL(n+20,m,color1);pitnt_7(n+20,m,color2);break;}
				case 8:{pitnt_FULL(n+20,m,color1);pitnt_8(n+20,m,color2);break;}
				case 9:{pitnt_FULL(n+20,m,color1);pitnt_9(n+20,m,color2);break;}
			 default:{pitnt_FULL(n+20,m,color1);pitnt_0(n+20,m,color2);break;}
			}                                           
			  switch(cnt2){                             
			  case 0:{pitnt_FULL(n+10,m,color1);pitnt_0(n+10,m,color2);break;}
				case 1:{pitnt_FULL(n+10,m,color1);pitnt_1(n+10,m,color2);break;}
				case 2:{pitnt_FULL(n+10,m,color1);pitnt_2(n+10,m,color2);break;}
				case 3:{pitnt_FULL(n+10,m,color1);pitnt_3(n+10,m,color2);break;}
				case 4:{pitnt_FULL(n+10,m,color1);pitnt_4(n+10,m,color2);break;}
				case 5:{pitnt_FULL(n+10,m,color1);pitnt_5(n+10,m,color2);break;}
				case 6:{pitnt_FULL(n+10,m,color1);pitnt_6(n+10,m,color2);break;}				
				case 7:{pitnt_FULL(n+10,m,color1);pitnt_7(n+10,m,color2);break;}
				case 8:{pitnt_FULL(n+10,m,color1);pitnt_8(n+10,m,color2);break;}
				case 9:{pitnt_FULL(n+10,m,color1);pitnt_9(n+10,m,color2);break;}
			 default:{pitnt_FULL(n+10,m,color1);pitnt_0(n+10,m,color2);break;}                        
			}	                                          
			  switch(cnt3){                             
			  case 0:{pitnt_FULL(n   ,m,color1);pitnt_0(n,m,color2);break;}
				case 1:{pitnt_FULL(n   ,m,color1);pitnt_1(n,m,color2);break;}
				case 2:{pitnt_FULL(n   ,m,color1);pitnt_2(n,m,color2);break;}
				case 3:{pitnt_FULL(n   ,m,color1);pitnt_3(n,m,color2);break;}
				case 4:{pitnt_FULL(n   ,m,color1);pitnt_4(n,m,color2);break;}
				case 5:{pitnt_FULL(n   ,m,color1);pitnt_5(n,m,color2);break;}
				case 6:{pitnt_FULL(n   ,m,color1);pitnt_6(n,m,color2);break;}				
				case 7:{pitnt_FULL(n   ,m,color1);pitnt_7(n,m,color2);break;}
				case 8:{pitnt_FULL(n   ,m,color1);pitnt_8(n,m,color2);break;}
				case 9:{pitnt_FULL(n   ,m,color1);pitnt_9(n,m,color2);break;}
			 default:{pitnt_FULL(n   ,m,color1);pitnt_0(n,m,color2);break;}
			}				
}
void WIN(int cnt){
	Music_data=16+2;
    LCD_Fill(1, 1, 240, 310, GREEN);
	  delay(500000);
		pitnt_Y(38,65,BLACK);pitnt_Y(38,65,BLACK);
		pitnt_O(45,65,BLACK);pitnt_O(45,65,BLACK);		
		pitnt_U(52,65,BLACK);pitnt_U(52,65,BLACK);
	             
		pitnt_W(64,65,BLACK);pitnt_W(64,65,BLACK);
		pitnt_I(71,65,BLACK);pitnt_I(71,65,BLACK);
		pitnt_N(78,65,BLACK);pitnt_N(78,65,BLACK);
			
		pitnt_Y(19,80,BLACK);pitnt_Y(19,80,BLACK);
		pitnt_O(26,80,BLACK);pitnt_O(26,80,BLACK);			
		pitnt_U(33,80,BLACK);pitnt_U(33,80,BLACK);
		pitnt_R(40,80,BLACK);pitnt_R(40,80,BLACK);			
               
		pitnt_S(52,80,BLACK);pitnt_S(52,80,BLACK);
		pitnt_C(59,80,BLACK);pitnt_C(59,80,BLACK);		
		pitnt_O(66,80,BLACK);pitnt_O(66,80,BLACK);
		pitnt_R(73,80,BLACK);pitnt_R(73,80,BLACK);	
		pitnt_E(80,80,BLACK);pitnt_E(80,80,BLACK);
			
		pitnt_I(92,80,BLACK);pitnt_I(92,80,BLACK);		
		pitnt_S(99,80,BLACK);pitnt_S(99,80,BLACK);


		pitnt_cnt(cnt,50,95,GREEN,BLACK);
		while(!key_flag && !uart_flag){
		pitnt_P(8,125,BLACK);
		pitnt_R(15,125,BLACK);
		pitnt_E(22,125,BLACK);
		pitnt_S(29,125,BLACK);
		pitnt_S(36,125,BLACK);
		
		pitnt_T(48,125,BLACK);
		pitnt_O(55,125,BLACK);
		
		pitnt_R(67,125,BLACK);
		pitnt_E(74,125,BLACK);
		pitnt_S(81,125,BLACK);
		pitnt_T(88,125,BLACK);
		pitnt_A(95,125,BLACK);
		pitnt_R(102,125,BLACK);
		pitnt_T(109,125,BLACK);
		delay(3000000000);
		pitnt_P(8,125,YELLOW);
		pitnt_R(15,125,YELLOW);
		pitnt_E(22,125,YELLOW);
		pitnt_S(29,125,YELLOW);
		pitnt_S(36,125,YELLOW);
		
		pitnt_T(48,125,YELLOW);
		pitnt_O(55,125,YELLOW);
		
		pitnt_R(67,125,YELLOW);
		pitnt_E(74,125,YELLOW);
		pitnt_S(81,125,YELLOW);
		pitnt_T(88,125,YELLOW);
		pitnt_A(95,125,YELLOW);
		pitnt_R(102,125,YELLOW);
		pitnt_T(109,125,YELLOW);
		delay(3000000000);		
		}
		
   }
void LOSE(int cnt){
	Music_data=16+3;
	  LCD_Fill(1, 1, 240, 310, RED);
	  delay(500000);
		pitnt_Y(35,65,BLACK);pitnt_Y(35,65,BLACK);
		pitnt_O(42,65,BLACK);pitnt_O(42,65,BLACK);		
		pitnt_U(49,65,BLACK);pitnt_U(49,65,BLACK);
			                    	
		pitnt_L(61,65,BLACK);pitnt_L(61,65,BLACK);
		pitnt_O(68,65,BLACK);pitnt_O(68,65,BLACK);
		pitnt_S(75,65,BLACK);pitnt_S(75,65,BLACK); 
		pitnt_E(82,65,BLACK);pitnt_E(82,65,BLACK);
		                     
		pitnt_Y(19,80,BLACK);pitnt_Y(19,80,BLACK);
		pitnt_O(26,80,BLACK);pitnt_O(26,80,BLACK);		
		pitnt_U(33,80,BLACK);pitnt_U(33,80,BLACK);
		pitnt_R(40,80,BLACK);pitnt_R(40,80,BLACK);			
                       
		pitnt_S(52,80,BLACK);pitnt_S(52,80,BLACK);
		pitnt_C(59,80,BLACK);pitnt_C(59,80,BLACK);		
		pitnt_O(66,80,BLACK);pitnt_O(66,80,BLACK);
		pitnt_R(73,80,BLACK);pitnt_R(73,80,BLACK);	
		pitnt_E(80,80,BLACK);pitnt_E(80,80,BLACK);
			                    	
		pitnt_I(92,80,BLACK);pitnt_I(92,80,BLACK);	
		pitnt_S(99,80,BLACK);pitnt_S(99,80,BLACK);
		
		pitnt_cnt(cnt,50,95,RED,BLACK);
		while(!key_flag && !uart_flag){
		pitnt_P(8,125,BLACK);
		pitnt_R(15,125,BLACK);
		pitnt_E(22,125,BLACK);
		pitnt_S(29,125,BLACK);
		pitnt_S(36,125,BLACK);
		
		pitnt_T(48,125,BLACK);
		pitnt_O(55,125,BLACK);
		
		pitnt_R(67,125,BLACK);
		pitnt_E(74,125,BLACK);
		pitnt_S(81,125,BLACK);
		pitnt_T(88,125,BLACK);
		pitnt_A(95,125,BLACK);
		pitnt_R(102,125,BLACK);
		pitnt_T(109,125,BLACK);
		delay(3000000000);
		pitnt_P(8,125,YELLOW);
		pitnt_R(15,125,YELLOW);
		pitnt_E(22,125,YELLOW);
		pitnt_S(29,125,YELLOW);
		pitnt_S(36,125,YELLOW);
		
		pitnt_T(48,125,YELLOW);
		pitnt_O(55,125,YELLOW);
		
		pitnt_R(67,125,YELLOW);
		pitnt_E(74,125,YELLOW);
		pitnt_S(81,125,YELLOW);
		pitnt_T(88,125,YELLOW);
		pitnt_A(95,125,YELLOW);
		pitnt_R(102,125,YELLOW);
		pitnt_T(109,125,YELLOW);
		delay(3000000000);		
		}
}
void MAP(){
		int m=0,n=0;
			LCD_Fill(0, 0, 240, 320, BLACK);
			for(m=0;m<=31;m++){
				for(n=0;n<=23;n++)
			{
				if(a[m][n]==0){LCD_Fill(n*10, m*10, n*10 + 10, m*10 + 10, BLACK);}
				if(a[m][n]==1||a[m][n]==3){LCD_Fill(n*10, m*10, n*10 + 10, m*10 + 10, WHITE);food(n,m);}
				if(a[m][n]==2){LCD_Fill(n*10, m*10, n*10 + 10, m*10 + 10, GBLUE);}
			}
  }
}
void clear(uint16_t x, uint16_t y){
	LCD_Fill(x, y, x + 9, y + 9, WHITE);
}
void pac_man_left1(uint16_t x, uint16_t y,uint8_t size){
	LCD_Fill(x*size+2*(size/10),y*size+0*(size/10),x*size+7*(size/10),y*size+1*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+1*(size/10),x*size+8*(size/10),y*size+2*(size/10),GRED);
	LCD_Fill(x*size+1*(size/10),y*size+2*(size/10),x*size+9*(size/10),y*size+3*(size/10),GRED);
	LCD_Fill(x*size+3*(size/10),y*size+3*(size/10),x*size+9*(size/10),y*size+4*(size/10),GRED);
	LCD_Fill(x*size+5*(size/10),y*size+4*(size/10),x*size+9*(size/10),y*size+5*(size/10),GRED);
	LCD_Fill(x*size+3*(size/10),y*size+5*(size/10),x*size+9*(size/10),y*size+6*(size/10),GRED);
	LCD_Fill(x*size+1*(size/10),y*size+6*(size/10),x*size+9*(size/10),y*size+7*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+7*(size/10),x*size+8*(size/10),y*size+8*(size/10),GRED);
	LCD_Fill(x*size+2*(size/10),y*size+8*(size/10),x*size+7*(size/10),y*size+9*(size/10),GRED);
}
void pac_man_right1(uint16_t x, uint16_t y,uint8_t size){
	LCD_Fill(x*size+2*(size/10),y*size+0*(size/10),x*size+7*(size/10),y*size+1*(size/10),GRED);
	LCD_Fill(x*size+1*(size/10),y*size+1*(size/10),x*size+9*(size/10),y*size+2*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+2*(size/10),x*size+8*(size/10),y*size+3*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+3*(size/10),x*size+6*(size/10),y*size+4*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+4*(size/10),x*size+4*(size/10),y*size+5*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+5*(size/10),x*size+6*(size/10),y*size+6*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+6*(size/10),x*size+8*(size/10),y*size+7*(size/10),GRED);
	LCD_Fill(x*size+1*(size/10),y*size+7*(size/10),x*size+9*(size/10),y*size+8*(size/10),GRED);
	LCD_Fill(x*size+2*(size/10),y*size+8*(size/10),x*size+7*(size/10),y*size+9*(size/10),GRED);
}
void pac_man_up1(uint16_t x, uint16_t y,uint8_t size){
	LCD_Fill(x*size+1*(size/10),y*size+0*(size/10),x*size+2*(size/10),y*size+1*(size/10),GRED);
	LCD_Fill(x*size+7*(size/10),y*size+0*(size/10),x*size+8*(size/10),y*size+1*(size/10),GRED);

	LCD_Fill(x*size+1*(size/10),y*size+1*(size/10),x*size+3*(size/10),y*size+2*(size/10),GRED);
	LCD_Fill(x*size+6*(size/10),y*size+1*(size/10),x*size+8*(size/10),y*size+2*(size/10),GRED);

	LCD_Fill(x*size+0*(size/10),y*size+2*(size/10),x*size+3*(size/10),y*size+3*(size/10),GRED);
	LCD_Fill(x*size+6*(size/10),y*size+2*(size/10),x*size+9*(size/10),y*size+3*(size/10),GRED);

	LCD_Fill(x*size+0*(size/10),y*size+3*(size/10),x*size+4*(size/10),y*size+3*(size/10),GRED);
	LCD_Fill(x*size+5*(size/10),y*size+3*(size/10),x*size+9*(size/10),y*size+3*(size/10),GRED);

	LCD_Fill(x*size+0*(size/10),y*size+4*(size/10),x*size+4*(size/10),y*size+5*(size/10),GRED);
	LCD_Fill(x*size+5*(size/10),y*size+4*(size/10),x*size+9*(size/10),y*size+5*(size/10),GRED);

	LCD_Fill(x*size+0*(size/10),y*size+5*(size/10),x*size+9*(size/10),y*size+6*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+6*(size/10),x*size+9*(size/10),y*size+7*(size/10),GRED);
	LCD_Fill(x*size+1*(size/10),y*size+7*(size/10),x*size+8*(size/10),y*size+8*(size/10),GRED);
	LCD_Fill(x*size+2*(size/10),y*size+8*(size/10),x*size+7*(size/10),y*size+9*(size/10),GRED);
} 
void pac_man_down1(uint16_t x, uint16_t y,uint8_t size){
	LCD_Fill(x*size+2*(size/10),y*size+0*(size/10),x*size+7*(size/10),y*size+1*(size/10),GRED);
	LCD_Fill(x*size+1*(size/10),y*size+1*(size/10),x*size+8*(size/10),y*size+2*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+2*(size/10),x*size+9*(size/10),y*size+3*(size/10),GRED);
	LCD_Fill(x*size+0*(size/10),y*size+3*(size/10),x*size+9*(size/10),y*size+4*(size/10),GRED);

	LCD_Fill(x*size+0*(size/10),y*size+4*(size/10),x*size+4*(size/10),y*size+5*(size/10),GRED);
	LCD_Fill(x*size+5*(size/10),y*size+4*(size/10),x*size+9*(size/10),y*size+5*(size/10),GRED);
																																											 
	LCD_Fill(x*size+0*(size/10),y*size+5*(size/10),x*size+4*(size/10),y*size+6*(size/10),GRED);
	LCD_Fill(x*size+5*(size/10),y*size+5*(size/10),x*size+9*(size/10),y*size+6*(size/10),GRED);

	LCD_Fill(x*size+0*(size/10),y*size+6*(size/10),x*size+3*(size/10),y*size+7*(size/10),GRED);
	LCD_Fill(x*size+6*(size/10),y*size+6*(size/10),x*size+9*(size/10),y*size+7*(size/10),GRED);

	LCD_Fill(x*size+1*(size/10),y*size+7*(size/10),x*size+3*(size/10),y*size+8*(size/10),GRED);
	LCD_Fill(x*size+6*(size/10),y*size+7*(size/10),x*size+8*(size/10),y*size+8*(size/10),GRED);

	LCD_Fill(x*size+1*(size/10),y*size+8*(size/10),x*size+2*(size/10),y*size+9*(size/10),GRED);
	LCD_Fill(x*size+7*(size/10),y*size+8*(size/10),x*size+8*(size/10),y*size+9*(size/10),GRED);
}
void ghost(uint16_t x, uint16_t y,uint8_t size,int color){
	LCD_Fill(x*size+2*(size/10),y*size+2*(size/10),x*size+8*(size/10),y*size+8*(size/10),color);
//	LCD_Fill(x*size+3*(size/10),y*size+0*(size/10),x*size+6*(size/10),y*size+1*(size/10),color);
//	LCD_Fill(x*size+2*(size/10),y*size+1*(size/10),x*size+7*(size/10),y*size+2*(size/10),color);
//	LCD_Fill(x*size+1*(size/10),y*size+2*(size/10),x*size+8*(size/10),y*size+3*(size/10),color);

//	LCD_Fill(x*size+1*(size/10),y*size+3*(size/10),x*size+2*(size/10),y*size+4*(size/10),color);
//	LCD_Fill(x*size+2*(size/10),y*size+3*(size/10),x*size+4*(size/10),y*size+4*(size/10),WHITE);
//	LCD_Fill(x*size+4*(size/10),y*size+3*(size/10),x*size+5*(size/10),y*size+4*(size/10),color);
//	LCD_Fill(x*size+5*(size/10),y*size+3*(size/10),x*size+7*(size/10),y*size+4*(size/10),WHITE);
//	LCD_Fill(x*size+7*(size/10),y*size+3*(size/10),x*size+8*(size/10),y*size+4*(size/10),color);

//	LCD_Fill(x*size+0*(size/10),y*size+4*(size/10),x*size+2*(size/10),y*size+5*(size/10),color);
//	LCD_Fill(x*size+2*(size/10),y*size+4*(size/10),x*size+3*(size/10),y*size+5*(size/10),WHITE);
//	LCD_Fill(x*size+3*(size/10),y*size+4*(size/10),x*size+4*(size/10),y*size+5*(size/10),BLACK);
//	LCD_Fill(x*size+4*(size/10),y*size+4*(size/10),x*size+5*(size/10),y*size+5*(size/10),color);
//	LCD_Fill(x*size+5*(size/10),y*size+4*(size/10),x*size+6*(size/10),y*size+5*(size/10),WHITE);
//	LCD_Fill(x*size+6*(size/10),y*size+4*(size/10),x*size+7*(size/10),y*size+5*(size/10),BLACK);
//	LCD_Fill(x*size+7*(size/10),y*size+4*(size/10),x*size+9*(size/10),y*size+5*(size/10),color);

//	LCD_Fill(x*size+0*(size/10),y*size+5*(size/10),x*size+2*(size/10),y*size+6*(size/10),color);
//	LCD_Fill(x*size+2*(size/10),y*size+5*(size/10),x*size+3*(size/10),y*size+6*(size/10),WHITE);
//	LCD_Fill(x*size+3*(size/10),y*size+5*(size/10),x*size+4*(size/10),y*size+6*(size/10),BLACK);
//	LCD_Fill(x*size+4*(size/10),y*size+5*(size/10),x*size+5*(size/10),y*size+6*(size/10),color);
//	LCD_Fill(x*size+5*(size/10),y*size+5*(size/10),x*size+6*(size/10),y*size+6*(size/10),WHITE);
//	LCD_Fill(x*size+6*(size/10),y*size+5*(size/10),x*size+7*(size/10),y*size+6*(size/10),BLACK);
//	LCD_Fill(x*size+7*(size/10),y*size+5*(size/10),x*size+9*(size/10),y*size+6*(size/10),color);

//  LCD_Fill(x*size+0*(size/10),y*size+6*(size/10),x*size+9*(size/10),y*size+7*(size/10),color);
//	LCD_Fill(x*size+0*(size/10),y*size+7*(size/10),x*size+9*(size/10),y*size+8*(size/10),color);

//  LCD_Fill(x*size+0*(size/10),y*size+8*(size/10),x*size+0*(size/10),y*size+9*(size/10),color);
//	LCD_Fill(x*size+2*(size/10),y*size+8*(size/10),x*size+2*(size/10),y*size+9*(size/10),color);
//	LCD_Fill(x*size+4*(size/10),y*size+8*(size/10),x*size+4*(size/10),y*size+9*(size/10),color);
//	LCD_Fill(x*size+6*(size/10),y*size+8*(size/10),x*size+6*(size/10),y*size+9*(size/10),color);
//	LCD_Fill(x*size+8*(size/10),y*size+8*(size/10),x*size+8*(size/10),y*size+9*(size/10),color);
}
void gameover(){
	LCD_Fill(0, 0, 240, 320, RED);
	while(!key_flag);
	Keyboard_keydata_clear = 1;
}
void MOVE(){
	Music_data=16+1;
	int xx =4,yy =5,xx1 =19,yy1 =5,xx2 =19,yy2 =27,xx3 =4,yy3 =27;
  int dxx=4,dyy=5,dxx1=19,dyy1=5,dxx2=19,dyy2=27,dxx3=4,dyy3=27;
	int col=4,row=5,col1=19,row1=5,col2=19,row2=27,col3=4,row3=27;
//	int vector=0,vector1=1,vector2=1,vector3=4;
	int vector1=1,vector2=1,vector3=4;
	int v     =0,v1     =1,v2     =1,v3     =4;
	int end=0;

	int cnt_tmp[768]={0};	
	int b[768]={0};
	int cnt=0;
	int w1,w2,w3;
	
	pitnt_cnt(cnt,47,79,GBLUE,BRRED);
	clear(xx*10,yy*10);
	pac_man_right1(dxx,dyy,10);	
	clear(xx1*10,yy1*10);
	ghost(dxx1,dyy1,10,RED);
	clear(xx2*10,yy2*10);
	ghost(dxx2,dyy2,10,GREEN);
	clear(xx3*10,yy3*10);
	ghost(dxx3,dyy3,10,MAGENTA);
	
	
while (1) {	
    if(key_flag){
		key_flag = 0;		
		uint32_t din;
		din = Keyboard_keydata_clear;

		    int i = 0;
		    int ans = 0;
		    for (i = 0; i < 16; i++) {
			    if ((din >> i) & 1) {
			    	ans = i;
				    break;
	     	   }
		    }
		Keyboard_keydata_clear = 1;		
		if(ans ==6){vector=1;}//left	
		else if(ans ==5){vector=2;}//down
		else if(ans ==9){vector=3;}//up
		else if(ans ==4){vector=4;}//right	
		else {vector=0;}
	}

   	if(uart_flag)
		{uart_flag = 0;}
		
		//delay(1000);
	
switch(vector){
			case(1):{
		if(a[row][col-1]==1||a[row][col-1]==3){
    b[row*32+col]=1;
		if(!cnt_tmp[row*32+(col-1)]){cnt_tmp[row*32+(col-1)]=1;cnt=cnt+1;pitnt_cnt(cnt,47,79,GBLUE,BRRED);}
    dxx=xx - 1;
    col=col-1;
		
    if(row==16 && col==0){
    	clear(0*10,16*10);
			clear(1*10,16*10);
    	col=23;xx=23;dxx=23;}
		
    clear(xx*10,yy*10);
    pac_man_left1(dxx,dyy,10);
	}
		else{vector=v;break;}
break;}
			
			case(2):{
			if(a[row+1][col]==1||a[row+1][col]==3){
			b[row*32+col]=1;
			if(!cnt_tmp[(row+1)*32+col]){cnt_tmp[(row+1)*32+col]=1;cnt=cnt+1;pitnt_cnt(cnt,47,79,GBLUE,BRRED);}
			dyy = yy + 1;
			row=row+1;
			clear(xx*10,yy*10);
			pac_man_down1(dxx,dyy,10);
	}
		else{vector=v;break;}
	break;}
			
			case(3):{
			if(a[row-1][col]==1||a[row-1][col]==3){
    b[row*32+col]=1;
					if(!cnt_tmp[(row-1)*32+col]){cnt_tmp[(row-1)*32+col]=1;cnt=cnt+1;pitnt_cnt(cnt,47,79,GBLUE,BRRED);}
    dyy = yy - 1;
    row=row-1;
    clear(xx*10,yy*10);
    pac_man_up1(dxx,dyy,10);	
	}
	else{vector=v;break;}
break;}
			
			case(4):{
				 if(a[row][col+1]==1||a[row][col+1]==3){
    b[row*32+col]=1;		
					if(!cnt_tmp[row*32+(col+1)]){cnt_tmp[row*32+(col+1)]=1;cnt=cnt+1;pitnt_cnt(cnt,47,79,GBLUE,BRRED);}							
    dxx = xx + 1; 
    col=col+1;
						
    if(row==16 && col==23){
    clear(23*10,16*10);
		clear(22*10,16*10);
    col=0;xx=0;dxx=0;}
		
    clear(xx*10,yy*10);
    pac_man_right1(dxx,dyy,10);
	}
	else{vector=v;break;}
	break;}
	default:{vector=v;break;}
}
w1=rand()%4+1;
w2=rand()%4+1;
w3=rand()%4+1;

///////////////////////////////AI1
switch(vector1){
	case(1):{
		if(a[row1][col1-1]==1){
		dxx1=xx1 - 1;
		if(b[row1*32+(col1-1)]==1){clear(xx1*10,yy1*10);}
		else if(b[row1*32+(col1-1)]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        col1=col1-1;
        //if(row1==16 && col1==0){clear(0*10,16*10);col1=23;xx1=23;dxx1=23;}	
        ghost(dxx1,dyy1,10,RED);
		//delay(100000000);
	}
	else if(a[row1][col1-1]==3){
		dxx1=xx1 - 1;
		if(b[row1*32+(col1-1)]==1){clear(xx1*10,yy1*10);}
		else if(b[row1*32+(col1-1)]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        col1=col1-1;	
        ghost(dxx1,dyy1,10,RED);
		vector1=w1;}
	else{vector1=w1;}
	break;}

	case(2):{
		if(a[row1+1][col1]==1){
		dyy1=yy1 + 1;
		if(b[(row1+1)*32+col1]==1){clear(xx1*10,yy1*10);}
		else if(b[(row1+1)*32+col1]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        row1=row1+1;	
        ghost(dxx1,dyy1,10,RED);
		//delay(100000000);
	}
	else if(a[row1+1][col1]==3){
		dyy1=yy1 + 1;
		if(b[(row1+1)*32+col1]==1){clear(xx1*10,yy1*10);}
		else if(b[(row1+1)*32+col1]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        row1=row1+1;	
        ghost(dxx1,dyy1,10,RED);
		vector1=w1;
	}
	else{vector1=w1;}
	break;}

	case(3):{
		if(a[row1-1][col1]==1){
		dyy1=yy1 - 1;
		if(b[(row1-1)*32+col1]==1){clear(xx1*10,yy1*10);}
		else if(b[(row1-1)*32+col1]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        row1=row1-1;	
        ghost(dxx1,dyy1,10,RED);
		//delay(100000000);
	}
	else if(a[row1-1][col1]==3){
		dyy1=yy1 - 1;
		if(b[(row1-1)*32+col1]==1){clear(xx1*10,yy1*10);}
		else if(b[(row1-1)*32+col1]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        row1=row1-1;	
        ghost(dxx1,dyy1,10,RED);
		vector1=w1;
	}
	else{vector1=w1;}
	break;}

	case(4):{
		if(a[row1][col1+1]==1){
		dxx1=xx1 + 1;
		if(b[row1*32+(col1+1)]==1){clear(xx1*10,yy1*10);}
		else if(b[row1*32+(col1+1)]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        col1=col1+1;
        //if(row1==16 && col1==23){clear(23*10,16*10);col1=0;xx1=0;dxx1=0;}	
        ghost(dxx1,dyy1,10,RED);
		//delay(100000000);
	}
	else if (a[row1][col1+1]==3){
		dxx1=xx1 + 1;
		if(b[row1*32+(col1+1)]==1){clear(xx1*10,yy1*10);}
		else if(b[row1*32+(col1+1)]==0){clear(xx1*10,yy1*10);food(xx1,yy1);}
        col1=col1+1;
        ghost(dxx1,dyy1,10,RED);
		vector1=w1;
	}
	else{vector1=w1;}
	break;}
}
if((row==row1 && col==col1) || (row==row2 && col==col2) || (row==row3 && col==col3)){end=2;}
if(cnt>=250){end=1;}

///////////////////////////////AI2
switch(vector2){
	case(1):{
		if(a[row2][col2-1]==1){
		dxx2=xx2 - 1;
		if(b[row2*32+(col2-1)]==1){clear(xx2*10,yy2*10);}
		else if(b[row2*32+(col2-1)]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        col2=col2-1;
        //if(row2==16 && col2==0){clear(0*10,16*10);col2=23;xx2=23;dxx2=23;}	
        ghost(dxx2,dyy2,10,GREEN);
		//delay(100000000);
	}
	else if(a[row2][col2-1]==3){
		dxx2=xx2 - 1;
		if(b[row2*32+(col2-1)]==1){clear(xx2*10,yy2*10);}
		else if(b[row2*32+(col2-1)]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        col2=col2-1;	
        ghost(dxx2,dyy2,10,GREEN);
		vector2=w2;}
	else{vector2=w2;}
	break;}

	case(2):{
		if(a[row2+1][col2]==1){
		dyy2=yy2 + 1;
		if(b[(row2+1)*32+col2]==1){clear(xx2*10,yy2*10);}
		else if(b[(row2+1)*32+col2]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        row2=row2+1;	
        ghost(dxx2,dyy2,10,GREEN);
		//delay(100000000);
	}
	else if(a[row2+1][col2]==3){
		dyy2=yy2 + 1;
		if(b[(row2+1)*32+col2]==1){clear(xx2*10,yy2*10);}
		else if(b[(row2+1)*32+col2]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        row2=row2+1;	
        ghost(dxx2,dyy2,10,GREEN);
		vector2=w2;
	}
	else{vector2=w2;}
	break;}

	case(3):{
		if(a[row2-1][col2]==1){
		dyy2=yy2 - 1;
		if(b[(row2-1)*32+col2]==1){clear(xx2*10,yy2*10);}
		else if(b[(row2-1)*32+col2]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        row2=row2-1;	
        ghost(dxx2,dyy2,10,GREEN);
		//delay(100000000);
	}
	else if(a[row2-1][col2]==3){
		dyy2=yy2 - 1;
		if(b[(row2-1)*32+col2]==1){clear(xx2*10,yy2*10);}
		else if(b[(row2-1)*32+col2]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        row2=row2-1;	
        ghost(dxx2,dyy2,10,GREEN);
		vector2=w2;
	}
	else{vector2=w2;}
	break;}

	case(4):{
		if(a[row2][col2+1]==1){
		dxx2=xx2 + 1;
		if(b[row2*32+(col2+1)]==1){clear(xx2*10,yy2*10);}
		else if(b[row2*32+(col2+1)]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        col2=col2+1;
        //if(row2==16 && col2==23){clear(23*10,16*10);col2=0;xx2=0;dxx2=0;}	
        ghost(dxx2,dyy2,10,GREEN);
		//delay(100000000);
	}
	else if (a[row2][col2+1]==3){
		dxx2=xx2 + 1;
		if(b[row2*32+(col2+1)]==1){clear(xx2*10,yy2*10);}
		else if(b[row2*32+(col2+1)]==0){clear(xx2*10,yy2*10);food(xx2,yy2);}
        col2=col2+1;
        ghost(dxx2,dyy2,10,GREEN);
		vector2=w2;
	}
	else{vector2=w2;}
	break;}
}
if((row==row1 && col==col1) || (row==row2 && col==col2) || (row==row3 && col==col3)){end=2;}
if(cnt>=250){end=1;}


///////////////////////////////AI3
switch(vector3){
	case(1):{
		if(a[row3][col3-1]==1){
		dxx3=xx3 - 1;
		if(b[row3*32+(col3-1)]==1){clear(xx3*10,yy3*10);}
		else if(b[row3*32+(col3-1)]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        col3=col3-1;
        //if(row3==16 && col3==0){clear(0*10,16*10);col3=23;xx3=23;dxx3=23;}	
        ghost(dxx3,dyy3,10,MAGENTA);
		//delay(100000000);
	}
	else if(a[row3][col3-1]==3){
		dxx3=xx3 - 1;
		if(b[row3*32+(col3-1)]==1){clear(xx3*10,yy3*10);}
		else if(b[row3*32+(col3-1)]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        col3=col3-1;	
        ghost(dxx3,dyy3,10,MAGENTA);
		vector3=w3;}
	else{vector3=w3;}
	break;}

	case(2):{
		if(a[row3+1][col3]==1){
		dyy3=yy3 + 1;
		if(b[(row3+1)*32+col3]==1){clear(xx3*10,yy3*10);}
		else if(b[(row3+1)*32+col3]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        row3=row3+1;	
        ghost(dxx3,dyy3,10,MAGENTA);
		//delay(100000000);
	}
	else if(a[row3+1][col3]==3){
		dyy3=yy3 + 1;
		if(b[(row3+1)*32+col3]==1){clear(xx3*10,yy3*10);}
		else if(b[(row3+1)*32+col3]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        row3=row3+1;	
        ghost(dxx3,dyy3,10,MAGENTA);
		vector3=w3;
	}
	else{vector3=w3;}
	break;}

	case(3):{
		if(a[row3-1][col3]==1){
		dyy3=yy3 - 1;
		if(b[(row3-1)*32+col3]==1){clear(xx3*10,yy3*10);}
		else if(b[(row3-1)*32+col3]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        row3=row3-1;	
        ghost(dxx3,dyy3,10,MAGENTA);
		//delay(100000000);
	}
	else if(a[row3-1][col3]==3){
		dyy3=yy3 - 1;
		if(b[(row3-1)*32+col3]==1){clear(xx3*10,yy3*10);}
		else if(b[(row3-1)*32+col3]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        row3=row3-1;	
        ghost(dxx3,dyy3,10,MAGENTA);
		vector3=w3;
	}
	else{vector3=w3;}
	break;}

	case(4):{
		if(a[row3][col3+1]==1){
		dxx3=xx3 + 1;
		if(b[row3*32+(col3+1)]==1){clear(xx3*10,yy3*10);}
		else if(b[row3*32+(col3+1)]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        col3=col3+1;
        //if(row3==16 && col3==23){clear(23*10,16*10);col3=0;xx3=0;dxx3=0;}	
        ghost(dxx3,dyy3,10,MAGENTA);
		//delay(100000000);
	}
	else if (a[row3][col3+1]==3){
		dxx3=xx3 + 1;
		if(b[row3*32+(col3+1)]==1){clear(xx3*10,yy3*10);}
		else if(b[row3*32+(col3+1)]==0){clear(xx3*10,yy3*10);food(xx3,yy3);}
        col3=col3+1;
        ghost(dxx3,dyy3,10,MAGENTA);
		vector3=w3;
	}
	else{vector3=w3;}
	break;}
}
if((row==row1 && col==col1) || (row==row2 && col==col2) || (row==row3 && col==col3)){end=2;}
if(cnt>=50){end=1;}


if(end==2){LOSE(cnt);break;}	
else if (end==1){WIN(cnt);break;}	

//delay(5000);
xx = dxx;
yy = dyy;
xx1=dxx1;
yy1=dyy1;
xx2=dxx2;
yy2=dyy2;
xx3=dxx3;
yy3=dyy3;
v  = vector;
	}
}	
void gamebegin(){
	while(1){
		Music_data=16;
	    LCD_Fill(0,0,240,320,BLACK);

    LCD_Fill(  5,50, 10,110,BRED);                LCD_Fill(  5,50, 10,110,BRED);
	  LCD_Fill( 10,50, 25,55,BRED);           	    LCD_Fill( 10,50, 25,55,BRED);
		LCD_Fill( 25,55, 30,60,BRED);              		LCD_Fill( 25,55, 30,60,BRED);
		LCD_Fill( 30,60, 35,65,BRED);              		LCD_Fill( 30,60, 35,65,BRED);
		LCD_Fill( 35,65, 40,80,BRED);              		LCD_Fill( 35,65, 40,80,BRED);
		LCD_Fill( 10,80, 35,85,BRED);           		  LCD_Fill( 10,80, 35,85,BRED);//P
		LCD_Fill( 40,90, 45,110,BRED);             		LCD_Fill( 40,90, 45,110,BRED);
		LCD_Fill( 45,75, 50,90,BRED);              		LCD_Fill( 45,75, 50,90,BRED);
		LCD_Fill( 50,60, 55,75,BRED);              		LCD_Fill( 50,60, 55,75,BRED);
		LCD_Fill( 55,50, 60,60,BRED);              		LCD_Fill( 55,50, 60,60,BRED);
		LCD_Fill( 60,60,65,75,BRED);               		LCD_Fill( 60,60,65,75,BRED);
		LCD_Fill(65,75,70,90,BRED);                		LCD_Fill(65,75,70,90,BRED);
		LCD_Fill(70,90,75,110,BRED);               		LCD_Fill(70,90,75,110,BRED);
		LCD_Fill( 50,85,65,90,BRED);            		  LCD_Fill( 50,85,65,90,BRED);//A
		LCD_Fill( 80,60 ,85,100,BRED);             		LCD_Fill( 80,60 ,85,100,BRED);
		LCD_Fill(85,55 ,90,60,BRED);               		LCD_Fill(85,55 ,90,60,BRED);
		LCD_Fill(90,50 ,110,55,BRED);              		LCD_Fill(90,50 ,110,55,BRED);
		LCD_Fill(110,55 ,115,60,BRED);             		LCD_Fill(110,55 ,115,60,BRED);
		LCD_Fill(85,100,90,105,BRED);              		LCD_Fill(85,100,90,105,BRED);
		LCD_Fill(90,105,110,110,BRED);             		LCD_Fill(90,105,110,110,BRED);
		LCD_Fill(110,100,115,105,BRED);         		  LCD_Fill(110,100,115,105,BRED);//
		LCD_Fill(120,65,125,110,BRED);             		LCD_Fill(120,65,125,110,BRED);
		LCD_Fill(125,55,130,65,BRED);              		LCD_Fill(125,55,130,65,BRED);
		LCD_Fill(130,50,135,55,BRED);              		LCD_Fill(130,50,135,55,BRED);
		LCD_Fill(135,55,140,110,BRED);             		LCD_Fill(135,55,140,110,BRED);
		LCD_Fill(140,50,145,55,BRED);              		LCD_Fill(140,50,145,55,BRED);
		LCD_Fill(145,55,150,65,BRED);              		LCD_Fill(145,55,150,65,BRED);
		LCD_Fill(150,65,155,110,BRED);          		  LCD_Fill(150,65,155,110,BRED);//M
		LCD_Fill(160,90, 165,110,BRED);            		LCD_Fill(160,90, 165,110,BRED);
		LCD_Fill(165,75, 170,90,BRED);             		LCD_Fill(165,75, 170,90,BRED);
		LCD_Fill( 170,60, 175,75,BRED);            		LCD_Fill( 170,60, 175,75,BRED);
		LCD_Fill(175,50, 180,60,BRED);             		LCD_Fill(175,50, 180,60,BRED);
		LCD_Fill(180,60,185,75,BRED);              		LCD_Fill(180,60,185,75,BRED);
		LCD_Fill(185,75,190,90,BRED);              		LCD_Fill(185,75,190,90,BRED);
		LCD_Fill(190,90,195,110,BRED);             		LCD_Fill(190,90,195,110,BRED);
		LCD_Fill(170,85,185,90,BRED);           		  LCD_Fill(170,85,185,90,BRED);//A
		LCD_Fill(200,55,205,110,BRED);             		LCD_Fill(200,55,205,110,BRED);
		LCD_Fill(205,50,210,55,BRED);              		LCD_Fill(205,50,210,55,BRED);
		LCD_Fill(210,55,215,70,BRED);              		LCD_Fill(210,55,215,70,BRED);
		LCD_Fill(215,70,220,90,BRED);              		LCD_Fill(215,70,220,90,BRED);
		LCD_Fill(220,90,225,105,BRED);             		LCD_Fill(220,90,225,105,BRED);
		LCD_Fill(225,105,230,110,BRED);            		LCD_Fill(225,105,230,110,BRED);
		LCD_Fill(230,50,235,110,BRED);          		  LCD_Fill(230,50,235,110,BRED);//N
		
	  pac_man_right1(1,4,40);
	  LCD_Fill(90 ,175,95 ,180,WHITE);
	  LCD_Fill(120,175,125,180,WHITE);
	  LCD_Fill(150,175,155,180,WHITE);
	  LCD_Fill(180,175,185,180,WHITE);
	  LCD_Fill(210,175,215,180,WHITE);


//		//////////////////////
//		pitnt_G(15,130,BRRED);
//		pitnt_A(22,130,BRRED);
//		pitnt_M(29,130,BRRED);
//		pitnt_E(36,130,BRRED);
//		
//		pitnt_M(48,130,BRRED);
//		pitnt_A(55,130,BRRED);
//		pitnt_D(62,130,BRRED);
//		pitnt_E(69,130,BRRED);
//		
//		pitnt_B(81,130,BRRED);
//		pitnt_Y(88,130,BRRED);
//		//////////////////////
//		pitnt_W(15,150,BRRED);
//		pitnt_R(22,150,BRRED);
//		pitnt_T(29,150,BRRED);
//		
//		pitnt_A(41,150,BRRED);
//		pitnt_N(48,150,BRRED);
//		pitnt_D(55,150,BRRED);
//		
//		pitnt_L(67,150,BRRED);
//		pitnt_Y(74,150,BRRED);
//		pitnt_X(81,150,BRRED);

		
	  while(!key_flag && !uart_flag){
		pitnt_P(15,110,RED);
		pitnt_R(22,110,RED);
		pitnt_E(29,110,RED);
		pitnt_S(36,110,RED);
		pitnt_S(43,110,RED);
		
		pitnt_T(55,110,RED);
		pitnt_O(62,110,RED);
		
		pitnt_S(74,110,RED);
		pitnt_T(81,110,RED);		
		pitnt_A(88,110,RED);
		pitnt_R(95,110,RED);
		pitnt_T(102,110,RED);
		delay(3000000000);
		pitnt_P(15,110,GREEN);
		pitnt_R(22,110,GREEN);
		pitnt_E(29,110,GREEN);
		pitnt_S(36,110,GREEN);
		pitnt_S(43,110,GREEN);
		               
		pitnt_T(55,110,GREEN);
		pitnt_O(62,110,GREEN);
		               
		pitnt_S(74,110,GREEN);
		pitnt_T(81,110,GREEN);		
		pitnt_A(88,110,GREEN);
		pitnt_R(95,110,GREEN);
		pitnt_T(102,110,GREEN);
		delay(3000000000);		
		}
			
	  Keyboard_keydata_clear = 1;
	  MAP();
	  MOVE();
	  while(!key_flag && !uart_flag);
		key_flag=0;
		uart_flag=0;
	  Keyboard_keydata_clear = 1;
		}
}


void uart_put(){
	
	UART_Init();	  	
		while(1){
			
			while(!key_flag);	
			uint32_t din;
			din = Keyboard_keydata_clear;

		    int i = 0;
		    int ans = 0;
         for (i = 0; i < 16; i++) 
            {
	            if ((din >> i) & 1)
                {
	        	    ans = i;
	                break;
	            }
	        }
					
          if(ans == 4) {UART_putc('d');LCD_Fill(200, 200, 220, 220, YELLOW);}
          else if(ans == 5) {UART_putc('s');LCD_Fill(200, 200, 220, 220, BROWN);}
          else if(ans == 6) {UART_putc('a');LCD_Fill(200, 200, 220, 220, GREEN);}
          else if(ans == 9) {UART_putc('w');LCD_Fill(200, 200, 220, 220, BLUE);}
					
		      key_flag = 0;						
					Keyboard_keydata_clear = 1;
     
	}
}

void uart_get(){
	
  uint8_t dx, dy;	
	x  = y  = 100;
	dx = dy = 20;	
	
  UART_Init();
		
	uint16_t nx, ny;
	nx = x, ny = y;
	
	while (1) {
    while (!uart_flag);	
		  LCD_Fill(nx, ny, nx + dx, ny + dy, WHITE);
		  LCD_Fill(x, y, x + dx, y + dy, RED);
		  nx = x;
		  ny = y;
			uart_flag = 0;
	}
}

void UARTRX_ISR()
{
    UART->INTSTATUSnCLEAR = 2;
    uart_flag = 1;
    char ch = UART_getc();

//    if(ch == 'a') {nx = x - 20;}
//    else if(ch == 'w') {ny = y - 20;}
//    else if(ch == 's') {ny = y + 20;}
//		else if(ch == 'd') {nx = x + 20;}
    if(ch == 'a') {vector=1;}
    else if(ch == 'w') {vector=3;}
    else if(ch == 's') {vector=2;}
		else if(ch == 'd') {vector=4;}	
}

int main()
{
	NVIC_CTRL_ADDR=0xf;
	//uint16_t x, y;
	//uint8_t dx, dy;
	SYSInit();
	LCD->LCD_MODE = 1;
  LCD_RST_CLR;
	LCD_RST_SET;
	LCD_BL_CTR_SET;
	//x  = y  = 10;
	//dx = dy = 10;
	LCD_Init();
	while(!LCD_ini_finish) ;
	LCD_ini_finish = 0;
	LCD -> LCD_MODE = 1;
	LCD_CS_SET;
	LCD_RS_SET;
  LCD_WR_SET;
  LCD_RD_SET;
	UART_Init();
//	VGA_print(0,0,255,255,8);
//	delay(30000);
//		while(1){
//			
//			while(!key_flag);	
//			uint32_t din;
//			din = Keyboard_keydata_clear;

//		    int i = 0;
//		    int ans = 0;
//         for (i = 0; i < 16; i++) 
//            {
//	            if ((din >> i) & 1)
//                {
//	        	    ans = i;
//	                break;
//	            }
//	        }
//					
//          if(ans == 4)      {VGA_print(10,10,20,20,1);}
//          else if(ans == 5) {VGA_print(20,20,30,30,2);}
//          else if(ans == 6) {VGA_print(30,30,40,40,3);}
//          else if(ans == 9) {VGA_print(40,40,50,50,4);}
//					else if(ans == 0) {VGA_print(10,10,100,100,5);}
//					
//		      key_flag = 0;						
//					Keyboard_keydata_clear = 1;
//     
//	}	
	
	gamebegin();
//	uart_put();
//	uart_get();
}
