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

void danger(){
    while(1){
        HEARTBEAT_DIODE_PIN = 0;
        ERROR_DIODE_PIN = 1;
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
