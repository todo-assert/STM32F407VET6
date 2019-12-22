#ifndef _NES_MAIN_H_
#define _NES_MAIN_H_
#include <stdio.h>
#include <stdbool.h>
#include <string.h>   
#include "6502.h"
#include "PPU.h"
#include "nes_joypad.h"	 
#include "nes_rom.h"
//////////////////////////////////////////////////////////////////////////////////	 
//参考自网友:xiaowei061的NES模拟器，再此对xiaowei061表示感谢！
//ALIENTEK战舰STM32开发板
//NES模拟器 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/10/3
//版本：V1.0		       								  
////////////////////////////////////////////////////////////////////////////////// 	   
		 
							 										  
typedef struct
{
	char filetype[4]; 	//字符串“NES^Z”用来识别.NES文件 		 
	uint8_t romnum;			//16kB ROM的数目 						 
	uint8_t vromnum;			//8kB VROM的数目				 
	uint8_t romfeature;		//D0：1＝垂直镜像，0＝水平镜像 
						// D1：1＝有电池记忆，SRAM地址$6000-$7FFF
						// D2：1＝在$7000-$71FF有一个512字节的trainer 
						// D3：1＝4屏幕VRAM布局 
						//  D4－D7：ROM Mapper的??	  
	uint8_t rommappernum;	// D0－D3：保留，必须是0（准备作为副Mapper号^_^）
						// D4－D7：ROM Mapper的高4位 		    
	//uint8_t reserve[8];	// 保留，必须是0 					    
	//OM段升序排列，如果存在trainer，它的512字节摆在ROM段之前 
	//VROM段, 升序排列 
}NesHeader;																		 

extern int scaler_init(uint16_t disp_width, uint16_t disp_hight);
uint8_t nes_main(void);
void NesFrameCycle(void);
void NES_ReadJoyPad(uint8_t JoyPadNum);


//PPU使用
extern uint8_t *NameTable;			//2K的变量
extern uint16_t	*Buffer_scanline;	//行显示缓存,上下标越界最大为7，显示区 7 ~ 263  0~7 263~270 为防止溢出区
//CPU使用
extern uint8_t *ram6502;  			//RAM  2K字节,由malloc申请

uint8_t nes_mem_creat(void);		//开辟nes运行所需的RAM.
void nes_mem_delete(void);	//删除nes运行时申请的RAM	
										 
#endif











