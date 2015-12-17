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

int heartBeatCounter;
int FIRST_SEND;
long interruptCounter;

//INPUTS

#define TURNOFF_IN          PORTBbits.RB4
#define BATTERY_IN          PORTAbits.RA0
//#define asdf                ADRESL

//OUTPUTS
#define CHIP_ALIVE_DIODE_PIN    LATAbits.LATA7
#define HEARTBEAT_DIODE_PIN     LATAbits.LATA6
#define ERROR_DIODE_PIN         LATBbits.LATB1
#define BACKLIGHT_OUT_PIN       LATBbits.LATB7
#define H_BLINK_OUT_PIN         LATBbits.LATB6
#define V_BLINK_OUT_PIN         LATBbits.LATB5

#endif	/* INIT_H */

