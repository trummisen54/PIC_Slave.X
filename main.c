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
    interruptCounter = 0; //for testing
    
    CHIP_ALIVE_DIODE_PIN = 1;
    ERROR_DIODE_PIN = 0;
    
    while(1){
        

        if(ECAN_Receive()){
            FIRST_SEND = 0;
            HEARTBEAT_DIODE_PIN = 1;
            unZipCAN();
            if(TEMP_MAP_HEARTBEAT == 1){ //will always be one
                heartBeatCounter = 0;
            }
            
        }
        
        //testar lägga detta i interruptet istället... säkrare...
        //if(heartBeatCounter > 35){ // 20 works, 10 is to low
        //    danger();
        //}
        
        checkBrake();
        checkBacklight();
        checkV_blink();
        checkH_blink();
        checkDirection();
        checkSafetyPin();
        checkStop();
        checkAccelerator();
              
        
        
        updateInputs();
            
        ECAN_Transmit(0x32,0xC0, 0x08,
                0,//not used
                MAP_VELOCITY,
                0x01, // heartbeat always one
                MAP_BATTERYSTATUS & 0x00FF,
                (MAP_BATTERYSTATUS & 0xFF00) >> 8,
                temp_D5,
                temp_D6,
                temp_D7);
        

        Delay(ONE_MS * 5);

    }
    return 0;
}


void interrupt ISR(){
    
    //interruptCounter++;
   
    if(IRXIF){// CAN Bus Error Message Received Interrupt Flag bit  
        if(TXB0CONbits.TXERR){ // wrong in send, maybe (TXREQ not cleared)
            CAN_ERRORBIT = 1;
            
        }
        IRXIF = 0;
    }
    
    
    //HEARTBEAT
    if(TMR0IF == 1){
        if(!FIRST_SEND){
            heartBeatCounter++;
            if(heartBeatCounter > 35){
                danger(HEARTBEAT_ERRORCODE);
            }
        }
        TMR0IF = 0;
    }
    
    
    //BLINK
    if(TMR1IF == 1){
        if(MAP_V_BLINK == 1){
            blinkCounter++; 
            
            if(blinkCounter == 13){
                V_BLINK_OUT_PIN = 0;
            }
            if(blinkCounter > 26){
                V_BLINK_OUT_PIN = 1;
                blinkCounter = 0;
            }
            
        }
        
        if(MAP_H_BLINK == 1){
            blinkCounter++; 
            
            if(blinkCounter == 13){
                H_BLINK_OUT_PIN = 0;
            }
            if(blinkCounter > 26){
                H_BLINK_OUT_PIN = 1;
                blinkCounter = 0;
            }
            
        }
        
        TMR1IF = 0;
    }
    
}

