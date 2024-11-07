cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(ws2812_example)

pico_sdk_init()

# Existing executables

# Main executable for the `simple.c` program
add_executable(simple simple.c)

# Generate PIO header from `ws2812.pio` for use with the `simple` executable
pico_generate_pio_header(simple ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

# Link necessary libraries
target_link_libraries(simple PRIVATE pico_stdlib hardware_pio)


# Add extra outputs (e.g., .uf2 file)
pico_add_extra_outputs(simple)

# Add URL if you want to set it for documentation purposes
# example_auto_set_url(simple)


# Original executables and configuration for `pio_ws2812`
add_executable(pio_ws2812)

pico_generate_pio_header(pio_ws2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(pio_ws2812 PRIVATE ws2812.c)

target_link_libraries(pio_ws2812 PRIVATE pico_stdlib hardware_pio)
pico_add_extra_outputs(pio_ws2812)

# example_auto_set_url(pio_ws2812)


# Original configuration for `pio_ws2812_parallel`
add_executable(pio_ws2812_parallel)

pico_generate_pio_header(pio_ws2812_parallel ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(pio_ws2812_parallel PRIVATE ws2812_parallel.c)

target_compile_definitions(pio_ws2812_parallel PRIVATE PIN_DBG1=3)

target_link_libraries(pio_ws2812_parallel PRIVATE pico_stdlib hardware_pio hardware_dma)
pico_add_extra_outputs(pio_ws2812_parallel)

# example_auto_set_url(pio_ws2812_parallel)

# Custom target for generating Python output of PIO program (for documentation)
add_custom_target(pio_ws2812_datasheet DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
    COMMAND pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
    VERBATIM
)
add_dependencies(pio_ws2812 pio_ws2812_datasheet)
