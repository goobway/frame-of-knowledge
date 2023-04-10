#include <iostream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <mcp23017.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>

#include "display.hpp"
#include "numbers.hpp"
#include "upper.hpp"
#include "lower.hpp"
#include "sketches.hpp"

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
unsigned char color = 10;
unsigned char submit = 0;

void matrix_clear(void);
void deinitalize_matrix(void);
void pick_prompt(unsigned char p_num);


void int_handler(int sig){
    printf("\n");
    
    clear_OLED();
    clear_matrix();
    deinitalize_matrix();
    
    exit(0);
}

unsigned int detect(void){
    unsigned int i;
    unsigned int val1, val2, val3, val4;

    for (i=0; i<16; i++){
        // if (i < 8){
        //     val1 = digitalRead(100+i+8);
        //     val2 = digitalRead(200+i+8);
        //     val3 = digitalRead(300+i+8);
        //     val4 = digitalRead(400+i+8);
        // } else {
        //     val1 = digitalRead(100+i-8);
        //     val2 = digitalRead(200+i-8);
        //     val3 = digitalRead(300+i+8);
        //     val4 = digitalRead(400+i+8);
        // }
        
        val1 = digitalRead(100+i);
        val2 = digitalRead(200+i);
        val3 = digitalRead(300+i);
        val4 = digitalRead(400+i);
        if (val1 == 0){
            cout << "collector: " << 100+i << "\n";
        }
        if (val2 == 0){
            cout << "collector: " << 200+i << "\n";
        }
        if (val3 == 0){
            cout << "collector: " << 300+i << "\n";
        }
        if (val4 == 0){
            cout << "collector: " << 400+i << "\n";
        }

        // if (val1 == 1){
        //     return 31-2*i;
        // }
        // if (val2 == 1){
        //     return 2*i;
        // } 
        
        // if (i == 15){
        //     return 33;
        // }
    
    }

}

void set_clear(){
    clear_matrix();
    for (int y=0; y<32; y++){
        for (int x=0; x<32; x++){
            if (USED_MATRIX[x][y] == 1){
                USED_MATRIX[x][y] = 0;
            }
        }
    }
}

void set_submit(){
    submit = 1;
}

void set_red(){
    color = 0;
}

void set_orange(){
    color = 1;
}

void set_yellow(){
    color = 2;
}

void set_green(){
    color = 3;
}

void set_blue(){
    color = 4;
}

void set_purple(){
    color = 5;
}

void set_pink(){
    color = 6;
}


int main(void){ 
    // Setup handler for CTRL-C.
    signal(SIGINT, int_handler);

    // GPIO control setup.
    wiringPiSetup();

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

    // Set up button control for the system
    unsigned int buttons[] = {CLEAR, SUBMIT, RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, PINK};
    unsigned int i;
    for (i=0; i<9; i++){
        pinMode(buttons[i], INPUT);
        pullUpDnControl(buttons[i], PUD_UP);
    }


    // Initialize OLED and display welcome message
    welcome();
        
    // Allows data to be sent to the matrix.
    initialize_matrix();

    // Color select interrupts
    wiringPiISR(CLEAR, INT_EDGE_FALLING, set_clear);
    wiringPiISR(SUBMIT, INT_EDGE_FALLING, set_submit);
    wiringPiISR(RED, INT_EDGE_FALLING, set_red);
    wiringPiISR(ORANGE, INT_EDGE_FALLING, set_orange);
    wiringPiISR(YELLOW, INT_EDGE_FALLING, set_yellow);
    wiringPiISR(BLUE, INT_EDGE_FALLING, set_blue);
    wiringPiISR(GREEN, INT_EDGE_FALLING, set_green);
    wiringPiISR(PURPLE, INT_EDGE_FALLING, set_purple);
    wiringPiISR(PINK, INT_EDGE_FALLING, set_pink);

    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term);

    unsigned char prompts[] = {42, 2, 11, 66, 42};
    unsigned char p_num;
    unsigned char pos = 0;
    int location;
    int x = 16;
    int y = 16;
    int k = 0;
    // unsigned char penUp = 1;

    int row;
    color = 10;
    unsigned char test_c = 0;
    while(1){
        p_num = prompts[pos];
        detect();

        // row = detect();
        // cout << row;
        // if (row < 33){
        //     if (row < 16){
        //         if(x%2 == 0){
        //             location = 16*x + row;
        //         } else {
        //             location = (16*x) + (15 - row);
        //         }
        //     } else {
        //         if(x%2 == 0){
        //             location = (512 + 16*x) + (row - 16);
        //         } else {
        //             location = (512 + 16*x) + (31 - row);
        //         }
        //     }
        //     update_matrix(location, test_c);
        // }
        cout << "\n";
        usleep(1000000);

        continue;

        // wait for color selection
        SC_PROMPT();
        while (color > 6);

        // picks corresponding prompt from given array
        pick_prompt(p_num);

        while (1){
            // gets x and y coords
            // detect();

            if (x < 0){
                x = 0;
            } else if (x>31){
                x = 31;
            }

            if (y < 0){
                y = 0;
            } else if (y>31){
                y = 31;
            }

            if (y < 16){
                if(x%2 == 0){
                    location = 16*x + y;
                } else {
                    location = (16*x) + (15 - y);
                }
                } else {
                if(x%2 == 0){
                    location = (512 + 16*x) + (y - 16);
                } else {
                    location = (512 + 16*x) + (31 - y);
                }
            }

            if (USED_MATRIX[x][y] != 1){
                USED_MATRIX[x][y] = 1;
                update_matrix(location, color);
            }

            // if (penUp == 1){
            //     // blink       
            //     update_matrix(location, color);
                

            // } else {
            //     if (USED_MATRIX[x][y] != 1){
            //         USED_MATRIX[x][y] = 1;
            //         update_matrix(location, color);
            //     }
            // }

            // keyboard input
            switch(k = getchar()){
                case 'w':
                    y--;
                    break;
                case 'a':
                    x--;
                    break;
                case 's':
                    y++;
                    break;
                case 'd':
                    x++;
                    break;
                // case 'p':
                //     penUp = !penUp;
                //     break;
            }


            

            

            if (submit == 1){
                // do stuff with ML
                break;
            } 
            // else {
            //     clear_matrix();
            //     for (y=0; y<32; y++){
            //         for (x=0; x<32; x++){
            //             if (USED_MATRIX[x][y] == 1){
            //                 USED_MATRIX[x][y] = 0;
            //             }
            //         }
            //     }
            // }
            
        }
        

        // clear the OLED before next prompt
        clear_OLED();
        set_clear();
        pos++;
        color = 10;
        submit = 0;
        x = 16;
        y = 16;
        if (pos > 4){
            break;
        }

    }

    return 0;
}


void pick_prompt(unsigned char p_num){
    // go through the given prompts 
    unsigned int pic;       
    switch(p_num){
        case 0:
            PROMPT(PRINT_0, ANIMATE_0, A0_length, color, pic=0);
            break;
        case 1:
            PROMPT(PRINT_1, ANIMATE_1, A1_length, color, pic=0);
            break;
        case 2:
            PROMPT(PRINT_2, ANIMATE_2, A2_length, color, pic=0);
            break;
        case 3:
            PROMPT(PRINT_3, ANIMATE_3, A3_length, color, pic=0);
            break;
        case 4:
            PROMPT(PRINT_4, ANIMATE_4, A4_length, color, pic=0);
            break;
        case 5:
            PROMPT(PRINT_5, ANIMATE_5, A5_length, color, pic=0);
            break;
        case 6:
            PROMPT(PRINT_6, ANIMATE_6, A6_length, color, pic=0);
            break;
        case 7:
            PROMPT(PRINT_7, ANIMATE_7, A7_length, color, pic=0);
            break;
        case 8:
            PROMPT(PRINT_8, ANIMATE_8, A8_length, color, pic=0);
            break;
        case 9:
            PROMPT(PRINT_9, ANIMATE_9, A9_length, color, pic=0);
            break;
        case 10:
            PROMPT(PRINT_A, ANIMATE_A, AA_length, color, pic=0); 
            break;
        case 11:
            PROMPT(PRINT_B, ANIMATE_B, AB_length, color, pic=0); 
            break;
        case 12:
            PROMPT(PRINT_C, ANIMATE_C, AC_length, color, pic=0); 
            break;
        case 13:
            PROMPT(PRINT_D, ANIMATE_D, AD_length, color, pic=0); 
            break;
        case 14:
            PROMPT(PRINT_E, ANIMATE_E, AE_length, color, pic=0); 
            break;
        case 15:
            PROMPT(PRINT_F, ANIMATE_F, AF_length, color, pic=0); 
            break;
        case 16:
            PROMPT(PRINT_G, ANIMATE_G, AG_length, color, pic=0); 
            break;
        case 17:
            PROMPT(PRINT_H, ANIMATE_H, AH_length, color, pic=0); 
            break;
        case 18:
            PROMPT(PRINT_I, ANIMATE_I, AI_length, color, pic=0); 
            break;
        case 19:
            PROMPT(PRINT_J, ANIMATE_J, AJ_length, color, pic=0); 
            break;
        case 20:
            PROMPT(PRINT_K, ANIMATE_K, AK_length, color, pic=0); 
            break;
        case 21:
            PROMPT(PRINT_L, ANIMATE_L, AL_length, color, pic=0); 
            break;
        case 22:
            PROMPT(PRINT_M, ANIMATE_M, AM_length, color, pic=0); 
            break;
        case 23:
            PROMPT(PRINT_N, ANIMATE_N, AN_length, color, pic=0); 
            break;
        case 24:
            PROMPT(PRINT_O, ANIMATE_O, AO_length, color, pic=0); 
            break;
        case 25:
            PROMPT(PRINT_P, ANIMATE_P, AP_length, color, pic=0); 
            break;
        case 26:
            PROMPT(PRINT_Q, ANIMATE_Q, AQ_length, color, pic=0); 
            break;
        case 27:
            PROMPT(PRINT_R, ANIMATE_R, AR_length, color, pic=0); 
            break;
        case 28:
            PROMPT(PRINT_S, ANIMATE_S, AS_length, color, pic=0); 
            break;
        case 29:
            PROMPT(PRINT_T, ANIMATE_T, AT_length, color, pic=0); 
            break;
        case 30:
            PROMPT(PRINT_U, ANIMATE_U, AU_length, color, pic=0); 
            break;
        case 31:
            PROMPT(PRINT_V, ANIMATE_V, AV_length, color, pic=0); 
            break;
        case 32:
            PROMPT(PRINT_W, ANIMATE_W, AW_length, color, pic=0); 
            break;
        case 33:
            PROMPT(PRINT_X, ANIMATE_X, AX_length, color, pic=0); 
            break;
        case 34:
            PROMPT(PRINT_Y, ANIMATE_Y, AY_length, color, pic=0); 
            break;
        case 35:
            PROMPT(PRINT_Z, ANIMATE_Z, AZ_length, color, pic=0); 
            break;
        case 36:
            PROMPT(PRINT_a, ANIMATE_a, Aa_length, color, pic=0); 
            break;
        case 37:
            PROMPT(PRINT_b, ANIMATE_b, Ab_length, color, pic=0); 
            break;
        case 38:
            PROMPT(PRINT_c, ANIMATE_c, Ac_length, color, pic=0); 
            break;
        case 39:
            PROMPT(PRINT_d, ANIMATE_d, Ad_length, color, pic=0); 
            break;
        case 40:
            PROMPT(PRINT_e, ANIMATE_e, Ae_length, color, pic=0); 
            break;
        case 41:
            PROMPT(PRINT_f, ANIMATE_f, Af_length, color, pic=0); 
            break;
        case 42:
            PROMPT(PRINT_g, ANIMATE_g, Ag_length, color, pic=0); 
            break;
        case 43:
            PROMPT(PRINT_h, ANIMATE_h, Ah_length, color, pic=0); 
            break;
        case 44:
            PROMPT(PRINT_i, ANIMATE_i, Ai_length, color, pic=0); 
            break;
        case 45:
            PROMPT(PRINT_j, ANIMATE_j, Aj_length, color, pic=0); 
            break;
        case 46:
            PROMPT(PRINT_k, ANIMATE_k, Ak_length, color, pic=0); 
            break;
        case 47:
            PROMPT(PRINT_l, ANIMATE_l, Al_length, color, pic=0); 
            break;
        case 48:
            PROMPT(PRINT_m, ANIMATE_m, Am_length, color, pic=0); 
            break;
        case 49:
            PROMPT(PRINT_n, ANIMATE_n, An_length, color, pic=0); 
            break;
        case 50:
            PROMPT(PRINT_o, ANIMATE_o, Ao_length, color, pic=0); 
            break;
        case 51:
            PROMPT(PRINT_p, ANIMATE_p, Ap_length, color, pic=0); 
            break;
        case 52:
            PROMPT(PRINT_q, ANIMATE_q, Aq_length, color, pic=0); 
            break;
        case 53:
            PROMPT(PRINT_r, ANIMATE_r, Ar_length, color, pic=0); 
            break;
        case 54:
            PROMPT(PRINT_s, ANIMATE_s, As_length, color, pic=0); 
            break;
        case 55:
            PROMPT(PRINT_tl, ANIMATE_tl, Atl_length, color, pic=0); 
            break;
        case 56:
            PROMPT(PRINT_u, ANIMATE_u, Au_length, color, pic=0); 
            break;
        case 57:
            PROMPT(PRINT_v, ANIMATE_v, Av_length, color, pic=0); 
            break;
        case 58:
            PROMPT(PRINT_w, ANIMATE_w, Aw_length, color, pic=0); 
            break;
        case 59:
            PROMPT(PRINT_x, ANIMATE_x, Ax_length, color, pic=0); 
            break;
        case 60:
            PROMPT(PRINT_y, ANIMATE_y, Ay_length, color, pic=0); 
            break;
        case 61:
            PROMPT(PRINT_z, ANIMATE_z, Az_length, color, pic=0); 
            break;
        case 62:
            PROMPT(apple, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 63:
            PROMPT(banana, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 64:
            PROMPT(chair, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 65:
            PROMPT(door, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 66:
            PROMPT(envelope, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 67:
            PROMPT(fish, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 68:
            PROMPT(giraffe, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 69:
            PROMPT(hand, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 70:
            PROMPT(ice_cream, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 71:
            PROMPT(jacket, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 72:
            PROMPT(key, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 73:
            PROMPT(light_bulb, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 74:
            PROMPT(mountain, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 75:
            PROMPT(necklace, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 76:
            PROMPT(octopus, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 77:
            PROMPT(pencil, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 78:
            PROMPT(queen, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 79:
            PROMPT(rainbow, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 80:
            PROMPT(snowflake, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 81:
            PROMPT(table, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 82:
            PROMPT(umbrella, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 83:
            PROMPT(van, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 84:
            PROMPT(water, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 85:
            PROMPT(axe, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 86:
            PROMPT(yoyo, ANIMATE_z, Az_length, color, pic=1); 
            break;
        case 87:
            PROMPT(zebra, ANIMATE_z, Az_length, color, pic=1); 
            break;
    }
}