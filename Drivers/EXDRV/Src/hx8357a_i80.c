
#include "main.h"
#include "lcd.h"

#if USE_LCD_HX8357A_3P2

const reg_array_t hx8357a_init[] = {
	fill_reg_array(0xFF, 0x00),  // Command page 0 
	fill_reg_array(0x72, 0xF6),  // SUB_SEL=0xF6 
	// Power saving for HX8357-A 
	fill_reg_array(0xFF, 0x00),  // Command page 0 
	fill_reg_array(0xF2, 0x00),  // GENON=0x00 
	fill_reg_array(0xE4, 0x00),  // EQVCI_M1=0x00 
	fill_reg_array(0xE5, 0x1C),  // EQGND_M1=0x1C 
	fill_reg_array(0xE6, 0x00),  // EQVCI_M0=0x1C 
	fill_reg_array(0xE7, 0x1C),  // EQGND_M0=0x1C 
	fill_reg_array(0xEE, 0x42),  // For GRAM read/write speed 
	fill_reg_array(0xEF, 0xDB),  // For GRAM read/write speed 
 	fill_reg_array(0x2E, 0x98),  //For Gate timing,  prevent the display abnormal in RGB I/F 
	// Gamma 
	fill_reg_array(0x40, 0x00),  
	fill_reg_array(0x41, 0x2E),  
	fill_reg_array(0x42, 0x2D),  
	fill_reg_array(0x43, 0x3F),  
	fill_reg_array(0x44, 0x3F),  
	fill_reg_array(0x45, 0x3F),  
	fill_reg_array(0x46, 0x2C),  
	fill_reg_array(0x47, 0x7F),  
	fill_reg_array(0x48, 0x07),  
	fill_reg_array(0x49, 0x05),  
	fill_reg_array(0x4A, 0x08),  
	fill_reg_array(0x4B, 0x13),  
	fill_reg_array(0x4C, 0x1E),  
	fill_reg_array(0x50, 0x00),  
	fill_reg_array(0x51, 0x00),  
	fill_reg_array(0x52, 0x00),  
	fill_reg_array(0x53, 0x12),  
	fill_reg_array(0x54, 0x11),  
	fill_reg_array(0x55, 0x3F),  
	fill_reg_array(0x56, 0x00),  
	fill_reg_array(0x57, 0x53),  
	fill_reg_array(0x58, 0x01),  
	fill_reg_array(0x59, 0x0C),  
	fill_reg_array(0x5A, 0x17),  
	fill_reg_array(0x5B, 0x1A),  
	fill_reg_array(0x5C, 0x18),  
	fill_reg_array(0x5D, 0xC3),  
	
	
	
	// Set GRAM area 320x480
	fill_reg_array(0x02, 0x00),  
	fill_reg_array(0x03, 0x00),  
	fill_reg_array(0x04, 0x01),  
	fill_reg_array(0x05, 0x3F),  
	fill_reg_array(0x06, 0x00),  
	fill_reg_array(0x07, 0x00),  
	fill_reg_array(0x08, 0x01),  
	fill_reg_array(0x09, 0xDF),  
	 
	fill_reg_array(0x24, 0x22),  // Set VCOMH voltage,  VHH=0x64 
	fill_reg_array(0x25, 0x64),  // Set VCOML voltage,  VML=0x71 
	fill_reg_array(0x23, 0x90),  // Set VCOM offset,  VMF=0x52 
	fill_reg_array(0x1B, 0x0E),  // Set VERG1 voltage,  VRH[5:0]=0x1E 
	fill_reg_array(0x1D, 0x11),  // FS0[1:0]=01,  Set the operating frequency of the step-up circuit 1 
	// Power on Setting 
	fill_reg_array(0x19, 0x01),  // OSC_EN=1,  Start to Oscillate 
	fill_reg_array(0x1C, 0x03),  // AP=011 
	fill_reg_array(0x01, 0x00),  // Normal display(Exit Deep standby mode) 
	fill_reg_array(0x1F, 0x80),  // Exit standby mode and Step-up circuit 1 enable 
	// GAS_EN=1,  VCOMG=0,  PON=0,  DK=0,  XDK=0,  DDVDH_TRI=0,  STB=0 
	fill_reg_array(DELAY_INSERT_FLAG, 5),  
	fill_reg_array(0x1F, 0x90),  // Step-up circuit 2 enable 
	// GAS_EN=1,  VCOMG=0,  PON=1,  DK=0,  XDK=0,  DDVDH_TRI=0,  STB=0 
	fill_reg_array(DELAY_INSERT_FLAG, 5),  
	fill_reg_array(0x1F, 0xD4),  
	// GAS_EN=1,  VCOMG=1,  PON=1,  DK=0,  XDK=1,  DDVDH_TRI=0,  STB=0 
	fill_reg_array(DELAY_INSERT_FLAG, 5),  
	// Display ON Setting 
	fill_reg_array(0x28, 0x08),  // GON=0,  DTE=0,  D[1:0]=01 
	fill_reg_array(DELAY_INSERT_FLAG, 40),  
	fill_reg_array(0x28, 0x38),  // GON=1,  DTE=1,  D[1:0]=10 
	fill_reg_array(DELAY_INSERT_FLAG, 40),  
	fill_reg_array(0x28, 0x3C),  // GON=1,  DTE=1,  D[1:0]=11 
	fill_reg_array(DELAY_INSERT_FLAG, 40),  

	fill_reg_array(0x17, 0x05),  // 16-bit/pixel 	
};

const reg_map_t hx8357a_reg_map[1] = {
	{
		.lcd_wramcmd = 0x22,
		.lcd_rramcmd = 0x22,
		.lcd_setxcmd = 0x02,
		.lcd_setycmd = 0x06,
		.lcd_xcursor = 0x80,
		.lcd_ycursor = 0x82,
	}
};

const lcd_info_t hx8357a_disp_info[1] = {
	{
		.lcd_width = 320,
		.lcd_hight = 480,
		.lcd_id = 0x57,
		.direction_reg = 0x16,
		{
			.direction_up = 0x48,
			.direction_left = 0x28,
			.direction_down = 0x88,
			.direction_right = 0xe8,
		},
	},
};

lcd_init_config(hx8357a, hx8357a_init, hx8357a_reg_map, hx8357a_disp_info)
{
	int ret = -1;
	
	uint16_t val;
	lcd_reg_opw(0xFF, 0x00);  // Command page 0 
	__delay_ms(1);
	lcd_wr_reg(0x00);
	__delay_ms(1);
	val = lcd_read()&hx8357a_disp_info->lcd_id;
	
	printf("lcd id get = %x\n", val);
	ret = hx8357a_disp_info->lcd_id == val ? 0:-1;
	
	return ret;
}

#endif