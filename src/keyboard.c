#include <stdint.h>
#include <string.h>
#include "code_def.h"
uint32_t key_flag;

void KEY_ISR(void)
{
	key_flag=1;
	//uint32_t din;
	//din = Keyboard_keydata_clear;    
	//int i = 0;
	//int ans = 0;
	//for (i = 0; i < 16; i++) {
	//  if ((din >> i) & 1) {
	//  	ans = i;
	//    Music_data = 16 + ans;
	//    break;
	//	}
	//}
	//Keyboard_keydata_clear = 1;
}
