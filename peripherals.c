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
            ENABLE_MOTOR_OUT = 0;
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
        //used in "checkAccelerator()"
    }
}
void checkSafetyPin(){
    if(TEMP_MAP_SAFETYPIN != MAP_SAFETYPIN){
        MAP_SAFETYPIN = TEMP_MAP_SAFETYPIN;
        //danger();
    }
}
void checkStop(){
    if(TEMP_MAP_STOP != MAP_STOP){
        MAP_STOP = TEMP_MAP_STOP;
        if(MAP_STOP == 1){
            ENABLE_MOTOR_OUT = 0; //motor stops
            TURNOFF_OUT = 1; //Kills the power
    
            /*
            for(int i = 0; i<7; i++){
                CHIP_ALIVE_DIODE_PIN = 0;
                Delay(ONE_MS * 100);
                CHIP_ALIVE_DIODE_PIN = 1;
                Delay(ONE_MS * 100);
            }
            */
            
            //danger();
        }     
    }

}
void checkAccelerator(){
    /*
     MOTORVAL
     1111 1111 = +10V
     1000 0001 = +1V
     1000 0000 = 0V
     0111 1111 = -1V
     0000 0000 = -10V
     * 
    
     TEMP_ACCELERATOR (input)
     1111 1111
     0000 0000
     * 
     * At zero gas, there will not be 0 volt in for shore,
     * TEMP_ACCELERATOR + OFFSET_ACCELERATOR = zero gas.
     * 
    */
    
    if(TEMP_ACCELERATOR != MAP_ACCELERATOR){
        MAP_ACCELERATOR = TEMP_ACCELERATOR;

        int HALF_ACCELERATOR = TEMP_ACCELERATOR/2;
        int gas;
        char startval = 0b10001000;
        
        if(MAP_DIRECTION == 1){ //front
            
            gas = startval + HALF_ACCELERATOR;
            
            if(gas > 0xFF)
                gas = 0xFF;
            
            LATC = gas;
        }
        else if(MAP_DIRECTION == 0){ //back
            
            gas = startval - HALF_ACCELERATOR;
            
            if(gas < 0)
                gas = 0;
            
            LATC = gas;
        }

        if(TEMP_ACCELERATOR < deadArea_gas){ //dead area
            ENABLE_MOTOR_OUT = 0;
        }
        else{
            startMotor();
        }
    }
}

void startMotor(){
    if(TEMP_MAP_BRAKE == 0){
        ENABLE_MOTOR_OUT = 1;
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
    
    int low = ADRESL;
    int high = (ADRESH << 8);
    int totBattery = (high | low);
    if(totBattery < 0){ // The status gets negative on min val.
        totBattery = 0;
    }
    
    
    return totBattery;

}




