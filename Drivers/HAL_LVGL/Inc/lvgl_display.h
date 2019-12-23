#ifndef __LVGL_DISPLAY_H
#define __LVGL_DISPLAY_H

#include "lcd.h"
extern lcd_class_t *lvgl_display;

#ifndef LV_CONF_H
// avoid error 
#include "lv_drv_conf.h"
#include "lvgl/lvgl.h"

extern void lvgl_dispaly_register(lcd_class_t *disp);
extern void lvgl_dispaly_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t *color_p);
extern int lvgl_main(int argc, char **argv);
#endif

#endif /* __LVGL_DISPLAY_H */