#include <iostream>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <wiringPi.h>
#include <mcp23017.h>

#include <signal.h>
#include "matrix.hpp"

#define CLEAR 29

void matrix_clear(void);
void deinitalize_matrix(void);


void int_handler(int sig){
    printf("\n");
    matrix_clear();
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
    Initialize the four micro controllers.
    h1/h1 - 
    */
    mcp23017Setup(100, 0x20);
    mcp23017Setup(200, 0x21);
    mcp23017Setup(300, 0x22);
    mcp23017Setup(400, 0x23);

    // Set all exapnders to read input values.
    int expander;
    int pin;
    int pin_start = 100;
    for (expander=1; expander<5; expander++){
        pin_start = 100*expander;
        for (pin=pin_start; pin < pin_start+16; pin++){
            pinMode(pin, OUTPUT);
        } 
    }

    pinMode(CLEAR, INPUT);
    digitalWrite(CLEAR, HIGH);
        
    /*
    Allows data to be sent to the matrix.
    - Found in matrix.cpp
    */
    initialize_matrix();





    // draw_A();
    // animate_A();
    // draw_A();

    // int j;
    // for (j=100; j<116; j++){
    //     digitalWrite(j, HIGH);
    // }

    // int j;
    // for (j=100; j<116; j++){
    //     digitalWrite(j, LOW);
    // }

     
    int read;
    while(1){
        read = digitalRead(CLEAR);
        printf("%d\n", read);
        // if (read == 0){
        //     printf("%d\n", read);
        // }
        // int read = digitalRead(107);
        // printf("%d\n", read);

        // digitalWrite(108, HIGH);
        // delay(100);
        // digitalWrite(108, LOW);
        // delay(100);

    }
   
    
    deinitalize_matrix();













    // // clock_t start, end;
    
    

    

    // pinMode(4, INPUT);
    // pinMode(5, OUTPUT);

    // while (1) {
    //     // testing for emitters
    //     digitalWrite(5, HIGH);
    //     delay(0.026);
    //     digitalWrite(5, LOW);

    //      if (digitalRead(4) == 0) {
    //         printf("detecting\n");
    //      } else {
    //         printf("gimme IR signal\n");
    //      }



        // start  = clock();
        // digitalWrite(5, HIGH);
        
        // end = clock();

        // double duration = (end-start)/CLOCKS_PER_SEC;
        

        // digitalWrite(5, LOW);
        
        
        // printf("%f\n", duration);
    //}

    return 0;
}