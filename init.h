/* 
 * File:   init.h
 * Author: E
 *
 * Created on den 10 december 2015, 18:16
 */

#ifndef INIT_H
#define	INIT_H

void InitDevice();
void setup_Interrupt();

int FIRST_SEND;


//INPUTS


#define BATTERY_IN          PORTAbits.RA0
//#define asdf                ADRESL

//OUTPUTS
#define CHIP_ALIVE_DIODE_PIN    LATAbits.LATA6
#define HEARTBEAT_DIODE_PIN     LATBbits.LATB1
#define ERROR_DIODE_PIN         LATAbits.LATA7
#define BACKLIGHT_OUT_PIN       LATBbits.LATB7
#define H_BLINK_OUT_PIN         LATBbits.LATB6
#define V_BLINK_OUT_PIN         LATBbits.LATB5
#define TURNOFF_OUT             LATBbits.LATB4
#define ENABLE_MOTOR_OUT        LATBbits.LATB0


//static final?
int HEARTBEAT_ERRORCODE = 3;
int CAN_ERRORCODE = 4;

int CAN_ERRORBIT; //will be set if there is a CAN error

#endif	/* INIT_H */

