/*
 * @ brief  LCD Platform Driver
 * @ author assert (longqi@1218715400@qq.com)
 * @ date   2019-12-18
 */
 
#include "main.h"
#include "lcd.h"

lcd_class_t lcd[1];

#define LCD_WRAMCMD	lcd->resource->map->lcd_wramcmd
#define LCD_RRAMCMD	lcd->resource->map->lcd_rramcmd
#define LCD_SETXCMD lcd->resource->map->lcd_setxcmd
#define LCD_SETYCMD lcd->resource->map->lcd_setycmd
#define LCD_XCURSOR	lcd->resource->map->lcd_xcursor
#define LCD_YCURSOR	lcd->resource->map->lcd_ycursor
#define LCD_DISPWID lcd->disp_width
#define LCD_DISPHIG lcd->disp_hight
#define LCD_WIDTH lcd->resource->info->lcd_width
#define LCD_HIGHT lcd->resource->info->lcd_hight

#define LCD_DIR_REG lcd->resource->info->direction_reg
#define LCD_DIR_UP lcd->resource->info->direction_up
#define LCD_DIR_LEFT lcd->resource->info->direction_left
#define LCD_DIR_RIGHT lcd->resource->info->direction_right
#define LCD_DIR_DOWN lcd->resource->info->direction_down

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
		if(lcd->dir == SET_ROTATE_0 || lcd->dir == SET_ROTATE_180) {
			lcd_reg_opw(LCD_XCURSOR+0, x0>>8);
			lcd_reg_opw(LCD_XCURSOR+1, x0&0xff);
			lcd_reg_opw(LCD_YCURSOR+0, y0>>8);
			lcd_reg_opw(LCD_YCURSOR+1, y0&0xff);
		} else {
			lcd_reg_opw(LCD_YCURSOR+0, x0>>8);
			lcd_reg_opw(LCD_YCURSOR+1, x0&0xff);
			lcd_reg_opw(LCD_XCURSOR+0, y0>>8);
			lcd_reg_opw(LCD_XCURSOR+1, y0&0xff);			
		}
	}
	lcd_reg_opw((LCD_SETXCMD+0), x0>>8);
	lcd_reg_opw((LCD_SETXCMD+1), x0&0xff);
	lcd_reg_opw((LCD_SETXCMD+2), x1>>8);
	lcd_reg_opw((LCD_SETXCMD+3), x1&0xff);
	lcd_reg_opw((LCD_SETYCMD+0), y0>>8);
	lcd_reg_opw((LCD_SETYCMD+1), y0&0xff);
	lcd_reg_opw((LCD_SETYCMD+2), y1>>8);
	lcd_reg_opw((LCD_SETYCMD+3), y1&0xff);
	lcd_ram_preparew();
}

void lcd_set_cursor(uint16_t x0, uint16_t y0) 
{
	if(LCD_XCURSOR && LCD_YCURSOR) {
		if(lcd->dir == SET_ROTATE_0 || lcd->dir == SET_ROTATE_180) {
			lcd_reg_opw(LCD_XCURSOR+0, x0>>8);
			lcd_reg_opw(LCD_XCURSOR+1, x0&0xff);
			lcd_reg_opw(LCD_YCURSOR+0, y0>>8);
			lcd_reg_opw(LCD_YCURSOR+1, y0&0xff);
		} else {
			lcd_reg_opw(LCD_YCURSOR+0, x0>>8);
			lcd_reg_opw(LCD_YCURSOR+1, x0&0xff);
			lcd_reg_opw(LCD_XCURSOR+0, y0>>8);
			lcd_reg_opw(LCD_XCURSOR+1, y0&0xff);			
		}
		lcd_ram_preparew();
	} else {
		lcd_set_window(x0, y0, LCD_DISPWID, LCD_DISPHIG);
	}
	// lcd_ram_preparew();
}

void lcd_set_direction(direction_set_t dir)
{
	lcd->dir = dir;
	switch(dir) {
		case SET_ROTATE_0:
			LCD_DISPWID=LCD_WIDTH;
			LCD_DISPHIG=LCD_HIGHT;
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_UP);
			break;
		case SET_ROTATE_90:
			LCD_DISPWID=LCD_HIGHT;
			LCD_DISPHIG=LCD_WIDTH;
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_LEFT);
			break;
		case SET_ROTATE_180:
			LCD_DISPWID=LCD_WIDTH;
			LCD_DISPHIG=LCD_HIGHT;
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_DOWN);
			break;
		case SET_ROTATE_270:
			LCD_DISPWID=LCD_HIGHT;
			LCD_DISPHIG=LCD_WIDTH;
			lcd_reg_opw(LCD_DIR_REG, LCD_DIR_RIGHT);
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

void lcd_set_backlight(unsigned char duty)
{
	if(!duty) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	} else {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	}
}

void lcd_init(void)
{
	uint16_t i=0;
	const reg_array_t *array = lcd->resource->array;
	for(i=0;i<lcd->resource->array_length;i++) {
		if(array[i].flag == DELAY_INSERT_FLAG) {
			__delay_ms(array[i].value);
		} else {
			lcd_reg_opw(array[i].reg, array[i].data);
		}
	}
	lcd->base = LCD_BASE;
	lcd->set_window = lcd_set_window;
	lcd->set_cursor = lcd_set_cursor;
	lcd->set_direction = lcd_set_direction;
	lcd->clear_window = lcd_clear_window;
	lcd->get_point = lcd_read_data;
	lcd->set_backlight = lcd_set_backlight;
}

lcd_class_t *lcd_probe(void)
{
	lcd_set_backlight(0);
	lcd->resource = &__lcd_info_begin;
	while(lcd->resource < &__lcd_info_end) {
		if(lcd->resource->probe && lcd->resource->probe() == 0) {
			break;
		}
		lcd->resource++;
	}
	assert(lcd->resource >= &__lcd_info_end);
	lcd_init();
	lcd_set_direction(SET_ROTATE_90);
	
	lcd_set_window(0, 0, LCD_DISPWID-1, LCD_DISPHIG-1);
	lcd_clear_window(COLOR_BLACK);
	__delay_ms(200);
	lcd_set_backlight(100);
	printf("\nlcd initial done lcd id = 0x%x\n", lcd->resource->info->lcd_id);
	printf("display window %dx%d\n", LCD_DISPHIG, LCD_DISPWID);
	return lcd;
}



void assert (bool condition)
{
	while(condition) {
		
	}
}
