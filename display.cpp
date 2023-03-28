/* Contains all of matrix functions */

#include "display.hpp"
#include "upper.hpp"
#include "numbers.hpp"
#include "ssd1306.h"
#include "ws2811.h"
#include <unistd.h>
#include <iostream>

#define TARGET_FREQ     WS2811_TARGET_FREQ
#define GPIO_PIN        18
#define DMA             10
#define STRIP_TYPE      WS2811_STRIP_GRB

#define WIDTH           32
#define HEIGHT          32
#define LED_COUNT       HEIGHT*WIDTH

#define CLEAR 29
#define SUBMIT 28
#define RED 27
#define ORANGE 26
#define YELLOW 25
#define GREEN 24
#define BLUE 23
#define PURPLE 22
#define PINK 21

SSD1306 myDisplay;

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
};


void clear_OLED(void){
    myDisplay.clearDisplay();
}

void color_OLED(void){
    myDisplay.textDisplay("Select a color to continue.");
}

void welcome(void){
    // Initialize OLED display and print messages
    myDisplay.initDisplay();
    myDisplay.clearDisplay();
    myDisplay.textDisplay("Welcome to");
    myDisplay.textDisplay("Frame of Knowledge");
    myDisplay.textDisplay("");
    
}

void initialize_matrix(void){
    ws2811_init(&ledstring);
}

void deinitalize_matrix(void){
    ws2811_fini(&ledstring);
}

void clear_matrix(void){
    for (int i=0; i<LED_COUNT; i++){
        ledstring.channel[0].leds[i] = 0;
    }
    ws2811_render(&ledstring);
}


void draw(unsigned char mat[][32], unsigned char color){
    int position;
    for (int y=0; y<32; y++){
        for (int x=0; x<32; x++){
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

void animate(unsigned int sequence[], unsigned char color, unsigned char length){
    unsigned char i;
    for (i=0; i<length; i++){
        ledstring.channel[0].leds[sequence[i]] = dotcolors[color];
        if (i%2 != 0){
            ws2811_render(&ledstring);
            usleep(20000);
        }
    }
    ws2811_render(&ledstring);
}

void PROMPT(unsigned char mat[][32], unsigned int sequence[], unsigned char length, unsigned char color){
    // static image
    clear_OLED();
    myDisplay.textDisplay("You will draw the");
    myDisplay.textDisplay("shown item.");
    draw(mat, color);
    usleep(3000000);
    // animated image
    clear_matrix();
    clear_OLED();
    myDisplay.textDisplay("Here is how you write it.");
    unsigned char i;
    for (i=0; i<3; i++){
        animate(sequence, color, length);
        usleep(1000000);
        clear_matrix();
    }
    // try youself
    clear_OLED();
    myDisplay.textDisplay("Try it yourself!");
    usleep(3000000);
}
