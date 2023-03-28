#include <unistd.h>

#include "ssd1306.h"
#include "display.hpp"
#include "upper.hpp"

SSD1306 myDisplay;

void clear_OLED(void){
    myDisplay.clearDisplay();
}

void welcome(void){
    // Initialize OLED display and print messages
    myDisplay.initDisplay();
    myDisplay.clearDisplay();
    myDisplay.textDisplay("Welcome to");
    myDisplay.textDisplay("Frame of Knowledge");
    
}

void repeat_animation(unsigned int sequence[], unsigned char length){
    unsigned char i;
    for (i=0; i<3; i++){
        animate(sequence, 0, length);
        usleep(1000000);
        clear_matrix();
    }
}

// void PROMPT(){
//     // write to OLED
//     //Static
//     draw(PRINT_A, 0);
//     usleep(5000000);
//     clear_matrix();
//     // Image
//     // animation
//     repeat_animation(ANIMATE_A);
// }

void PROMPT_0(void){
    // write to OLED
    myDisplay.textDisplay("Working");
    //Static
    // Image
    // animation
}