/* Contains all of matrix functions */
#include <iostream>
#include <unistd.h>

#include "display.hpp"
#include "ws2811.h"

#define TARGET_FREQ     WS2811_TARGET_FREQ
#define GPIO_PIN        18
#define DMA             10
#define STRIP_TYPE      WS2811_STRIP_GRB
#define WIDTH           32
#define HEIGHT          32
#define LED_COUNT       HEIGHT*WIDTH


ws2811_t ledstring =
{
    .freq = TARGET_FREQ,
    .dmanum = DMA,
    .channel =
    {
        [0] =
        {
            .gpionum = GPIO_PIN,
            .invert = 0,
            .count = LED_COUNT,
            .strip_type = STRIP_TYPE,
            .brightness = 50,
        },
        [1] =
        {
            .gpionum = 0,
            .invert = 0,
            .count = 0,
            .brightness = 0,
        },
    },
};

ws2811_led_t dotcolors[] =
{
    0x00200000,  // red
    0x00201000,  // orange
    0x00202000,  // yellow
    0x00002000,  // green
    0x00000020,  // blue
    0x00100010,  // purple
    0x00200010,  // pink
    0xEEEEEEEE,  // white
};

// allows for the matrix to be turned on
void matrix_init(void){
    ws2811_init(&ledstring);
}

// resets all things turned on from init
void matrix_deinit(void){
    ws2811_fini(&ledstring);
}

// turns off all LEDs
void clear_matrix(void){
    for (unsigned int i=0; i<LED_COUNT; i++){
        ledstring.channel[0].leds[i] = 0;
    }
    ws2811_render(&ledstring);
}

// print a static image to matrix
void static_image(unsigned char mat[][32], unsigned char color){
    int position;
    for (int y=0; y<HEIGHT; y++){
        for (int x=0; x<WIDTH; x++){
            if (mat[y][x] == 1){
                if (y < 16){
                    if(x%2 == 0){
                        position = 16*x + y;
                    } else {
                        position = (16*x) + (15 - y);
                    }
                } else {
                    if(x%2 == 0){
                        position = (512 + 16*x) + (y - 16);
                    } else {
                        position = (512 + 16*x) + (31 - y);
                    }
                }
                ledstring.channel[0].leds[position] = dotcolors[color];
            }
                
        }
    }

    ws2811_render(&ledstring);
}

// aniamte given image on matrix
void animated_image(unsigned int sequence[], unsigned char length, unsigned char color){
    for (unsigned int i=0; i<3; i++){
        for (unsigned char i=0; i<length; i++){
            ledstring.channel[0].leds[sequence[i]] = dotcolors[color];
            if (i%2 != 0){
                ws2811_render(&ledstring);
                usleep(20000);
            }
        }
        ws2811_render(&ledstring);
        usleep(1000000);
        clear_matrix();
    }
    
    
}

// turn on LEDs from finger tracking
void update_matrix(int location, unsigned char color){
    ledstring.channel[0].leds[location] = dotcolors[color];
    ws2811_render(&ledstring);
}
