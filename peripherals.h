/* 
 * File:   peripherals.h
 * Author: E
 *
 * Created on den 9 december 2015, 13:31
 */

#ifndef PERIPHERALS_H
#define	PERIPHERALS_H

void checkHeartbeat();
void checkBrake();
void checkBacklight();
void checkV_blink();
void checkH_blink();
void checkDirection();
void checkSafetyPin();
void checkAccelerator();
void updateInputs();



//RECIEVED REGISTERS
//***********************************************

//REGISTER VALUE
int MAP_HEARTBEAT, MAP_BRAKE, MAP_BACKLIGHT, MAP_V_BLINK,
        MAP_H_BLINK, MAP_DIRECTION, MAP_SAFETYPIN, MAP_ACCELERATOR;

//ACTUAL VALUE
int TEMP_MAP_HEARTBEAT, TEMP_MAP_BRAKE, TEMP_MAP_BACKLIGHT, TEMP_MAP_V_BLINK,
        TEMP_MAP_H_BLINK, TEMP_MAP_DIRECTION, TEMP_MAP_SAFETYPIN, TEMP_MAP_ACCELERATOR;
//******************************************************************


//TRANSMITT REGISTERS
//***********************************************
int MAP_BATTERYSTATUS, MAP_VELOCITY, MAP_HEARTBEAT;
//***********************************************


#define HEARTBEAT_BIT   0
#define BRAKE_BIT       1
#define BACKLIGHT_BIT   2
#define V_BLINK_BIT     3
#define H_BLINK_BIT     4
#define DIRECTION_BIT   5
#define SAFETYPIN_BIT   6


#endif	/* PERIPHERALS_H */

