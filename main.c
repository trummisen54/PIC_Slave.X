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
    
    CHIP_ALIVE_DIODE_PIN = 1;
    
    while(1){
        

        if(ECAN_Receive()){
            unZipCAN();
        }
        
        checkHeartbeat();
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
                MAP_HEARTBEAT,
                temp_D3,
                temp_D4,
                temp_D5,
                temp_D6,
                temp_D7);
        

        Delay(100);

    }
    return 0;
}


void interrupt ISR(){
   
    if(IRXIF){// CAN Bus Error Message Received Interrupt Flag bit
        
        if(TXB0CONbits.TXERR){ // wrong in send, maybe (TXREQ not cleared)
            while(1);
    
        }
    }
}

