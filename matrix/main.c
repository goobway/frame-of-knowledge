#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <wiringPi.h>
#include <mcp23017.h>

#include <signal.h>
#include "matrix.h"

void matrix_clear(void);
void deinitalize_matrix(void);


void int_handler(int sig){
    printf("\n");
    matrix_clear();
    digitalWrite(108, LOW);
    exit(0);
}


int main(void){ 
    signal(SIGINT, int_handler);
    wiringPiSetup();
    mcp23017Setup(100, 0x20);
    pinMode(108, OUTPUT);
    // pinMode(5, OUTPUT);
    
    initialize_matrix();

    // draw_A();
    // animate_A();
    test();

    while(1){
        

        digitalWrite(108, HIGH);
        delay(100);
        digitalWrite(108, LOW);
        delay(100);

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