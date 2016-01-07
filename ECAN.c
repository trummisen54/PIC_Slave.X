
/**********************************************************************
* 2010 Microchip Technology Inc.
*
* FileName:        ECAN.c
* Dependencies:    ECAN (.h) & other files if applicable, see below
* Processor:       PIC18F66K80 family
* Linker:          MPLINK 4.37+
* Compiler:        C18 3.36+
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all 
* ownership and intellectual property rights in the code accompanying
* this message and in all derivatives hereto.  You may use this code,
* and any derivatives created by any person or entity by or on your 
* behalf, exclusively with Microchip's proprietary products.  Your 
* acceptance and/or use of this code constitutes agreement to the 
* terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS". NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT 
* NOT LIMITED TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, 
* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS 
* CODE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS, COMBINATION WITH 
* ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE 
* LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR
* BREACH OF STATUTORY DUTY), STRICT LIABILITY, INDEMNITY, 
* CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
* EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR 
* EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER 
* CAUSED, EVEN IF MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE
* DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT ALLOWABLE BY LAW, 
* MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS
* CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP 
* SPECIFICALLY TO HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify,
* test, certify, or support the code.
*
* REVISION HISTORY:
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        Date      	Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Manning C.    12/1/2010	First release of source file
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
* ADDITIONAL NOTES:
* Code Tested on:
* PIC18 Explorer Demo Board with PIC18F46K80 (PIC18F66K80 family) controller + ECAN/LIN Daughterboard 
* 
*
* DESCRIPTION:
* In this example, CPU is initially configured to run from external 
* secondary osc and then clock switching is initiated to run from 
* Internal FRC.
*********************************************************************/




/*********************************************************************
*
*                            Includes 
*
*********************************************************************/
//#include <p18cxxx.h>
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"
#include "init.h"
#include "peripherals.h"

/*********************************************************************
*
*                             Defines 
*
*********************************************************************/
// ECAN Operation mode
#define F_Lisn_mode     0      // 1 set ECAN module in listen only mode
#define F_Loop_mode     0      // 1 set ECAN module in loopback mode
#define F_Normal_mode   1       // 1 set the ECAN module in normal mode



/*********************************************************************
*
*                            Global Variables 
*
*********************************************************************/
unsigned char temp_EIDH;
unsigned char temp_EIDL;
unsigned char temp_SIDH;
unsigned char temp_SIDL;
unsigned char temp_DLC;


//unsigned char count;



/*********************************************************************
*
*                       Configure the CAN Module
*
*********************************************************************/
void CANSetup(void)
{
    // Enter CAN module into config mode
    CANCON = 0x80;    //REQOP<2:0>=100
    while(!(CANSTATbits.OPMODE ==0x04));
    
    // Enter CAN module into Mode 1
    ECANCON = 0x40;
    
    // Initialize CAN Timing  
    //  1   Mbps @ 64MHz  
    BRGCON1 = 0x81; //0000 0011     //SJW=3TQ     BRP  1
    BRGCON2 = 0xB8; //1011 1000     //SEG2PHTS 1    sampled once  PS1=8TQ  PropagationT 1TQ  
    BRGCON3 = 0x05; //0000 0101     //PS2  6TQ


    // Setup Programmable buffers
    //  B0 is a receive buffer AND B2,B3,B4,B5 are Transmit buffers
    BSEL0 = 0xF8;   //1111 10--
    
    // Initialize Receive Masks
    //  The first mask is used that accepts all SIDs and no EIDs
    RXM0EIDH = 0x00;    // 
    RXM0EIDL = 0x00;
    RXM0SIDH = 0xFF;    // Standard ID FILTER
    RXM0SIDL = 0xE0;
    
    //  The second mask is used that accepts all SIDs and EIDs
    RXM1EIDH = 0x00;    // 0's for EID and SID
    RXM1EIDL = 0x00;
    RXM1SIDH = 0xFF;
    RXM1SIDL = 0xE0;
    
    // Enable Filters
    //  Only using first three filters
    RXFCON0 = 0x07;     //Enable Filters 0,1,2
    RXFCON1 = 0x00;     //Disable all others
    
    // Assign Filters to Masks
    MSEL0 = 0xC0;     //Assign Filters 0-2 to Mask 0 //F  3 3 No mask
    MSEL1 = 0xFF;     //Assign Filters 4-7 to Mask     // No mask
    MSEL2 = 0xFF;     //Assign Filters 8-11 to Mask    // No mask
    MSEL3 = 0xFF;     //Assign Filters 12-15 to Mask   // No mask
    
    // Assign Filters to Buffers
    
    RXFBCON0 = 0x10;     //Assign Filter 0 to RXB0, and Filter 1 to RXB1
    RXFBCON1 = 0xF2;     //Assign Filter 2 to B0, Filter 2 no filter
    
    RXFBCON2 = 0xFF;     //Assign the rest of the buffers with no filter
    RXFBCON3 = 0xFF;
    RXFBCON4 = 0xFF;
    RXFBCON5 = 0xFF;
    RXFBCON6 = 0xFF;
    RXFBCON7 = 0xFF;
    
    // Initialize Receive Filters
    //  Filter 0 = 0x196
    //  Filter 1 = 0x19A
    //  Filter 2 = 0x19E
    RXF0EIDH = 0x00;
    RXF0EIDL = 0x00;
    RXF0SIDH = 0x32;
    RXF0SIDL = 0xC0;
    RXF1EIDH = 0x00;
    RXF1EIDL = 0x00;
    RXF1SIDH = 0x33;
    RXF1SIDL = 0x40;
    RXF2EIDH = 0x00;
    RXF2EIDL = 0x00;
    RXF2SIDH = 0x33;
    RXF2SIDL = 0xC0;
    
    // CAN module 
    if (F_Loop_mode ==1)
    {
        CANCON = 0x40;
        while(CANSTATbits.OPMODE==0x40);
    } 
    else if (F_Lisn_mode==1)
    {
        CANCON = 0x60;
        while(CANSTATbits.OPMODE==0x60);
    }
    else if (F_Normal_mode == 1){
        CANCON = 0x00;
        while(CANSTATbits.OPMODE==0x00);
    }
    
    else
    {
        CANCON = 0x40;
        while(CANSTATbits.OPMODE==0x40);
    }

    // Set Receive Mode for buffers
    RXB0CON = 0x00;
    RXB1CON = 0x00;
    
    
    CAN_ERRORBIT = 0;
    
}






/*********************************************************************
*
*                Check the buffers, if it have message
*
*********************************************************************/
unsigned char ECAN_Receive(void)
{
    unsigned char RXMsgFlag;

    RXMsgFlag = 0x00;
    
    if (RXB0CONbits.RXFUL) //CheckRXB0
    {
        temp_EIDH = RXB0EIDH;
        temp_EIDL = RXB0EIDL;
        temp_SIDH = RXB0SIDH;
        temp_SIDL = RXB0SIDL;
        temp_DLC = RXB0DLC;
        BITDATA = RXB0D0;
        TEMP_ACCELERATOR = RXB0D1; 
        temp_D2 = RXB0D2;
        temp_D3 = RXB0D3;
        temp_D4 = RXB0D4;
        temp_D5 = RXB0D5;
        temp_D6 = RXB0D6;
        temp_D7 = RXB0D7;
        RXB0CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
    }
    else if (RXB1CONbits.RXFUL) //CheckRXB1
    {
        temp_EIDH = RXB1EIDH;
        temp_EIDL = RXB1EIDL;
        temp_SIDH = RXB1SIDH;
        temp_SIDL = RXB1SIDL;
        temp_DLC = RXB1DLC;
        BITDATA = RXB1D0;
        TEMP_ACCELERATOR = RXB1D1;
        temp_D2 = RXB1D2;
        temp_D3 = RXB1D3;
        temp_D4 = RXB1D4;
        temp_D5 = RXB1D5;
        temp_D6 = RXB1D6;
        temp_D7 = RXB1D7;
        RXB1CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
    }
    else if (B0CONbits.RXFUL) //CheckB0
    {
        temp_EIDH = B0EIDH;
        temp_EIDL = B0EIDL;
        temp_SIDH = B0SIDH;
        temp_SIDL = B0SIDL;
        temp_DLC = B0DLC;
        BITDATA = B0D0;
        TEMP_ACCELERATOR = B0D1;
        temp_D2 = B0D2;
        temp_D3 = B0D3;
        temp_D4 = B0D4;
        temp_D5 = B0D5;
        temp_D6 = B0D6;
        temp_D7 = B0D7;
        
        B0CONbits.RXFUL = 0;
        RXMsgFlag = 0x01;
    }
    
    if  (RXMsgFlag == 0x01)
    {
        RXMsgFlag = 0x00;
        PIR5bits.RXB1IF = 0; //In Mode 1 this is RXBnIF, A CAN Receive Buffer has received a new message 
        return TRUE;
    }
    else
    {
        return FALSE;
    }    
}



/*********************************************************************
*
*                      Transmit Sample Mesaage
*
*********************************************************************/
void ECAN_Transmit(unsigned char SIDH, 
        unsigned char SIDL,
        unsigned char DLC,
        unsigned char TRANSMIT_ID,
        unsigned char DATA1,
        unsigned char DATA2,
        unsigned char DATA3,
        unsigned char DATA4,
        unsigned char DATA5,
        unsigned char DATA6,
        unsigned char DATA7)
{
    TXB0EIDH = 0x00;
    TXB0EIDL = 0x00;
    
    //0x
    TXB0SIDH = SIDH;
    TXB0SIDL = SIDL;
    TXB0DLC = DLC;
    
    /*
     * TXB0D0 = ID
     *0x01 = motor
     *0x02 = batteristatus 
     * 
     */
    
    TXB0D0 = TRANSMIT_ID; //TRANSMIT BUFFER
    TXB0D1 = DATA1;
    TXB0D2 = DATA2;
    TXB0D3 = DATA3;
    TXB0D4 = DATA4;
    TXB0D5 = DATA5;
    TXB0D6 = DATA6;
    TXB0D7 = DATA7;
    
    TXB0CONbits.TXREQ = 1; //Set the buffer to transmit
    
    
    /*This code shows that an error has occured
     
    while(TXB0CONbits.TXREQ = 1){ //TXB0CONbits.TXREQ is automatically cleared when the message is successfully sent
        while(TXB0CONbits.TXLARB);
        while(TXB0CONbits.TXERR);
        
        
    }
     * 
     * */
    
}





void unZipCAN(){

    TEMP_MAP_HEARTBEAT = (BITDATA & (1 << HEARTBEAT_BIT));
    TEMP_MAP_HEARTBEAT = (TEMP_MAP_HEARTBEAT >> HEARTBEAT_BIT);
    
    TEMP_MAP_BRAKE = BITDATA & (1 << BRAKE_BIT);
    TEMP_MAP_BRAKE = (TEMP_MAP_BRAKE >> BRAKE_BIT);
    
    TEMP_MAP_BACKLIGHT = BITDATA & (1 << BACKLIGHT_BIT);
    TEMP_MAP_BACKLIGHT = (TEMP_MAP_BACKLIGHT >> BACKLIGHT_BIT);
    
    TEMP_MAP_V_BLINK = BITDATA & (1 << V_BLINK_BIT);
    TEMP_MAP_V_BLINK = (TEMP_MAP_V_BLINK >> V_BLINK_BIT);
    
    TEMP_MAP_H_BLINK = BITDATA & (1 << H_BLINK_BIT);
    TEMP_MAP_H_BLINK = (TEMP_MAP_H_BLINK >> H_BLINK_BIT);
    
    TEMP_MAP_DIRECTION = BITDATA & (1 << DIRECTION_BIT);
    TEMP_MAP_DIRECTION = (TEMP_MAP_DIRECTION >> DIRECTION_BIT);
    
    TEMP_MAP_SAFETYPIN = BITDATA & (1 << SAFETYPIN_BIT);
    TEMP_MAP_SAFETYPIN = (TEMP_MAP_SAFETYPIN >> SAFETYPIN_BIT);
    
    TEMP_MAP_STOP = BITDATA & (1 << STOP_BIT);
    TEMP_MAP_STOP = (TEMP_MAP_STOP >> STOP_BIT);
    
}
