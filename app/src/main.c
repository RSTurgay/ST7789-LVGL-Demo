#include "../inc/main.h"

lv_display_t *lcd_disp;

void lcd_color_transfer_ready_cb(void)
{
    lv_display_flush_ready(lcd_disp);
}

int32_t lcd_send_cmd(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, const uint8_t *param,
                     size_t param_size)
{
    LV_UNUSED(disp);
    gpio_put(LCD_DC_PIN, 0);
    spi_write_blocking(LCD_SPI, cmd, cmd_size);
}

int32_t lcd_send_color(lv_display_t *disp, const uint8_t *cmd, size_t cmd_size, const uint8_t *param,
                       size_t param_size)
{
    LV_UNUSED(disp);
    gpio_put(LCD_DC_PIN, 1);
    spi_write_blocking(LCD_SPI, param, param_size);
}

int main()
{
    stdio_init_all();

    while (!tud_cdc_connected()) {}

    printf("App Started ! \r\n");

    spi_init(LCD_SPI, 500 * 1000);

    gpio_set_function(LCD_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(LCD_MOSI_PIN, GPIO_FUNC_SPI);

    bi_decl(bi_2pins_with_func(LCD_SCK_PIN, LCD_MOSI_PIN, GPIO_FUNC_SPI));

    gpio_init(LCD_BLK_PIN);
    gpio_init(LCD_DC_PIN);
    gpio_init(LCD_RES_PIN);

    gpio_set_dir(LCD_BLK_PIN, GPIO_OUT);
    gpio_set_dir(LCD_DC_PIN, GPIO_OUT);
    gpio_set_dir(LCD_DC_PIN, GPIO_OUT);

    gpio_put(LCD_BLK_PIN, 1);
    gpio_put(LCD_RES_PIN, 1);

    lv_init();

    lcd_disp = lv_st7789_create(LCD_H_RES, LCD_V_RES, LV_LCD_FLAG_NONE, lcd_send_cmd, lcd_send_color);
    lv_display_set_rotation(lcd_disp, LV_DISPLAY_ROTATION_270);

    lv_color_t *buf1 = NULL;
    lv_color_t *buf2 = NULL;

    uint32_t buf_size = LCD_H_RES * LCD_V_RES / 10 * lv_color_format_get_size(lv_display_get_color_format(lcd_disp));

    buf1 = lv_malloc(buf_size);
    if (buf1 == NULL)
    {
        LV_LOG_ERROR("display draw buffer malloc failed");
        return -1;
    }

    buf2 = lv_malloc(buf_size);
    if (buf2 == NULL)
    {
        LV_LOG_ERROR("display buffer malloc failed");
        lv_free(buf1);
        return -1;
    }
    lv_display_set_buffers(lcd_disp, buf1, buf2, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_obj_t *obj;

    lv_obj_t *scr = lv_screen_active();
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_100, 0);


    obj = lv_label_create(scr);
    lv_obj_set_align(obj, LV_ALIGN_CENTER);
    lv_obj_set_height(obj, LV_SIZE_CONTENT);
    lv_obj_set_width(obj, LV_SIZE_CONTENT);
    lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, 0);
    lv_obj_set_style_text_color(obj, lv_color_black(), 0);
    lv_label_set_text(obj, "Hello World!");

    while (1)
    {
        lv_timer_handler(); // Call LVGL timer handler
        sleep_ms(5);        // Sleep for a while
    }

    return 0;
}