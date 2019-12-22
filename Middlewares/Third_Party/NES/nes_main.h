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
//�ο�������:xiaowei061��NESģ�������ٴ˶�xiaowei061��ʾ��л��
//ALIENTEKս��STM32������
//NESģ���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/10/3
//�汾��V1.0		       								  
////////////////////////////////////////////////////////////////////////////////// 	   
		 
							 										  
typedef struct
{
	char filetype[4]; 	//�ַ�����NES^Z������ʶ��.NES�ļ� 		 
	uint8_t romnum;			//16kB ROM����Ŀ 						 
	uint8_t vromnum;			//8kB VROM����Ŀ				 
	uint8_t romfeature;		//D0��1����ֱ����0��ˮƽ���� 
						// D1��1���е�ؼ��䣬SRAM��ַ$6000-$7FFF
						// D2��1����$7000-$71FF��һ��512�ֽڵ�trainer 
						// D3��1��4��ĻVRAM���� 
						//  D4��D7��ROM Mapper���4� 	  
	uint8_t rommappernum;	// D0��D3��������������0��׼����Ϊ��Mapper��^_^��
						// D4��D7��ROM Mapper�ĸ�4λ 		    
	//uint8_t reserve[8];	// ������������0 					    
	//OM���������У��������trainer������512�ֽڰ���ROM��֮ǰ 
	//VROM��, �������� 
}NesHeader;																		 

uint8_t nes_main(void);
void NesFrameCycle(void);
void NES_ReadJoyPad(uint8_t JoyPadNum);


//PPUʹ��
extern uint8_t *NameTable;			//2K�ı���
extern uint16_t	*Buffer_scanline;	//����ʾ����,���±�Խ�����Ϊ7����ʾ�� 7 ~ 263  0~7 263~270 Ϊ��ֹ�����
//CPUʹ��
extern uint8_t *ram6502;  			//RAM  2K�ֽ�,��malloc����

uint8_t nes_mem_creat(void);		//����nes���������RAM.
void nes_mem_delete(void);	//ɾ��nes����ʱ�����RAM	
										 
#endif











