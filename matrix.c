/* Contains all of matrix functions */

#include "matrix.h"
#include "ws2811.h"

#define TARGET_FREQ     WS2811_TARGET_FREQ
#define GPIO_PIN        18
#define DMA             10
#define STRIP_TYPE      WS2811_STRIP_GRB

#define WIDTH           16
#define HEIGHT          16
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
    0x00002020,  // lightblue
    0x00000020,  // blue
    0x00100010,  // purple
    0x00200010,  // pink
};


void initialize_matrix(void){
    ws2811_init(&ledstring);
}


void deinitalize_matrix(void){
    ws2811_fini(&ledstring);
}

void matrix_clear(void){
    for (int i=0; i<LED_COUNT; i++){
        ledstring.channel[0].leds[i] = 0;
    }
    ws2811_render(&ledstring);
}


void draw_matrix(){
    int c = 0;
    for (int i=0; i<LED_COUNT; i++){
        ledstring.channel[0].leds[i] = dotcolors[c];
        ws2811_render(&ledstring);
        c++;

        if (c>7){
            c = 0;
        }   
    }

    

    usleep(100000);
}


void draw_A(){
    // unsigned char a_code[] = {
    //                     39, 40 ,41, 42, 43, 44, 45, 46, 49, 50, 51, 52, 53, 54,
    //                     55, 56, 57, 58, 59, 66, 67, 68, 69, 70, 71, 72, 87, 88,
    //                     91, 92, 93, 94, 97, 98, 103, 104
    //                  };

    unsigned char a_code[16][16] = 
    {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    int position;
    int c = 0;
    for (int i=0; i<16; i++){
        for (int j=0; j<16; j++){
            if (a_code[i][j] == 1){
                if(j%2 == 0){
                    position = 16*j + i;
                } else {
                    position = (16*j) + (15-i);
                }
                ledstring.channel[0].leds[position] = dotcolors[c];
            } 
        }

        c++;

        if (c>7){
            c = 0;
        }   
    }
    ws2811_render(&ledstring);
}