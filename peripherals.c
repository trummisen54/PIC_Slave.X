#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"
#include "init.h"
#include "peripherals.h"

 

void checkHeartbeat(){
    
    /*
    if(i2c_reg_map[REC] == 0){
        if(TMR1L > ?){
        }
        else{
            TMR1L = 0;

        }
        if(i2c_reg_map[5] != MAP_HEARTBEAT){
            MAP_HEARTBEAT = i2c_reg_map[5];
            //send
        }
    }
    else{
        send
    
    }
     */
    
}
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
    if(TEMP_MAP_V_BLINK != MAP_V_BLINK){
        MAP_V_BLINK = TEMP_MAP_V_BLINK;
        V_BLINK_OUT_PIN = MAP_V_BLINK;
    }
}
void checkH_blink(){
    if(TEMP_MAP_H_BLINK != MAP_H_BLINK){
        MAP_H_BLINK = TEMP_MAP_H_BLINK;
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
    if(TEMP_MAP_ACCELERATOR != MAP_ACCELERATOR){
        MAP_ACCELERATOR = TEMP_MAP_ACCELERATOR;
        LATB = MAP_ACCELERATOR;
    }
}


void updateInputs(){
    MAP_BATTERYSTATUS = BATTERY_IN;
    //MAP_VELOCITY = 
    //MAP_HEARTBEAT = 
 
}