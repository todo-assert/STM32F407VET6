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
//²Î¿¼×ÔÍøÓÑ:xiaowei061µÄNESÄ£ÄâÆ÷£¬ÔÙ´Ë¶Ôxiaowei061±íÊ¾¸ĞĞ»£¡
//ALIENTEKÕ½½¢STM32¿ª·¢°å
//NESÄ£ÄâÆ÷ ´úÂë	   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ĞŞ¸ÄÈÕÆÚ:2012/10/3
//°æ±¾£ºV1.0		       								  
////////////////////////////////////////////////////////////////////////////////// 	   
		 
							 										  
typedef struct
{
	char filetype[4]; 	//×Ö·û´®¡°NES^Z¡±ÓÃÀ´Ê¶±ğ.NESÎÄ¼ş 		 
	uint8_t romnum;			//16kB ROMµÄÊıÄ¿ 						 
	uint8_t vromnum;			//8kB VROMµÄÊıÄ¿				 
	uint8_t romfeature;		//D0£º1£½´¹Ö±¾µÏñ£¬0£½Ë®Æ½¾µÏñ 
						// D1£º1£½ÓĞµç³Ø¼ÇÒä£¬SRAMµØÖ·$6000-$7FFF
						// D2£º1£½ÔÚ$7000-$71FFÓĞÒ»¸ö512×Ö½ÚµÄtrainer 
						// D3£º1£½4ÆÁÄ»VRAM²¼¾Ö 
						//  D4£­D7£ºROM MapperµÄÍ4» 	  
	uint8_t rommappernum;	// D0£­D3£º±£Áô£¬±ØĞëÊÇ0£¨×¼±¸×÷Îª¸±MapperºÅ^_^£©
						// D4£­D7£ºROM MapperµÄ¸ß4Î» 		    
	//uint8_t reserve[8];	// ±£Áô£¬±ØĞëÊÇ0 					    
	//OM¶ÎÉıĞòÅÅÁĞ£¬Èç¹û´æÔÚtrainer£¬ËüµÄ512×Ö½Ú°ÚÔÚROM¶ÎÖ®Ç° 
	//VROM¶Î, ÉıĞòÅÅÁĞ 
}NesHeader;																		 

uint8_t nes_main(void);
void NesFrameCycle(void);
void NES_ReadJoyPad(uint8_t JoyPadNum);


//PPUÊ¹ÓÃ
extern uint8_t *NameTable;			//2KµÄ±äÁ¿
extern uint16_t	*Buffer_scanline;	//ĞĞÏÔÊ¾»º´æ,ÉÏÏÂ±êÔ½½ç×î´óÎª7£¬ÏÔÊ¾Çø 7 ~ 263  0~7 263~270 Îª·ÀÖ¹Òç³öÇø
//CPUÊ¹ÓÃ
extern uint8_t *ram6502;  			//RAM  2K×Ö½Ú,ÓÉmallocÉêÇë

uint8_t nes_mem_creat(void);		//¿ª±ÙnesÔËĞĞËùĞèµÄRAM.
void nes_mem_delete(void);	//É¾³ınesÔËĞĞÊ±ÉêÇëµÄRAM	
										 
#endif











