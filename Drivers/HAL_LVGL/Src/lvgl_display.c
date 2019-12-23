
#include "lvgl_display.h"

lcd_class_t *lvgl_display;
void lvgl_dispaly_register(lcd_class_t *disp)
{
	lvgl_display = disp;
}

static void lcd_show_window(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, lv_color_t *color_p)
{
	uint16_t x, i=0;
    lv_disp_buf_t * vdb = lv_disp_get_buf(lv_refr_get_disp_refreshing());
	lvgl_display->set_window(x0, y0, x1, y1);
	// printf("x0:%d y0:%d x1:%d y1:%d\n", x0, y0, x1, y1);
	for(;y0<=y1;y0++) {
		for(x=x0;x<=x1;x++) {
			lvgl_display->base->GRAM = *(uint16_t *)&color_p[i++];
		}
	}
    vdb->flushing = 0;
}

void lvgl_dispaly_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t *color_p)
{
	uint16_t act_x1 = area->x1 < 0 ? 0 : area->x1;
	uint16_t act_y1 = area->y1 < 0 ? 0 : area->y1;
	uint16_t act_x2 = area->x2 > lvgl_display->disp_width - 1 ? lvgl_display->disp_width - 1 : area->x2;
	uint16_t act_y2 = area->y2 > lvgl_display->disp_hight - 1 ? lvgl_display->disp_hight - 1 : area->y2;

	lcd_show_window(act_x1, act_y1, act_x2, act_y2, color_p);
}