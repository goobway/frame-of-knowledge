#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPiI2C.h>
#include <ws2811.h>
#include <cstdint>

/*
    Defines für ws2811 LED Stripes
*/

#define TARGET_FREQ                             WS2811_TARGET_FREQ
#define GPIO_PIN                                18
#define DMA                                     10
#define STRIP_TYPE                              WS2811_STRIP_BGR        // WS2812/SK6812RGB integrated chip+leds
#define LED_COUNT                               256

ws2811_led_t dotcolors[] =
{
    0x00200000,  // red
    0x00201000,  // orange
    0x00202000,  // yellow
    0x00002000,  // green
    0x00002020,  // lightblue
    0x00000020,  // blue
    0x00100010,  // purple
    0x00200010,  // pink
};

ws2811_t ledstring =
{
    nullptr,
    TARGET_FREQ,
    DMA,

    GPIO_PIN, 0, LED_COUNT, 125, STRIP_TYPE,
    0
};

using namespace std;

int main()
{
    ws2811_init(&ledstring);

    int c = 0;

    for (int i = 0; i < LED_COUNT; i++)
    {
        if (ledstring.channel[0].strip_type == WS2811_STRIP_RGB) {
            ledstring.channel[0].leds[i] = dotcolors_rgbw[c];
        }
        else {
            ledstring.channel[0].leds[i] = dotcolors[c];
        }
        
        c++;
        
        ws2811_render(&ledstring);

        if (c == sizeof(dotcolors))
        {
            c = 0;
        }

        usleep(1000000);
    }
    return 0;
}