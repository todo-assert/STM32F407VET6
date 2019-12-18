/*
 * @ brief  LCD Platform Driver
 * @ author assert (longqi@1218715400@qq.com)
 * @ date   2019-12-18
 */
 
#incldue "lcd.h"

#define LCD_WRAMCMD	0
#define LCD_RRAMCMD	0

typedef union {
	uint16_t data;
	struct {
		uint16_t r:5;
		uint16_t g:6;
		uint16_t b:5;
	};
}rgb565_map_t;
#define RGB565_MAP_T __attrubte__ ((packed)) rgb565_map_t

#define lcd_read() (LCD_BASE->GRAM)
#define lcd_wr_reg(r) do{LCD_BASE->REG=r;}while(0)
#define lcd_wr_data(d) do{LCD_BASE-GRAM=d;}while(0)
#define lcd_reg_opw(r,g) do{lcd_wr_reg(r);lcd_wr_data(d);}while(0)
#define lcd_reg_opr(r,p,size) do {\
		if(p) {\
			uint16_t *__tmp_p = p;\
			while(size--) {\
				*(__tmp_p++)==lcd_read();\
				asm("nop");\
			}\
		}\
	}while(0)
		
#define lcd_ram_preparew() do{lcd_wr_reg(LCD_WRAMCMD);}while(0)
#define lcd_ram_preparew() do{lcd_wr_reg(LCD_RRAMCMD);}while(0)
	
