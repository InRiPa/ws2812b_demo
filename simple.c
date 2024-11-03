#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h" // PIO program for WS2812

#define LED_PIN 22  // GPIO Pin where the WS2812 data line is connected
#define NUM_LEDS 61 // Set this to the number of LEDs in your strip

// Function to set color for an LED (24-bit color: 0xRRGGBB)
void set_led_color(PIO pio, uint sm, uint32_t color)
{
    // Shift color to output one pixel
    pio_sm_put_blocking(pio, sm, color << 8u);
}

// Convert RGB values to a 24-bit color
uint32_t rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

int main()
{
    // Initialize stdio and PIO
    stdio_init_all();
    PIO pio = pio0;
    uint sm = 0; // State machine

    // Load and initialize the PIO program
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, LED_PIN, 800000, false);

    // Cycle through each LED in the strip
    while (1)
    {
        for (int i = 0; i < NUM_LEDS; i++)
        {
            // Light up LED one by one in red, green, and blue
            set_led_color(pio, sm, rgb(255, 0, 0)); // Red
            sleep_ms(200);

            set_led_color(pio, sm, rgb(0, 255, 0)); // Green
            sleep_ms(200);

            set_led_color(pio, sm, rgb(0, 0, 255)); // Blue
            sleep_ms(200);
        }
    }
}
