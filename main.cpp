#include <iostream>
#include <cstdlib>
using namespace std;


#include <wiringPi.h>
#include <mcp23017.h>
#include <unistd.h>
#include <signal.h>

#include <termios.h>

#include "ssd1306.h"
#include "display.hpp"

#include "numbers.hpp"
#include "upper.hpp"
#include "lower.hpp"
#include "sketches.hpp"

#include "classify_input.hpp"

#define CLEAR 29
#define SUBMIT 28
#define RED 27
#define ORANGE 26
#define YELLOW 25
#define GREEN 24
#define BLUE 23
#define PURPLE 22
#define PINK 21

// global vars
SSD1306 myDisplay;
unsigned char submit;
unsigned char color;

// initialize the expanders
void mcp_init(void){
    // Initialize the four expanders.
    mcp23017Setup(100, 0x20);
    mcp23017Setup(200, 0x21);
    mcp23017Setup(300, 0x22);
    mcp23017Setup(400, 0x23);

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
}

// set the push buttons as inputs
void button_init(void){
    unsigned int buttons[] = {CLEAR, SUBMIT, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK};
    unsigned int i;
    for (i=0; i<9; i++){
        pinMode(buttons[i], INPUT);
        pullUpDnControl(buttons[i], PUD_UP);
    }
}

// handles ctrl-c input
void ctrl_c(int sig){
    printf("\n");

    myDisplay.clearDisplay();
    clear_matrix();
    matrix_deinit();
    
    exit(0);
}

// the following functions control the push buttons interrupts
void clear_int(){
    clear_matrix();
    for (int y=0; y<32; y++){
        for (int x=0; x<32; x++){
            if (USED_MATRIX[x][y] == 1){
                USED_MATRIX[x][y] = 0;
            }
        }
    }
}

void submit_int(){
    submit = 1;
}

void red_int(){
    color = 0;
}

void orange_int(){
    color = 1;
}

void yellow_int(){
    color = 2;
}

void green_int(){
    color = 3;
}

void blue_int(){
    color = 4;
}

void purple_int(){
    color = 5;
}

void pink_int(){
    color = 6;
}

// gives the correct prompt
void prompt_selection(unsigned char p_num){     
    switch(p_num){
        case 0:
            myDisplay.textDisplay("You will write the number 0.");
            static_image(PRINT_0, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            // myDisplay.textDisplay("This is an (A)pple.");
            // static_image(apple, color);
            // usleep(3000000);
            // clear_matrix();
            // myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("number 0.");
            animated_image(ANIMATE_0, A0_length, color);
            usleep(1000000);
            
            break;
        case 10:
            myDisplay.textDisplay("You will write the letter A.");
            static_image(PRINT_A, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is an (A)pple.");
            static_image(apple, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter A.");
            animated_image(ANIMATE_A, AA_length, color);
            usleep(1000000);
            
            break;
        case 11:
            myDisplay.textDisplay("You will write the letter B.");
            static_image(PRINT_B, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is an (B)anana.");
            static_image(banana, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter B.");
            animated_image(ANIMATE_B, AB_length, color);
            usleep(1000000);
        
            break;
        // case 12:
        //     myDisplay.textDisplay("You will write the letter C.");
        //     static_image(PRINT_C, color);
        //     usleep(3000000);
        //     clear_matrix();
        //     myDisplay.clearDisplay();

        //     myDisplay.textDisplay("This is an (B)anana.");
        //     static_image(banana, color);
        //     usleep(3000000);
        //     clear_matrix();
        //     myDisplay.clearDisplay();

        //     myDisplay.textDisplay("This is how to write the");
        //     myDisplay.textDisplay("letter C.");
        //     animated_image(ANIMATE_C, AC_length, color);
        //     usleep(1000000);
            
        //     break;
    }
}

// got x-dimension location of finger
// returns when a collector outputs a 1
int get_x(void){
    unsigned int x1, x2;

    for (unsigned int i=0; i<16; i++){
        if (i < 8){
            x1 = digitalRead(100+i+8);
            x2 = digitalRead(200+i+8);
        } else {
            x1 = digitalRead(100+i-8);
            x2 = digitalRead(200+i-8);
        }

        if (x1 == 1){
            return 31-2*i;
        } else if (x2 == 1){
            return 2*i;
        } else if (i==15){
            return 32;
        }
    }
}

// got y-dimension location of finger
// returns when a collector outputs a 1
int get_y(void){
    unsigned int y1, y2;

    for (unsigned int i=0; i<16; i++){
        if (i < 8){
            y1 = digitalRead(300+i+8);
            y2 = digitalRead(400+i+8);
        } else {
            y1 = digitalRead(300+i-8);
            y2 = digitalRead(400+i-8);
        }

        if (y1 == 1){
            return 31-2*i;
        } else if (y2 == 1){
            return 2*i;
        } else if (i==15){
            return 32;
        }
    }
}

int main(void){
    // Setup handler for CTRL-C.
    signal(SIGINT, ctrl_c);

    // Setup everything
    wiringPiSetup();
    mcp_init();
    button_init();
    matrix_init();
    myDisplay.initDisplay();

    // Color select interrupts
    wiringPiISR(CLEAR, INT_EDGE_FALLING, clear_int);
    wiringPiISR(SUBMIT, INT_EDGE_FALLING, submit_int);
    wiringPiISR(RED, INT_EDGE_FALLING, red_int);
    wiringPiISR(ORANGE, INT_EDGE_FALLING, orange_int);
    wiringPiISR(YELLOW, INT_EDGE_FALLING, yellow_int);
    wiringPiISR(BLUE, INT_EDGE_FALLING, blue_int);
    wiringPiISR(GREEN, INT_EDGE_FALLING, green_int);
    wiringPiISR(PURPLE, INT_EDGE_FALLING, purple_int);
    wiringPiISR(PINK, INT_EDGE_FALLING, pink_int);

    // set initial values for globals
    submit = 0;
    color = 10; // outside range of colors

    // set up random color selection
    srand(time(NULL));

    // greet user on start
    myDisplay.clearDisplay();
    myDisplay.textDisplay("Welcome to the");
    myDisplay.textDisplay("Frame of Knowledge.");
    myDisplay.textDisplay("");
    myDisplay.textDisplay("Press Submit to start!");

    // wait for user to start the prompts
    while(submit==0);
    submit = 0;
    myDisplay.clearDisplay();

    unsigned char prompts[] = {0};  // prompts that will be shown
    unsigned char pos = 0;  // control position in prompts array

    int x_coord;
    int y_coord;

    while (1){
        // select a random color
        color = rand() % 7;

        // show student given prompt
        prompt_selection(prompts[pos]);

        // tells the user they can now draw on the matrix
        myDisplay.clearDisplay();
        myDisplay.textDisplay("Try it yourself!");
        myDisplay.textDisplay(" ");
        myDisplay.textDisplay("Use the buttons to select");
        myDisplay.textDisplay("different colors!");

        // allows user to draw on the matrix
        while(1){
            if (submit){
                // for now brak out of the loop
                submit = 0;
                break;
            }
            
            // call detection function
            x_coord = get_x();
            y_coord = get_y();

            // check if they pressed submit
            

            // within submit check if they are right or wrong
        }
    }


}




// unsigned int detect(void){
//     unsigned int i;
//     unsigned int val1, val2, val3, val4;

//     for (i=0; i<16; i++){
//         // if (i < 8){
//         //     val1 = digitalRead(100+i+8);
//         //     val2 = digitalRead(200+i+8);
//         //     val3 = digitalRead(300+i+8);
//         //     val4 = digitalRead(400+i+8);
//         // } else {
//         //     val1 = digitalRead(100+i-8);
//         //     val2 = digitalRead(200+i-8);
//         //     val3 = digitalRead(300+i+8);
//         //     val4 = digitalRead(400+i+8);
//         // }
        
//         val1 = digitalRead(100+i);
//         val2 = digitalRead(200+i);
//         val3 = digitalRead(300+i);
//         val4 = digitalRead(400+i);
//         if (val1 == 0){
//             cout << "collector: " << 100+i << "\n";
//         }
//         if (val2 == 0){
//             cout << "collector: " << 200+i << "\n";
//         }
//         if (val3 == 0){
//             cout << "collector: " << 300+i << "\n";
//         }
//         if (val4 == 0){
//             cout << "collector: " << 400+i << "\n";
//         }

//         // if (val1 == 1){
//         //     return 31-2*i;
//         // }
//         // if (val2 == 1){
//         //     return 2*i;
//         // } 
        
//         // if (i == 15){
//         //     return 33;
//         // }
    
//     }

// }

// void prompt_selection(unsigned char p_num){
//     // go through the given prompts 
//     unsigned int pic;       
//     switch(p_num){
//         case 0:
//             myDisplay.textDisplay("You will write the letter A");
//             static_image(PRINT_0, color);
//             usleep(3000000);
//             myDisplay.clearDisplay();
//             myDisplay.textDisplay("This is how to write the letter A");
//             animated_image(ANIMATE_0, A0_length, color);
//             usleep(1000000);
//             myDisplay.clearDisplay();
//             myDisplay.textDisplay("Try it yourself!");
//             myDisplay.textDisplay(' ');
//             myDisplay.textDisplay("Select any color you want!");

            
//             break;
//         // case 1:
//         //     PROMPT(PRINT_1, ANIMATE_1, A1_length, color, pic=0);
//         //     break;
//         // case 2:
//         //     PROMPT(PRINT_2, ANIMATE_2, A2_length, color, pic=0);
//         //     break;
//         // case 3:
//         //     PROMPT(PRINT_3, ANIMATE_3, A3_length, color, pic=0);
//         //     break;
//         // case 4:
//         //     PROMPT(PRINT_4, ANIMATE_4, A4_length, color, pic=0);
//         //     break;
//         // case 5:
//         //     PROMPT(PRINT_5, ANIMATE_5, A5_length, color, pic=0);
//         //     break;
//         // case 6:
//         //     PROMPT(PRINT_6, ANIMATE_6, A6_length, color, pic=0);
//         //     break;
//         // case 7:
//         //     PROMPT(PRINT_7, ANIMATE_7, A7_length, color, pic=0);
//         //     break;
//         // case 8:
//         //     PROMPT(PRINT_8, ANIMATE_8, A8_length, color, pic=0);
//         //     break;
//         // case 9:
//         //     PROMPT(PRINT_9, ANIMATE_9, A9_length, color, pic=0);
//         //     break;
//         // case 10:
//         //     PROMPT(PRINT_A, ANIMATE_A, AA_length, color, pic=0); 
//         //     break;
//         // case 11:
//         //     PROMPT(PRINT_B, ANIMATE_B, AB_length, color, pic=0); 
//         //     break;
//         // case 12:
//         //     PROMPT(PRINT_C, ANIMATE_C, AC_length, color, pic=0); 
//         //     break;
//         // case 13:
//         //     PROMPT(PRINT_D, ANIMATE_D, AD_length, color, pic=0); 
//         //     break;
//         // case 14:
//         //     PROMPT(PRINT_E, ANIMATE_E, AE_length, color, pic=0); 
//         //     break;
//         // case 15:
//         //     PROMPT(PRINT_F, ANIMATE_F, AF_length, color, pic=0); 
//         //     break;
//         // case 16:
//         //     PROMPT(PRINT_G, ANIMATE_G, AG_length, color, pic=0); 
//         //     break;
//         // case 17:
//         //     PROMPT(PRINT_H, ANIMATE_H, AH_length, color, pic=0); 
//         //     break;
//         // case 18:
//         //     PROMPT(PRINT_I, ANIMATE_I, AI_length, color, pic=0); 
//         //     break;
//         // case 19:
//         //     PROMPT(PRINT_J, ANIMATE_J, AJ_length, color, pic=0); 
//         //     break;
//         // case 20:
//         //     PROMPT(PRINT_K, ANIMATE_K, AK_length, color, pic=0); 
//         //     break;
//         // case 21:
//         //     PROMPT(PRINT_L, ANIMATE_L, AL_length, color, pic=0); 
//         //     break;
//         // case 22:
//         //     PROMPT(PRINT_M, ANIMATE_M, AM_length, color, pic=0); 
//         //     break;
//         // case 23:
//         //     PROMPT(PRINT_N, ANIMATE_N, AN_length, color, pic=0); 
//         //     break;
//         // case 24:
//         //     PROMPT(PRINT_O, ANIMATE_O, AO_length, color, pic=0); 
//         //     break;
//         // case 25:
//         //     PROMPT(PRINT_P, ANIMATE_P, AP_length, color, pic=0); 
//         //     break;
//         // case 26:
//         //     PROMPT(PRINT_Q, ANIMATE_Q, AQ_length, color, pic=0); 
//         //     break;
//         // case 27:
//         //     PROMPT(PRINT_R, ANIMATE_R, AR_length, color, pic=0); 
//         //     break;
//         // case 28:
//         //     PROMPT(PRINT_S, ANIMATE_S, AS_length, color, pic=0); 
//         //     break;
//         // case 29:
//         //     PROMPT(PRINT_T, ANIMATE_T, AT_length, color, pic=0); 
//         //     break;
//         // case 30:
//         //     PROMPT(PRINT_U, ANIMATE_U, AU_length, color, pic=0); 
//         //     break;
//         // case 31:
//         //     PROMPT(PRINT_V, ANIMATE_V, AV_length, color, pic=0); 
//         //     break;
//         // case 32:
//         //     PROMPT(PRINT_W, ANIMATE_W, AW_length, color, pic=0); 
//         //     break;
//         // case 33:
//         //     PROMPT(PRINT_X, ANIMATE_X, AX_length, color, pic=0); 
//         //     break;
//         // case 34:
//         //     PROMPT(PRINT_Y, ANIMATE_Y, AY_length, color, pic=0); 
//         //     break;
//         // case 35:
//         //     PROMPT(PRINT_Z, ANIMATE_Z, AZ_length, color, pic=0); 
//         //     break;
//         // case 36:
//         //     PROMPT(PRINT_a, ANIMATE_a, Aa_length, color, pic=0); 
//         //     break;
//         // case 37:
//         //     PROMPT(PRINT_b, ANIMATE_b, Ab_length, color, pic=0); 
//         //     break;
//         // case 38:
//         //     PROMPT(PRINT_c, ANIMATE_c, Ac_length, color, pic=0); 
//         //     break;
//         // case 39:
//         //     PROMPT(PRINT_d, ANIMATE_d, Ad_length, color, pic=0); 
//         //     break;
//         // case 40:
//         //     PROMPT(PRINT_e, ANIMATE_e, Ae_length, color, pic=0); 
//         //     break;
//         // case 41:
//         //     PROMPT(PRINT_f, ANIMATE_f, Af_length, color, pic=0); 
//         //     break;
//         // case 42:
//         //     PROMPT(PRINT_g, ANIMATE_g, Ag_length, color, pic=0); 
//         //     break;
//         // case 43:
//         //     PROMPT(PRINT_h, ANIMATE_h, Ah_length, color, pic=0); 
//         //     break;
//         // case 44:
//         //     PROMPT(PRINT_i, ANIMATE_i, Ai_length, color, pic=0); 
//         //     break;
//         // case 45:
//         //     PROMPT(PRINT_j, ANIMATE_j, Aj_length, color, pic=0); 
//         //     break;
//         // case 46:
//         //     PROMPT(PRINT_k, ANIMATE_k, Ak_length, color, pic=0); 
//         //     break;
//         // case 47:
//         //     PROMPT(PRINT_l, ANIMATE_l, Al_length, color, pic=0); 
//         //     break;
//         // case 48:
//         //     PROMPT(PRINT_m, ANIMATE_m, Am_length, color, pic=0); 
//         //     break;
//         // case 49:
//         //     PROMPT(PRINT_n, ANIMATE_n, An_length, color, pic=0); 
//         //     break;
//         // case 50:
//         //     PROMPT(PRINT_o, ANIMATE_o, Ao_length, color, pic=0); 
//         //     break;
//         // case 51:
//         //     PROMPT(PRINT_p, ANIMATE_p, Ap_length, color, pic=0); 
//         //     break;
//         // case 52:
//         //     PROMPT(PRINT_q, ANIMATE_q, Aq_length, color, pic=0); 
//         //     break;
//         // case 53:
//         //     PROMPT(PRINT_r, ANIMATE_r, Ar_length, color, pic=0); 
//         //     break;
//         // case 54:
//         //     PROMPT(PRINT_s, ANIMATE_s, As_length, color, pic=0); 
//         //     break;
//         // case 55:
//         //     PROMPT(PRINT_tl, ANIMATE_tl, Atl_length, color, pic=0); 
//         //     break;
//         // case 56:
//         //     PROMPT(PRINT_u, ANIMATE_u, Au_length, color, pic=0); 
//         //     break;
//         // case 57:
//         //     PROMPT(PRINT_v, ANIMATE_v, Av_length, color, pic=0); 
//         //     break;
//         // case 58:
//         //     PROMPT(PRINT_w, ANIMATE_w, Aw_length, color, pic=0); 
//         //     break;
//         // case 59:
//         //     PROMPT(PRINT_x, ANIMATE_x, Ax_length, color, pic=0); 
//         //     break;
//         // case 60:
//         //     PROMPT(PRINT_y, ANIMATE_y, Ay_length, color, pic=0); 
//         //     break;
//         // case 61:
//         //     PROMPT(PRINT_z, ANIMATE_z, Az_length, color, pic=0); 
//         //     break;
//         // case 62:
//         //     PROMPT(apple, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 63:
//         //     PROMPT(banana, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 64:
//         //     PROMPT(chair, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 65:
//         //     PROMPT(door, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 66:
//         //     PROMPT(envelope, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 67:
//         //     PROMPT(fish, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 68:
//         //     PROMPT(giraffe, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 69:
//         //     PROMPT(hand, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 70:
//         //     PROMPT(ice_cream, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 71:
//         //     PROMPT(jacket, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 72:
//         //     PROMPT(key, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 73:
//         //     PROMPT(light_bulb, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 74:
//         //     PROMPT(mountain, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 75:
//         //     PROMPT(necklace, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 76:
//         //     PROMPT(octopus, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 77:
//         //     PROMPT(pencil, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 78:
//         //     PROMPT(queen, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 79:
//         //     PROMPT(rainbow, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 80:
//         //     PROMPT(snowflake, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 81:
//         //     PROMPT(table, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 82:
//         //     PROMPT(umbrella, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 83:
//         //     PROMPT(van, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 84:
//         //     PROMPT(water, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 85:
//         //     PROMPT(axe, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 86:
//         //     PROMPT(yoyo, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//         // case 87:
//         //     PROMPT(zebra, ANIMATE_z, Az_length, color, pic=1); 
//         //     break;
//     }
// }