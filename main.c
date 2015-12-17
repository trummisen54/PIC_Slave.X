#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"
#include "init.h"
#include "peripherals.h"

int main(void){
    
    
    InitDevice();
    CANSetup();
    setup_Interrupt();
    
    heartBeatCounter = 0;
    FIRST_SEND = 1;
    interruptCounter = 0;
    
    CHIP_ALIVE_DIODE_PIN = 1;
    ERROR_DIODE_PIN = 0;
    
    while(1){
        

        if(ECAN_Receive()){
            FIRST_SEND = 0;
            HEARTBEAT_DIODE_PIN = 1;
            unZipCAN();
            if(TEMP_MAP_HEARTBEAT == 1){
                heartBeatCounter = 0;
            }
            
        }
        
        if(heartBeatCounter > 500000){
            danger();
        }
        
        checkBrake();
        checkBacklight();
        checkV_blink();
        checkH_blink();
        checkDirection();
        checkSafetyPin();
        checkAccelerator();
              
  
        
        
        updateInputs();
            
        ECAN_Transmit(0x32,0xC0, 0x08,
                MAP_BATTERYSTATUS,
                MAP_VELOCITY,
                1, // heartbeat always one
                temp_D3,
                temp_D4,
                temp_D5,
                temp_D6,
                temp_D7);
        

        Delay(10);

    }
    return 0;
}


void interrupt ISR(){
    
    interruptCounter++;
   
    if(IRXIF){// CAN Bus Error Message Received Interrupt Flag bit  
        if(TXB0CONbits.TXERR){ // wrong in send, maybe (TXREQ not cleared)
            ERROR_DIODE_PIN = 1;
    
        }
    }
    
    
    
    
    if(TMR0IF == 1){
        interruptCounter++;
        TMR0IF = 0;
    }
     
    
    
    
    
    
    
    
    /*
    if(!FIRST_SEND){
        if(TMR0IF == 1){
            heartBeatCounter++;
            TMR0IF = 0;
        }
    }
    */
}

