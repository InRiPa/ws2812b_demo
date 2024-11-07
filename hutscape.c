/**
 * Example found on : https://hutscape.com/tutorials/pico-neopixel
 */

#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"

const int PIN_TX = 22;

static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) |
           ((uint32_t)(g) << 16) |
           (uint32_t)(b);
}

void run_initial_demo()
{
    // OPTION A: uncomment sleep_ms(500) and view the individual colors
    // OPTION B: comment sleep_ms(500) and view the pixels cascading colors
    put_pixel(urgb_u32(0xff, 0, 0)); // Red
    // // sleep_ms(500);
    put_pixel(urgb_u32(0, 0xff, 0)); // Green
    // // // sleep_ms(500);
    put_pixel(urgb_u32(0, 0, 0xff)); // Blue
    // // // sleep_ms(500);
    put_pixel(urgb_u32(0xff, 0xff, 0)); // Purple
    // // sleep_ms(500);
    put_pixel(urgb_u32(0, 0xff, 0xff)); // Cyan
    // // sleep_ms(500);
    put_pixel(urgb_u32(0xff, 0xff, 0xff)); // White
    // // sleep_ms(500);
    put_pixel(urgb_u32(0, 0, 0)); // Black or off
    // // sleep_ms(500);

    sleep_ms(1000);
    // Clear all pixels
    for (int i = 0; i <= 64; i++)
    {
        put_pixel(urgb_u32(0, 0, 0)); // Black or off
    }
    sleep_ms(1000);
}

void run_lightall()
{
    puts("Hello RGB and other colors!");

    for (size_t i = 0; i < 64; i++)
    {
        put_pixel(urgb_u32(0, 0xff, 0)); // Green
    }

    sleep_ms(1000);
    // Clear all pixels
    for (int i = 0; i <= 64; i++)
    {
        put_pixel(urgb_u32(0, 0, 0)); // Black or off
    }
    sleep_ms(1000);
}

void run_oneLed()
{
    const int num_leds = 64;
    const uint32_t color = urgb_u32(0, 0xff, 0); // Green

    for (int i = 0; i < num_leds; i++)
    {
        // Turn on one LED at position `i` and turn off the rest
        for (int j = 0; j < num_leds; j++)
        {
            if (j == i)
            {
                put_pixel(color); // Turn on LED at position i
            }
            else
            {
                put_pixel(urgb_u32(0, 0, 0)); // Turn off other LEDs
            }
        }
        sleep_ms(200); // Delay to create the running effect
    }
}

int main()
{
    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    char str[12];

    ws2812_program_init(pio, sm, offset, PIN_TX, 800000, false);

    while (true)
    {
        run_oneLed();
    }
}