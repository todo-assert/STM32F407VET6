#include "nes_main.h"
#include "malloc.h"
//////////////////////////////////////////////////////////////////////////////////	 
//�ο�������:xiaowei061��NESģ�������ٴ˶�xiaowei061��ʾ��л��
//ALIENTEKս��STM32������
//NESģ���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/10/3
//�汾��V1.0		       								  
////////////////////////////////////////////////////////////////////////////////// 	   


uint8_t nesruning = 0;		//��ʼ��Ϊ��
uint8_t frame_cnt;		 	//ͳ��֡��

//NES ֡����ѭ�� 
void NesFrameCycle(void)
{
 	int	clocks;	//CPUִ��ʱ��	 
	//����ģ����ѭ�������VROM���ã�������Ϊ0����ʼ��VROM
	//if ( NesHeader.byVRomSize == 0)
	//����VROM�洢��λ�á�
	frame_cnt=0;
	nesruning=1;
	while(nesruning)
	{
 		//scanline: 0~19 VBANK �Σ���PPUʹ��NMI��������NMI �ж�
		frame_cnt++;//֡������		    
		SpriteHitFlag=false;		
		for(PPU_scanline=0; PPU_scanline<20; PPU_scanline++)
		{ 
			exec6502(CLOCKS_PER_SCANLINE);
 		}
		//scanline: 20, PPU�������ã�ִ��һ�οյ�ɨ��ʱ�� 
		exec6502(CLOCKS_PER_SCANLINE);
		//NesHBCycle();  //ˮƽ����
		PPU_scanline++;	  //20++
		PPU_Reg.NES_R2 &= ~R2_SPR0_HIT;
		//scanline: 21~261 	
		for(; PPU_scanline < SCAN_LINE_DISPALY_END_NUM; PPU_scanline++)
		{
			if((SpriteHitFlag == true) && ((PPU_Reg.NES_R2 & R2_SPR0_HIT) == 0))
			{
				clocks = sprite[0].x * CLOCKS_PER_SCANLINE / NES_DISP_WIDTH;
				exec6502(clocks);
				PPU_Reg.NES_R2 |= R2_SPR0_HIT;
				exec6502(CLOCKS_PER_SCANLINE - clocks);
			}else exec6502(CLOCKS_PER_SCANLINE); 

			if(PPU_Reg.NES_R1 & (R1_BG_VISIBLE | R1_SPR_VISIBLE))//��Ϊ�٣��ر���ʾ
			{
				if(SpriteHitFlag == false)
				NES_GetSpr0HitFlag(PPU_scanline - SCAN_LINE_DISPALY_START_NUM);//����Sprite #0 ��ײ��־
			}
			if((frame_cnt%3)==0)//ÿ2֡��ʾһ��
			{
				NES_RenderLine(PPU_scanline - SCAN_LINE_DISPALY_START_NUM);//ˮƽͬ������ʾһ��
			}	
		}
		//scanline: 262 ���һ֡ 
		exec6502(CLOCKS_PER_SCANLINE);
		PPU_Reg.NES_R2 |= R2_VBlank_Flag;//����VBANK ��־
		//��ʹ��PPU VBANK�жϣ�������VBANK 
		if(PPU_Reg.NES_R0 & R0_VB_NMI_EN)
		{
			NMI_Flag = SET1;//���һ֡ɨ�裬����NMI�ж�
		}  
	   	//����֡IRQ��־��ͬ����������APU�� 		   
		//A mapper function in V-Sync �洢���л���ֱVBANKͬ�� 
		//MapperVSync();  
		//��ȡ������JoyPad״̬,����JoyPad������ֵ*/
		//NES_JoyPadUpdateValue();	 //systick �ж϶�ȡ����ֵ   
	}
} 
//����ֵ:0,ִ��OK;
//	  ����,�������
uint8_t nes_main(void)
{	
	uint16_t offset=0;
	uint8_t res;
	NesHeader *neshreader = (NesHeader *) rom_file;
 	//����NES�ļ�ͷ������0x1A��������0x1a��Ctrl+Z,����ģ���ļ������ķ��ţ�
	//����ʹ��strcncmp�Ƚ�ǰ3���ֽڡ�   
	if(strncmp(neshreader->filetype, "NES", 3) != 0)
	{
		// printf("\r\n�ļ�δ���ػ��ļ����ʹ���, NESģ�����˳���");
		return 1;
	}else
	{
		// printf("\r\n�ļ�������ɡ�");
		// printf("\r\n  16kB  ROM ����Ŀ: %d", neshreader->romnum);
		// printf("\r\n   8kB VROM ����Ŀ: %d", neshreader->vromnum);
		if((neshreader->romfeature & 0x01) == 0){
			// printf("\r\n  ˮƽ����");
		}else{
	 		// printf("\r\n  ��ֱ����");
		}

		if((neshreader->romfeature & 0x02) == 0){
			// printf("\r\n  �޼���SRAM");
		}else{
	 		// printf("\r\n  �м���SRAM");
		}

		if((neshreader->romfeature & 0x04) == 0)
		{
			// printf("\r\n  ��512�ֽڵ�trainer($7000-$71FF)");
		}else
		{
			offset=512;
	 		// printf("\r\n  ��512�ֽڵ�trainer(ROM��ʽ�ݲ�֧��)");
		}

		if((neshreader->romfeature & 0x08) == 0){
			// printf("\r\n  2��ĻVRAM����");
		}else{
	 		// printf("\r\n  4��ĻVRAM����(�ݲ�֧��)");
		}

		printf("\r\n  iNES Mapper Numbers: %d", (neshreader->rommappernum & 0xF0)|( neshreader->romfeature >> 4));
	}	  
	res=nes_mem_creat();//�����ڴ�
	if(res==0)//����ɹ���.��������Ϸ
	{  
		//��ʼ��nes ģ����		 
		init6502mem(0,						//exp_rom 
					0,						//sram �ɿ����;���, �ݲ�֧�� 
					((uint8_t*)&rom_file[offset+0x10]),	//prg_rombank, �洢����С �ɿ����;��� 
					neshreader->romnum 	
					);//��ʼ��6502�洢������
		reset6502();//��λ
		PPU_Init(((uint8_t*)&rom_file[offset+0x10] + (neshreader->romnum * 0x4000)), (neshreader->romfeature & 0x01));//PPU_��ʼ�� 	
		NES_JoyPadInit();  
		NesFrameCycle();//ģ����ѭ��ִ��
	}
	nes_mem_delete();//�ͷ��ڴ�
 	return res;	 		    
}	 
//����nes���������RAM.
//����ֵ:0,�ɹ�;
//    ����,�������.
uint8_t nes_mem_creat(void)
{
	ram6502=(uint8_t*)malloc(2048);	//����2K�ڴ�
	if(ram6502==NULL)return 1;			//����ʧ��
	NameTable=(uint8_t*)malloc(2048);//����2K�ڴ�
	if(NameTable==NULL)return 2;
	Buffer_scanline=(uint16_t*)malloc((8+256+8)*2);
	if(Buffer_scanline==NULL)return 3;
	return 0;	
}	 
//ɾ��nes����ʱ�����RAM		
void nes_mem_delete(void)
{
	free(ram6502);
	free(NameTable);
	free(Buffer_scanline);
} 		











