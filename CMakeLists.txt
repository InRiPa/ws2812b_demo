# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion 13_3_Rel1)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(ws2812_example)
pico_sdk_init()

# Define executables
add_executable(simple simple.c)
add_executable(hutscape hutscape.c)
add_executable(pio_ws2812 ws2812.c)
add_executable(pio_ws2812_parallel ws2812_parallel.c)

# Generate PIO headers for each executable
pico_generate_pio_header(simple ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)
pico_generate_pio_header(hutscape ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)
pico_generate_pio_header(pio_ws2812 ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)
pico_generate_pio_header(pio_ws2812_parallel ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

# Link libraries
target_link_libraries(simple PRIVATE pico_stdlib hardware_pio)
target_link_libraries(hutscape PRIVATE pico_stdlib hardware_pio)
target_link_libraries(pio_ws2812 PRIVATE pico_stdlib hardware_pio)
target_link_libraries(pio_ws2812_parallel PRIVATE pico_stdlib hardware_pio hardware_dma)

# Add extra outputs (e.g., .uf2 file)
pico_add_extra_outputs(simple)
pico_add_extra_outputs(hutscape)
pico_add_extra_outputs(pio_ws2812)
pico_add_extra_outputs(pio_ws2812_parallel)

# Compile definitions for `pio_ws2812_parallel`
target_compile_definitions(pio_ws2812_parallel PRIVATE PIN_DBG1=3)

# Custom target for generating Python output of PIO program (for documentation)
add_custom_target(pio_ws2812_datasheet DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
    DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
    COMMAND pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
    VERBATIM
)
add_dependencies(pio_ws2812 pio_ws2812_datasheet)