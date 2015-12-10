#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"
#include "init.h"
#include "peripherals.h"



void InitDevice(){   
    count = 0x01;
    
    // Set the internal oscillator to 64MHz
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    
    // Initialize global variables to 0
    heartbeatCount = 0;
    buttonWasPressed = 0;
    
    
    
    
    
    ANCON0 = ANCON1 = 0x00;
    
    TRISA = 0b00111111; //chip alive, heartbeat ->output, battery -> input
    LATA = 0x00;
    
    TRISB = 0b00011101; //backlight, hblink, vblink, error diode -> output,       turn off, canrx, cantx -> inputs                  (block input?)
    LATB = 0x00;
    
    TRISC = 0x00; // Engine output
    LATC = 0x00;
    
    
    
    MAP_HEARTBEAT = 0; 
    MAP_BRAKE = 0;
    MAP_BACKLIGHT = 0; 
    MAP_V_BLINK = 0;
    MAP_H_BLINK = 0;
    MAP_DIRECTION = 0;
    MAP_SAFETYPIN = 0;
    MAP_ACCELERATOR = 0;

    TEMP_MAP_HEARTBEAT = 0;
    TEMP_MAP_BRAKE = 0;
    TEMP_MAP_BACKLIGHT = 0;
    TEMP_MAP_V_BLINK = 0;
    TEMP_MAP_H_BLINK = 0;
    TEMP_MAP_DIRECTION = 0;
    TEMP_MAP_SAFETYPIN = 0;
    TEMP_MAP_ACCELERATOR = 0;

    MAP_BATTERYSTATUS = 0;
    MAP_VELOCITY = 0; 
    MAP_HEARTBEAT = 0;
    


}