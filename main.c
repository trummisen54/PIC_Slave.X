
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"


int main(void){
    
    
    InitDevice();
    CANSetup();
    
    LATCbits.LATC6 = 1;//chip alive indicator
    
    while(1){
        
        checkInputs();
        
        checkCAN();
        Delay(100);// good to have great delay! the program sends all the time.
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

