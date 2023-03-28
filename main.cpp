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
#include "numbers.hpp"
#include "upper.hpp"

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
        
    // Allows data to be sent to the matrix.
    initialize_matrix();
 
    // unsigned int color;

    pinMode(4, OUTPUT);
    int val;

    unsigned char prompts[] = {24, 2, 3, 4, 5};
    unsigned char number;
    unsigned char pos = 0;

    unsigned char color = 10;
    unsigned char colors[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK};

    // int test = 100;

    while(1){
        number = prompts[pos];
        // digitalWrite(4, HIGH);
        // usleep(13);
        // digitalWrite(4, LOW);
        // usleep(13);

        // for (i=100; i<116; i++){
        //     val = digitalRead(i);
        //     if (val == 0){
        //         cout << "collector: " << i << "\n";
        //     }
        // }

        // cout << "\n";
        
        // usleep(500000);

        // if (digitalRead(test) == 0){
        //     cout << "collector: " << test;
        //     cout << "\n";
        //     test++;
        // }

        // if (test > 115){
        //     break;
        // }
        

        // continue;

        // wait for user to proceed

        // wait for color selection
        color_OLED();
        while (color > 6){
            for (i=0; i<7; i++){
                if (digitalRead(colors[i]) == 0){
                    color = i;
                }
            }
        }
        // while (digitalRead(SUBMIT) != 0);
        // while (digitalRead(SUBMIT) == 0);
        // myDisplay.clearDisplay();
        // myDisplay.textDisplay("Choose a color");

        // user picks color to have letter to display in
        

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
        switch(number){
            case 0:
            PROMPT(PRINT_0, ANIMATE_0, A0_length, color);
            break;
            case 1:
            PROMPT(PRINT_1, ANIMATE_1, A1_length, color);
            break;
            case 2:
            PROMPT(PRINT_2, ANIMATE_2, A2_length, color);
            break;
            case 3:
            PROMPT(PRINT_3, ANIMATE_3, A3_length, color);
            break;
            case 4:
            PROMPT(PRINT_4, ANIMATE_4, A4_length, color);
            break;
            case 5:
            PROMPT(PRINT_5, ANIMATE_5, A5_length, color);
            break;
            case 6:
            PROMPT(PRINT_6, ANIMATE_6, A6_length, color);
            break;
            case 7:
            PROMPT(PRINT_7, ANIMATE_7, A7_length, color);
            break;
            case 8:
            PROMPT(PRINT_8, ANIMATE_8, A8_length, color);
            break;
            case 9:
            PROMPT(PRINT_9, ANIMATE_9, A9_length, color);
            break;
            case 10:
            PROMPT(PRINT_A, ANIMATE_A, AA_length, color); 
            break;
            case 11:
            PROMPT(PRINT_B, ANIMATE_B, AB_length, color); 
            break;
            case 12:
            PROMPT(PRINT_C, ANIMATE_C, AC_length, color); 
            break;
            case 13:
            PROMPT(PRINT_D, ANIMATE_D, AD_length, color); 
            break;
            case 14:
            PROMPT(PRINT_E, ANIMATE_E, AE_length, color); 
            break;
            case 15:
            PROMPT(PRINT_F, ANIMATE_F, AF_length, color); 
            break;
            case 16:
            PROMPT(PRINT_G, ANIMATE_G, AG_length, color); 
            break;
            case 17:
            PROMPT(PRINT_H, ANIMATE_H, AH_length, color); 
            break;
            case 18:
            PROMPT(PRINT_I, ANIMATE_I, AI_length, color); 
            break;
            case 19:
            PROMPT(PRINT_J, ANIMATE_J, AJ_length, color); 
            break;
            case 20:
            PROMPT(PRINT_K, ANIMATE_K, AK_length, color); 
            break;
            case 21:
            PROMPT(PRINT_L, ANIMATE_L, AL_length, color); 
            break;
            case 22:
            PROMPT(PRINT_M, ANIMATE_M, AM_length, color); 
            break;
            case 23:
            PROMPT(PRINT_N, ANIMATE_N, AN_length, color); 
            break;
            case 24:
            PROMPT(PRINT_O, ANIMATE_O, AO_length, color); 
            break;
            case 25:
            PROMPT(PRINT_P, ANIMATE_P, AP_length, color); 
            break;
            case 26:
            PROMPT(PRINT_Q, ANIMATE_Q, AQ_length, color); 
            break;
            case 27:
            PROMPT(PRINT_R, ANIMATE_R, AR_length, color); 
            break;
            case 28:
            PROMPT(PRINT_S, ANIMATE_S, AS_length, color); 
            break;
            case 29:
            PROMPT(PRINT_T, ANIMATE_T, AT_length, color); 
            break;
            case 30:
            PROMPT(PRINT_U, ANIMATE_U, AU_length, color); 
            break;
            case 31:
            PROMPT(PRINT_V, ANIMATE_V, AV_length, color); 
            break;
            case 32:
            PROMPT(PRINT_W, ANIMATE_W, AW_length, color); 
            break;
            case 33:
            PROMPT(PRINT_X, ANIMATE_X, AX_length, color); 
            break;
            case 34:
            PROMPT(PRINT_Y, ANIMATE_Y, AY_length, color); 
            break;
            case 35:
            PROMPT(PRINT_Z, ANIMATE_Z, AZ_length, color); 
            break;
        }

        clear_OLED();
        pos++;
        color = 10;
        if (pos > 4){
            break;
        }

    }

    return 0;
}