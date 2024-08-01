cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK
include(pico_sdk_import.cmake)

# Set project name
project(st7789_lvgl_demo CXX C ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add subdirectories
add_subdirectory(app)
add_subdirectory(third-party/lvgl)
