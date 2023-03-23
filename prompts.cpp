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

void PROMPT_A(void){
    // write to OLED
    //Static
    draw(PRINT_A, 0);
    // Image
    // animation
    // animate(ANIMATE_A, 0);
}

void PROMPT_0(void){
    // write to OLED
    myDisplay.textDisplay("Working");
    //Static
    // Image
    // animation
}