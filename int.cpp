#include <iostream>
using namespace std;

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>
#include <signal.h>

#define IODIRA      0x00
#define IPOLA       0x02
#define GPINTENA    0x04
#define DEFVALA     0x06
#define INTCONA     0x08
#define IOCONA       0x0A
#define GPPUA       0x0C
#define INTFA       0x0E
#define INTCAPA     0x10
#define GPIOA       0x12

int mcp0 = wiringPiI2CSetup(0x20);
volatile int intFlag = 0;


void mcp_interrupt(void){
    int val = wiringPiI2CReadReg8(mcp0, INTFA);
    cout << val << ": Button Pressed!\n";
    intFlag = 1;
    wiringPiI2CReadReg8(mcp0, INTCAPA);
}

int main(){
    wiringPiSetup();
    
    wiringPiI2CWriteReg8(mcp0, IODIRA, 0xFF);
    wiringPiI2CWriteReg8(mcp0, IPOLA, 0x00);
    wiringPiI2CWriteReg8(mcp0, GPINTENA, 0xFF);
    wiringPiI2CWriteReg8(mcp0, DEFVALA, 0xFF);
    wiringPiI2CWriteReg8(mcp0, INTCONA, 0xFF);
    wiringPiI2CWriteReg8(mcp0, IOCONA, 0x20);
    wiringPiI2CWriteReg8(mcp0, GPPUA, 0xFF);

    pinMode(7, INPUT);
    pullUpDnControl(7, PUD_UP);
    wiringPiISR(7, INT_EDGE_FALLING, mcp_interrupt);


    while (1){
        if (intFlag){
            
            
            
            intFlag = 0;
        }
    }

    

    return 0;
}