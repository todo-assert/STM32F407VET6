/*
 * @ brief  LCD Platform Driver
 * @ author assert (longqi@1218715400@qq.com)
 * @ date   2019-12-18
 */
 
#include "main.h"
#include "lcd.h"

static lcd_resources_t *resource = NULL;

#define LCD_WRAMCMD	resource->map->lcd_wramcmd
#define LCD_RRAMCMD	resource->map->lcd_rramcmd
#define LCD_SETXCMD resource->map->lcd_setxcmd
#define LCD_SETYCMD resource->map->lcd_setycmd
#define LCD_XCURSOR	resource->map->lcd_xcursor
#define LCD_YCURSOR	resource->map->lcd_ycursor
#define LCD_DISPWID resource->info->disp_width
#define LCD_DISPHIG resource->info->disp_hight

#define LCD_DIR_REG resource->info->direction_reg
#define LCD_DIR_UP resource->info->direction_up
#define LCD_DIR_LEFT resource->info->direction_left
#define LCD_DIR_RIGHT resource->info->direction_right
#define LCD_DIR_DOWN resource->info->direction_down

typedef enum {
	SET_ROTATE_0 = 0,
	SET_ROTATE_90,
	SET_ROTATE_180,
	SET_ROTATE_270
}direction_set_t;

typedef union {
	uint16_t data;
	struct {
		uint16_t r:5;
		uint16_t g:6;
		uint16_t b:5;
	};
}__attribute__((packed)) rgb565_map_t;

#define lcd_ram_preparew() do{if(LCD_WRAMCMD) lcd_wr_reg(LCD_WRAMCMD);}while(0)
#define lcd_ram_preparer() do{if(LCD_RRAMCMD) lcd_wr_reg(LCD_RRAMCMD);}while(0)
	
uint16_t lcd_read_data(void)
{
	rgb565_map_t color[1];
	uint16_t data[2];
	data[0] = lcd_read();
	__delay_us(1);
	data[0] = lcd_read();
	__delay_us(1);
	data[1] = lcd_read();
	color->r = data[0] >> 8;
	color->g = data[0] & 0xff;
	color->b = data[1] >> 8;
	
	return color->data;
}

void lcd_set_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
	if(LCD_XCURSOR && LCD_YCURSOR) {
		lcd_reg_opw(LCD_XCURSOR+0, x0>>8);
		lcd_reg_opw(LCD_XCURSOR+1, x0&0xff);
		lcd_reg_opw(LCD_YCURSOR+0, y0>>8);
		lcd_reg_opw(LCD_YCURSOR+1, y0&0xff);
	}
	lcd_reg_opw(LCD_SETXCMD+0, x0>>8);
	lcd_reg_opw(LCD_SETXCMD+1, x0&0xff);
	lcd_reg_opw(LCD_SETXCMD+2, x1>>8);
	lcd_reg_opw(LCD_SETXCMD+3, x1&0xff);
	lcd_reg_opw(LCD_SETYCMD+0, y0>>8);
	lcd_reg_opw(LCD_SETYCMD+1, y0&0xff);
	lcd_reg_opw(LCD_SETYCMD+2, y1>>8);
	lcd_reg_opw(LCD_SETYCMD+3, y1&0xff);
	// lcd_ram_preparew();
}

void lcd_set_cursor(uint16_t x0, uint16_t y0) 
{
	if(LCD_XCURSOR && LCD_YCURSOR) {
		lcd_reg_opw(LCD_XCURSOR+0, x0>>8);
		lcd_reg_opw(LCD_XCURSOR+1, x0&0xff);
		lcd_reg_opw(LCD_YCURSOR+0, y0>>8);
		lcd_reg_opw(LCD_YCURSOR+1, y0&0xff);
		// lcd_ram_preparew();
	} else {
		lcd_set_window(x0, y0, LCD_DISPWID-1, LCD_DISPHIG-1);
	}
	lcd_ram_preparew();
}

void lcd_set_direction(direction_set_t dir)
{
	switch(dir) {
		case SET_ROTATE_0:
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_UP);
			break;
		case SET_ROTATE_90:
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_LEFT);
			break;
		case SET_ROTATE_180:
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_RIGHT);
			break;
		case SET_ROTATE_270:
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_DOWN);
			break;
		default: break;
	}
}

void lcd_clear_window(uint16_t color)
{
	uint32_t w, h;
	lcd_set_cursor(0, 0);
	for(w=0;w<LCD_DISPWID;w++) {
		for(h=0;h<LCD_DISPHIG;h++)
			lcd_wr_data(color);
	}
}

void lcd_init(void)
{
	uint16_t i=0;
	const reg_array_t *array = resource->array;
	for(i=0;i<resource->array_length;i++) {
		if(array[i].flag == DELAY_INSERT_FLAG) {
			__delay_ms(array[i].value);
		} else {
			lcd_reg_opw(array[i].reg, array[i].data);
		}
	}
}

void lcd_probe(void)
{
	resource = &__lcd_info_begin;
	while(resource < &__lcd_info_end) {
		if(resource->probe==NULL) continue;
		if(resource->probe() == 0) {
			break;
		}
	}
	assert(resource >= &__lcd_info_end);
	lcd_init();
	// lcd_wr_reg(0x2900);
	// lcd_wr_reg(0x2c00);
	lcd_set_direction(SET_ROTATE_0);
	lcd_clear_window(0xF800);
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	printf("\n lcd initial done lcd id = 0x%x\n", resource->info->lcd_id);
	printf("display window %dx%d\n", LCD_DISPHIG, LCD_DISPWID);
}



void assert (bool condition)
{
	while(condition) {
		
	}
}
