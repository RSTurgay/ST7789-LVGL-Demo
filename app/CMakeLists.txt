# Create executable
add_executable(st7789_lvgl_demo)

# Add source files
target_sources(st7789_lvgl_demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/main.h
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/lv_conf.h
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

# Include directories
target_include_directories(st7789_lvgl_demo PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../third-party/lvgl
)

# Link libraries
target_link_libraries(st7789_lvgl_demo PRIVATE pico_stdlib hardware_spi lvgl)

# Enable USB serial output, disable UART output
pico_enable_stdio_usb(st7789_lvgl_demo 1)
pico_enable_stdio_uart(st7789_lvgl_demo 0)

# Create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(st7789_lvgl_demo)