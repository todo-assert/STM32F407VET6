#ifndef __LVGL_DISPLAY_H
#define __LVGL_DISPLAY_H

#ifndef LV_CONF_H
// avoid error 

#include "lv_drv_conf.h"
#include "lvgl/lvgl.h"

#endif

#include "lcd.h"
extern lcd_class_t *lvgl_display;

#endif /* __LVGL_DISPLAY_H */