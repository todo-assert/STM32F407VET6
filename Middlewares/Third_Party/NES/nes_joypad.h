 
#ifndef _NES_JOYPAD_H_
#define _NES_JOYPAD_H_

int JOYPAD_DAT;
int JOYPAD_CLK;
int JOYPAD_LAT;

#define JOYPAD_0 	0
#define JOYPAD_1 	1	 
 
typedef struct{
	uint8_t state;   //状态
	uint8_t  index;	//当前读取位
	uint32_t value;	//JoyPad 当前值	
}JoyPadType;

/* function ------------------------------------------------------------------*/
void NES_JoyPadInit(void);
void NES_JoyPadReset(void);
void NES_JoyPadDisable(void);
uint8_t NES_GetJoyPadVlaue(int JoyPadNum);


#endif 













