
#ifndef __LCD_H
#define __LCD_H

#include "stdint.h"
#include "stdbool.h"
#include "color.h"

#define USE_LCD_NT35510 1
#define USE_LCD_HX8357A_3P2 1

typedef struct
{
	uint16_t REG;
	uint16_t GRAM;
}lcd_base;

#ifndef LCD_BASE
#define LCD_BASE ((volatile lcd_base *)(0x60000000 | 0x0001FFFE))
#endif

typedef union {
	struct {
		uint16_t reg;
		uint16_t data;
	};
	struct {
		uint16_t flag;
		uint16_t value;
	};
}reg_array_t;

#define fill_reg_array(r,d) \
	{.reg=r, .data=d}

#define DELAY_INSERT_FLAG 0xdead

typedef struct {
	uint16_t lcd_wramcmd;
	uint16_t lcd_rramcmd;
	uint16_t lcd_setxcmd;
	uint16_t lcd_setycmd;
	uint16_t lcd_xcursor;
	uint16_t lcd_ycursor;	
}reg_map_t;

typedef struct {
	uint16_t lcd_width;
	uint16_t lcd_hight;
	uint16_t lcd_id;
	uint16_t direction_reg;
	struct {
		uint16_t direction_up;
		uint16_t direction_down;
		uint16_t direction_left;
		uint16_t direction_right;
	};
}lcd_info_t;

typedef struct {
	const reg_array_t *array;
	uint32_t array_length;
	const reg_map_t *map;
	const lcd_info_t *info;
	int (*probe) (void);
}lcd_resources_t;

typedef enum {
	SET_ROTATE_0 = 0,
	SET_ROTATE_90,
	SET_ROTATE_180,
	SET_ROTATE_270
}direction_set_t;

typedef struct {
	lcd_resources_t *resource;
	volatile lcd_base *base;
	void (*set_window)(uint16_t, uint16_t, uint16_t, uint16_t );
	void (*set_cursor)(uint16_t, uint16_t );
	void (*set_direction)(direction_set_t );
	void (*set_backlight)(unsigned char );
	void (*clear_window)(uint16_t );
	uint16_t (*get_point)(void);
	uint16_t disp_width;
	uint16_t disp_hight;
	direction_set_t dir;
}lcd_class_t;

extern lcd_class_t *lcd_probe(void);

extern lcd_resources_t __lcd_info_begin;
extern lcd_resources_t __lcd_info_end;


#define __delay_us(n) do{uint32_t __delay_us_n=n; while(__delay_us_n--) asm("nop");}while(0);// HAL_Delay(n)
#define __delay_ms(n) HAL_Delay(n)

#define lcd_read() (LCD_BASE->GRAM)
#define lcd_wr_reg(r) do{LCD_BASE->REG=r;}while(0)
#define lcd_wr_data(d) do{LCD_BASE->GRAM=d;}while(0)
#define lcd_reg_opw(r,d) do{lcd_wr_reg(r);lcd_wr_data(d);}while(0)
#define lcd_reg_opr(r,p,s) do {\
		uint16_t size = s; \
		uint16_t *__tmp_p = p;\
		lcd_wr_reg(r);\
		while(size--) {\
			*(__tmp_p++)=lcd_read();\
			__delay_us(1/*80*/);\
		}\
	}while(0)
		

#define location_lcd_info(name) __attribute__((unused, section(".lcd_info_"#name), aligned(4)))

#define __structure_fill_member(name,init,reg,disp) \
	{.array=init, .array_length=sizeof(init)/sizeof(reg_array_t), .map=reg, .info=disp, .probe=__lcd_info_probe_##name}

#define __function_method(name) \
	int __lcd_info_probe_##name(void)

#define __structure_comlete(name,array,map,info) \
	location_lcd_info(name) lcd_resources_t __lcd_info_resource_##name = \
	__structure_fill_member(name,array,map,info)

#define __function_declare(name) \
	extern __function_method(name)
	

#define lcd_init_config(name,array,map,info) \
	__function_declare(name); \
	__structure_comlete(name,array,map,info); \
	__function_method(name)
	
#endif /* __LCD_H */
	