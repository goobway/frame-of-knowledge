#include <iostream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <wiringPi.h>
#include <mcp23017.h>
#include <unistd.h>

#include <signal.h>
#include "display.hpp"
#include "prompts.hpp"

#define CLEAR 29
#define SUBMIT 28
#define RED 27
#define ORANGE 26
#define YELLOW 25
#define GREEN 24
#define BLUE 23
#define PURPLE 22
#define PINK 21

void matrix_clear(void);
void deinitalize_matrix(void);


void int_handler(int sig){
    printf("\n");
    clear_matrix();
    // finshes all process started by the matrix
    deinitalize_matrix();
    clear_OLED();
    int j;
    for (j=100; j<116; j++){
        digitalWrite(j, LOW);
    }
    
    exit(0);
}


int main(void){ 
    // Setup handler for CTRL-C.
    signal(SIGINT, int_handler);

    // GPIO control setup.
    wiringPiSetup();

    /*
    Initialize the four expanders.
    h1/h1 - 
    */
    mcp23017Setup(100, 0x20);
    // mcp23017Setup(200, 0x21);
    // mcp23017Setup(300, 0x22);
    // mcp23017Setup(400, 0x23);

    // Set all exapnders to read input values.
    unsigned int expander;
    unsigned int pin;
    unsigned int pin_start = 100;
    for (expander=1; expander<5; expander++){
        pin_start = 100*expander;
        for (pin=pin_start; pin < pin_start+16; pin++){
            pinMode(pin, INPUT);
        } 
    }

    // Set up button control for the system
    unsigned int buttons[] = {CLEAR, SUBMIT, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK};
    unsigned int i;
    for (i=0; i<9; i++){
        pinMode(buttons[i], INPUT);
        pullUpDnControl(buttons[i], PUD_UP);
    }

    // Initialize matrix and display welcome message
    welcome();
        
    /*
    Allows data to be sent to the matrix.
    - Found in matrix.cpp
    */
    initialize_matrix();

    

    
    // draw_matrix(PRINT_0, 1);
    
    // animate_matrix(ANIMATE_0);
 

    // unsigned int color;

    pinMode(4, OUTPUT);
    int val;

    PROMPT_A();

    while(1){
        // digitalWrite(4, HIGH);
        // usleep(13);
        // digitalWrite(4, LOW);
        // usleep(13);

        for (i=100; i<116; i++){
            val = digitalRead(i);
            if (val == 0){
                cout << "collector: " << i << "\n";
            }
        }
        // usleep(1000000);
        // cout << "\n";
        
        
        // if (val == 0){
        //     cout << "IR\n";
        //     cout.flush();
        // }
        // if (val == 1){
        //     cout << "NO IR\n";
        //     cout.flush();
        // }

        // wait for user to proceed
        // myDisplay.textDisplay("Welcome to");
        // myDisplay.textDisplay("Frame of Knowledge");
        // myDisplay.textDisplay("");
        // myDisplay.textDisplay("Press Submit To continue");
        // while (digitalRead(SUBMIT) != 0);
        // while (digitalRead(SUBMIT) == 0);
        // myDisplay.clearDisplay();
        // myDisplay.textDisplay("Choose a color");

        // // user picks color to have letter to display in
        // unsigned int color = 7;
        // unsigned int colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK};
        // while (color > 6){
        //     for (i=0; i<7; i++){
        //         if (digitalRead(colors[i]) == 0){
        //             color = i;
        //         }
        //     }
        // }

        // myDisplay.clearDisplay();
        // myDisplay.textDisplay("Color selected!");
        // usleep(500000);

        // // display static image
        // myDisplay.clearDisplay();
        // myDisplay.textDisplay("You will draw the");
        // myDisplay.textDisplay("given letter.");

        // draw_matrix(PRINT_0, color);

        // myDisplay.textDisplay("");
        // myDisplay.textDisplay("Press submit to continue");

        
        // while (digitalRead(SUBMIT) != 0);
        // while (digitalRead(SUBMIT) == 0);

        // myDisplay.clearDisplay();
        // matrix_clear();
        // int number = 10;
        // switch(number){
        //     case 0:
        //     PROMPT_0();
        //     break;
        //     case 1:
        //     break;
        //     case 2:
        //     break;
        //     case 3:
        //     break;
        //     case 4:
        //     break;
        //     case 5:
        //     break;
        //     case 6:
        //     break;
        //     case 7:
        //     break;
        //     case 8:
        //     break;
        //     case 9:
        //     break;
        //     case 10:
        //     PROMPT_A();
        //     number = 1;
        //     break;
        // }

        // user looks at static image

        // user looks at animation


    }

    return 0;
}