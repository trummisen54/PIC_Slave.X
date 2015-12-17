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
    
    
    
    
    TRISA = 0b00111111; //chip alive, heartbeat ->output, battery -> input
    ANCON0 = 0x01; // AN0 enabled
    ANCON1 = 0x00; //AN8-AN14 not enabled
    
    
    ADCON0 = 0x00;
    ADCON1 = 0x00;
    ADCON2 = 0x00; //set ADFM to 0, (fourth lower bits of ADRESL gives no resultbit))
    
    
    //HOW OFTEN
    ADCON2bits.ADFM=1; // Result format 1= Right justified
    ADCON2bits.ACQT=1; // Acquisition time 7 = 20TAD 2 = 4TAD 1=2TAD
    ADCON2bits.ADCS=2;
    
    
    
    LATA = 0x00;
    
    TRISB = 0b00011101; //backlight, hblink, vblink, error diode -> output,       turn off, canrx, cantx -> inputs                  (block input?)
    LATB = 0x00;
    
    TRISC = 0x00; // Engine output
    LATC = 0x00;
    
    
    
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
    
     
    
    //SYSTEM TIMER heartbeat
    T0CONbits.TMR0ON = 1; // Enable timer
    T0CONbits.T08BIT = 0; //16 bit
    T0CONbits.T0CS = 0; //not counter
    //T0CONbits.T0SE = 0;
    T0CONbits.PSA = 0; //enable prescaler
    T0CONbits.T0PS = 7; //111 -> 1000 0111
    
    
    /*
    //SYSTEM TIMER RFID
    T1CONbits.TMR1ON = 1; // Enable timer
    T1CONbits.RD16 = 1; //16 bit
    //T0CONbits.T0SE = 0;
    T1CONbits.PSA = 0;
    T1CONbits.T0PS = 7; //111 -> 1000 0111
    */
    

}

void setup_Interrupt(){
    RCONbits.IPEN = 1; //interrupt priority enable
    INTCONbits.GIEH = 1; //high priority interrupts
    INTCONbits.GIEL = 1; //low priority interrupts
    INTCONbits.TMR0IE = 1; //Enables the TMR0 overflow interrupt
    
    
}