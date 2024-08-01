#include "../inc/main.h"

int main() {
    stdio_init_all();
    
    lv_init();
    
    while (1) {
        lv_timer_handler(); // Call LVGL timer handler
        sleep_ms(5); // Sleep for a while
    }

    return 0;
}