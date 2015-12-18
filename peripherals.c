#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"
#include "init.h"
#include "peripherals.h"

 
void checkBrake(){
    if(TEMP_MAP_BRAKE != MAP_BRAKE){
        MAP_BRAKE = TEMP_MAP_BRAKE;
        if(MAP_BRAKE == 1){
            //slow down!!
        }
        else{
            //speed up :)
        }
    }
}
void checkBacklight(){
    if(TEMP_MAP_BACKLIGHT != MAP_BACKLIGHT){
        MAP_BACKLIGHT = TEMP_MAP_BACKLIGHT;
        BACKLIGHT_OUT_PIN = MAP_BACKLIGHT;
    }
}
void checkV_blink(){
    if(TEMP_MAP_V_BLINK != MAP_V_BLINK){ //generate blink signal if TEMP_MAP_V_BLINK == 1
        MAP_V_BLINK = TEMP_MAP_V_BLINK;
        
        blinkCounter = 0;
        V_BLINK_OUT_PIN = MAP_V_BLINK;
    }
}
void checkH_blink(){
    if(TEMP_MAP_H_BLINK != MAP_H_BLINK){
        MAP_H_BLINK = TEMP_MAP_H_BLINK;
        H_BLINK_OUT_PIN = MAP_H_BLINK;
        
        blinkCounter = 0;
        H_BLINK_OUT_PIN = MAP_H_BLINK;
    }
}
void checkDirection(){
    if(TEMP_MAP_DIRECTION != MAP_DIRECTION){
        MAP_DIRECTION = TEMP_MAP_DIRECTION;
        //goto motor
    }
}
void checkSafetyPin(){
    if(TEMP_MAP_SAFETYPIN != MAP_SAFETYPIN){
        MAP_SAFETYPIN = TEMP_MAP_SAFETYPIN;
        // ?????
    }
}
void checkAccelerator(){
    if(TEMP_ACCELERATOR != MAP_ACCELERATOR){
        LATC = TEMP_ACCELERATOR;
        MAP_ACCELERATOR = TEMP_ACCELERATOR;
    }
}


void updateInputs(){
    
    
    MAP_BATTERYSTATUS = readAnalog();
    //MAP_VELOCITY = 
    //MAP_HEARTBEAT = 
 
}

int readAnalog(){
    
    
    ADCON0 = 0x00;
    
    ADCON0bits.ADON = 1; //A/D Converter is operating
    
     
    
    Delay(ONE_MS * 100); //Pauses the pic to allow the ADC capacitor to fully ......
    
    ADCON0bits.GO_DONE = 1;  //Start analog read
    while(ADCON0bits.GO_DONE); //Clears when analog read is done
    
    ADCON0bits.ADON = 0;
    
    
    
    return ADRESH;

}

