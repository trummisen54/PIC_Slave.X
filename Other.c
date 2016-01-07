#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"
#include "init.h"
#include "peripherals.h"


void Delay(unsigned int count)
{
    // Countdown until equal to zero and then return
    while(count--);
}

void danger(int errorCode){
    
    //turn off interrupts
    INTCONbits.GIEH = 0; //high priority interrupts
    INTCONbits.GIEL = 0; //low priority interrupts

    HEARTBEAT_DIODE_PIN = 0;
    TURNOFF_OUT = 1; //motor stops
    ENABLE_MOTOR_OUT = 0;
    
    while(1){
        for(int i = 0; i< errorCode; i++){
            ERROR_DIODE_PIN = 1;
            Delay(ONE_MS * 500);
            ERROR_DIODE_PIN = 0;
            Delay(ONE_MS * 500);
            
        }
        
        Delay(ONE_MS * 2000);
        
        if(CAN_ERRORBIT == 1){
            for(int i = 0; i< CAN_ERRORCODE; i++){
                ERROR_DIODE_PIN = 1;
                Delay(ONE_MS * 500);
                ERROR_DIODE_PIN = 0;
                Delay(ONE_MS * 500);
            
            }
        }
        
        Delay(ONE_MS * 2000);
    }
    
}

/*
void heartBeat(){
    if(TEMP_MAP_HEARTBEAT == 0){
        MAP_HEARTBEAT = 0;
        if(heartBeatCounter > 2){ //500000 = 2sec
            danger();       //if heartbeat has lost connection. DANGER!!
        }
    }
    else{
        
        
        MAP_HEARTBEAT = 1;      // Send heartbeat
        
        TEMP_MAP_HEARTBEAT = 0; // Reset receive heartbeat
        heartBeatCounter = 0;
    }
}
*/
