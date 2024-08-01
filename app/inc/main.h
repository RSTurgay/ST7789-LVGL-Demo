#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include "tusb.h"

#include "./src/drivers/display/st7789/lv_st7789.h"
#include "lvgl.h"

#define LCD_H_RES       240
#define LCD_V_RES       320

#define LCD_SPI spi0
#define LCD_SCK_PIN 2
#define LCD_MOSI_PIN 3
#define LCD_DC_PIN 0
#define LCD_RES_PIN 1
#define LCD_BLK_PIN 4
