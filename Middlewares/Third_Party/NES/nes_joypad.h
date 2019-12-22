 
#ifndef _NES_JOYPAD_H_
#define _NES_JOYPAD_H_

int JOYPAD_DAT;
int JOYPAD_CLK;
int JOYPAD_LAT;

#define JOYPAD_0 	0
#define JOYPAD_1 	1	 
 
typedef struct{
	uint8_t state;   //״̬
	uint8_t  index;	//��ǰ��ȡλ
	uint32_t value;	//JoyPad ��ǰֵ	
}JoyPadType;

/* function ------------------------------------------------------------------*/
void NES_JoyPadInit(void);
void NES_JoyPadReset(void);
void NES_JoyPadDisable(void);
uint8_t NES_GetJoyPadVlaue(int JoyPadNum);


#endif 













