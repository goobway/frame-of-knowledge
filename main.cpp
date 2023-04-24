#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
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
string prompt_selection(unsigned char p_num){  
    string result;   
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

            result = "0";
            
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

            result = "A_upper";
            
            break;
        case 11:
            myDisplay.textDisplay("You will write the letter B.");
            static_image(PRINT_B, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (B)anana.");
            static_image(banana, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter B.");
            animated_image(ANIMATE_B, AB_length, color);
            usleep(1000000);

            result = "B_upper";
            
            break;
        case 12:
            myDisplay.textDisplay("You will write the letter C.");
            static_image(PRINT_C, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (C)hair.");
            static_image(chair, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter C.");
            animated_image(ANIMATE_C, AC_length, color);
            usleep(1000000);

            result = "C_upper";
            
            break;
        case 13:
            myDisplay.textDisplay("You will write the letter D.");
            static_image(PRINT_D, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (D)oor.");
            static_image(door, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter D.");
            animated_image(ANIMATE_D, AD_length, color);
            usleep(1000000);

            result = "D_upper";
            
            break;
        case 14:
            myDisplay.textDisplay("You will write the letter E.");
            static_image(PRINT_E, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is an (E)nvelope.");
            static_image(envelope, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter E.");
            animated_image(ANIMATE_E, AE_length, color);
            usleep(1000000);

            result = "E_upper";
            
            break;
        case 15:
            myDisplay.textDisplay("You will write the letter F.");
            static_image(PRINT_F, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (F)ish.");
            static_image(fish, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter F.");
            animated_image(ANIMATE_F, AF_length, color);
            usleep(1000000);

            result = "F_upper";
            
            break;
        case 16:
            myDisplay.textDisplay("You will write the letter G.");
            static_image(PRINT_G, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (G)iraffe.");
            static_image(giraffe, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter G.");
            animated_image(ANIMATE_G, AG_length, color);
            usleep(1000000);

            result = "G_upper";
            
            break;
        case 17:
            myDisplay.textDisplay("You will write the letter H.");
            static_image(PRINT_H, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (H)and.");
            static_image(hand, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter H.");
            animated_image(ANIMATE_H, AH_length, color);
            usleep(1000000);

            result = "H_upper";
            
            break;
        case 18:
            myDisplay.textDisplay("You will write the letter I.");
            static_image(PRINT_I, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is (I)ce Cream.");
            static_image(ice_cream, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter I.");
            animated_image(ANIMATE_I, AI_length, color);
            usleep(1000000);

            result = "I_upper";
            
            break;
        case 19:
            myDisplay.textDisplay("You will write the letter J.");
            static_image(PRINT_J, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (J)acket.");
            static_image(jacket, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter J.");
            animated_image(ANIMATE_J, AJ_length, color);
            usleep(1000000);

            result = "J_upper";
            
            break;
        case 20:
            myDisplay.textDisplay("You will write the letter K.");
            static_image(PRINT_K, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (K)ey.");
            static_image(key, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter K.");
            animated_image(ANIMATE_K, AK_length, color);
            usleep(1000000);

            result = "K_upper";
            
            break;
        case 21:
            myDisplay.textDisplay("You will write the letter L.");
            static_image(PRINT_L, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (L)ight bulb.");
            static_image(light_bulb, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter L.");
            animated_image(ANIMATE_L, AL_length, color);
            usleep(1000000);

            result = "L_upper";
            
            break;
        case 22:
            myDisplay.textDisplay("You will write the letter M.");
            static_image(PRINT_M, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (M)ountain.");
            static_image(mountain, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter M.");
            animated_image(ANIMATE_M, AM_length, color);
            usleep(1000000);

            result = "M_upper";
            
            break;
        case 23:
            myDisplay.textDisplay("You will write the letter N.");
            static_image(PRINT_N, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (N)ecklace.");
            static_image(necklace, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter N.");
            animated_image(ANIMATE_N, AN_length, color);
            usleep(1000000);

            result = "N_upper";
            
            break;
        case 24:
            myDisplay.textDisplay("You will write the letter O.");
            static_image(PRINT_O, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is an (O)ctopus.");
            static_image(octopus, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter O.");
            animated_image(ANIMATE_O, AO_length, color);
            usleep(1000000);

            result = "O_upper";
            
            break;
        case 25:
            myDisplay.textDisplay("You will write the letter P.");
            static_image(PRINT_P, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (P)encil.");
            static_image(pencil, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter P.");
            animated_image(ANIMATE_P, AP_length, color);
            usleep(1000000);

            result = "P_upper";
            
            break;
        case 26:
            myDisplay.textDisplay("You will write the letter Q.");
            static_image(PRINT_Q, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (Q)ueen.");
            static_image(queen, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter Q.");
            animated_image(ANIMATE_Q, AQ_length, color);
            usleep(1000000);

            result = "Q_upper";
            
            break;
        case 27:
            myDisplay.textDisplay("You will write the letter R.");
            static_image(PRINT_R, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (R)ainbow.");
            static_image(rainbow, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter R.");
            animated_image(ANIMATE_R, AR_length, color);
            usleep(1000000);

            result = "R_upper";
            
            break;
        case 28:
            myDisplay.textDisplay("You will write the letter S.");
            static_image(PRINT_S, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (S)nowflake.");
            static_image(snowflake, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter S.");
            animated_image(ANIMATE_S, AS_length, color);
            usleep(1000000);

            result = "S_upper";
            
            break;
        case 29:
            myDisplay.textDisplay("You will write the letter T.");
            static_image(PRINT_T, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (T)able.");
            static_image(table, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter T.");
            animated_image(ANIMATE_T, AT_length, color);
            usleep(1000000);

            result = "T_upper";
            
            break;
        case 30:
            myDisplay.textDisplay("You will write the letter U.");
            static_image(PRINT_U, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is an (U)mbrella.");
            static_image(umbrella, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter U.");
            animated_image(ANIMATE_U, AU_length, color);
            usleep(1000000);

            result = "U_upper";
            
            break;
        case 31:
            myDisplay.textDisplay("You will write the letter V.");
            static_image(PRINT_V, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (V)an.");
            static_image(van, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter V.");
            animated_image(ANIMATE_V, AV_length, color);
            usleep(1000000);

            result = "V_upper";
            
            break;
        case 32:
            myDisplay.textDisplay("You will write the letter W.");
            static_image(PRINT_W, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is (W)ater.");
            static_image(water, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter W.");
            animated_image(ANIMATE_W, AW_length, color);
            usleep(1000000);

            result = "W_upper";
            
            break;
        case 33:
            myDisplay.textDisplay("You will write the letter X.");
            static_image(PRINT_X, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is an a(X)e.");
            static_image(axe, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter X.");
            animated_image(ANIMATE_X, AX_length, color);
            usleep(1000000);

            result = "X_upper";
            
            break;
        case 34:
            myDisplay.textDisplay("You will write the letter Y.");
            static_image(PRINT_Y, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (Y)oyo.");
            static_image(yoyo, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter Y.");
            animated_image(ANIMATE_Y, AY_length, color);
            usleep(1000000);

            result = "Y_upper";
            
            break;
        case 35:
            myDisplay.textDisplay("You will write the letter Z.");
            static_image(PRINT_Z, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is a (Z)ebra.");
            static_image(zebra, color);
            usleep(3000000);
            clear_matrix();
            myDisplay.clearDisplay();

            myDisplay.textDisplay("This is how to write the");
            myDisplay.textDisplay("letter Z.");
            animated_image(ANIMATE_Z, AZ_length, color);
            usleep(1000000);

            result = "Z_upper";
            
            break;
    }

    return result;
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
            return 2*i;
        // } else if (x2 == 1){
        //     return 31 - 2*i;
        }
    }

    return 32;
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
            return 2*i;
        // } else if (y2 == 1){
        //     return 31 - 2*i;
        } 
    }

    return 32;
}

// test function for checking collectors
void detect(void){
    unsigned int i, val1;

    for (i=0; i<16; i++){ 
        val1 = digitalRead(100+i);
        if (val1 == 0 && i == 8){
            cout << "collector: " << 100+i << "\n";
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

    unsigned char prompts[] = {14, 10};  // prompts that will be shown
    unsigned char pos = 0;  // control position in prompts array

    int x_coord;  // tracks x position of finger
    int y_coord;  // tracks y position of finger
    int location;  // used to store location on the LED matrix
    int result;  // return ML guess - line position
    int attempts;  // track number of attempts on a given prompt
    int line;  // keepts track of line number in class file
    string ml_guess;  // save tthe guess of the ML model
    string expected;  // compare against the ML model
    ifstream myfile;  // load class list into this


    while (1){       
        // testing for Maia

        // detect();

        // continue;

        x_coord = get_x();
        y_coord = 0;
        color = 5;
 
        // switch  or to and on the first conditional  || (y_coord < 32)
        if ((x_coord < 32)){
            if (x_coord < 16){
                if(y_coord%2 == 0){
                    location = 16*y_coord + x_coord;
                } else {
                    location = (16*y_coord) + (15 - x_coord);
                }
            } else {
                if(y_coord%2 == 0){
                    location = (512 + 16*y_coord) + (x_coord - 16);
                } else {
                    location = (512 + 16*y_coord) + (31 - x_coord);
                }
            }
            if (USED_MATRIX[x_coord][y_coord] == 0){
                USED_MATRIX[x_coord][y_coord] = 1;
                update_matrix(location, color);
            }

        }


        continue;

        // end of Maia's testing


        // select a random color
        color = rand() % 7;

        // show student given prompt
        expected = prompt_selection(prompts[pos]);

        // tells the user they can now draw on the matrix
        myDisplay.clearDisplay();
        myDisplay.textDisplay("Try it yourself!");
        myDisplay.textDisplay(" ");
        myDisplay.textDisplay("Use the buttons to select");
        myDisplay.textDisplay("different colors!");

        submit = 0;  // reset submit if user pressed it by accident
        attempts = 0;  // reset the number of attempts the user has
        // allows user to draw on the matrix
        while(attempts < 3){
            if (submit){
                // for now break out of the loop
                submit = 0;

                myDisplay.clearDisplay();
                myDisplay.textDisplay("Submission accepted!");

                result = classify_image(USED_MATRIX);

                line = 0;
                myfile.open("/home/sdp19/tflite/models/classification/class_list.txt");
                while (line <= result){
                    getline(myfile, ml_guess);   
                    line++;
                }   
                myfile.close();

                // PUT SERVER CODE HERE

                if (ml_guess == expected){
                    myDisplay.textDisplay(" ");
                    myDisplay.textDisplay("Correct!");
                    myDisplay.textDisplay(" ");
                    myDisplay.textDisplay("Loading next prompt...");
                    usleep(3000000);
                    clear_matrix();
                    clear_int();
                    pos++;
                    break;
                } else {
                    myDisplay.textDisplay(" ");
                    myDisplay.textDisplay("Try again!");
                    usleep(3000000);
                    clear_matrix();
                    clear_int();
                    myDisplay.clearDisplay();
                    myDisplay.textDisplay("Try it yourself!");
                    myDisplay.textDisplay(" ");
                    myDisplay.textDisplay("Use the buttons to select");
                    myDisplay.textDisplay("different colors!");
                    
                    attempts++;
                }
            }

            x_coord = get_x();
            y_coord = get_y();

            // switch  or to and on the first conditional
            if ((x_coord < 32) || (y_coord < 32)){
                if (y_coord < 16){
                    if(x_coord%2 == 0){
                        location = 16*x_coord + y_coord;
                    } else {
                        location = (16*x_coord) + (15 - y_coord);
                    }
                } else {
                    if(x_coord%2 == 0){
                        location = (512 + 16*x_coord) + (y_coord - 16);
                    } else {
                        location = (512 + 16*x_coord) + (31 - y_coord);
                    }
                }
                update_matrix(location, color);
                if (USED_MATRIX[x_coord][y_coord] == 0){
                    USED_MATRIX[x_coord][y_coord] = 1;
                }
            }
        }

        pos++;

    }

    return 0;
}