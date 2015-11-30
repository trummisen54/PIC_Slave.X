
#include "ECAN.h"
#include "config.h"
#include "Other.h"


#define BTN1 PORTBbits.RB0
#define PRESSED 0

#define TRUE    1
#define FALSE   0



void InitDevice(void){   
    count = 0x01;
    
    // Set the internal oscillator to 64MHz
    OSCCONbits.IRCF = 7;
    OSCTUNEbits.PLLEN = 1;
    
    // Initialize global variables to 0
    heartbeatCount = 0;
    buttonWasPressed = 0;
    
    ANCON0 = ANCON1 = 0x00;
    TRISB = 0xFF;                   //using b0 as input
    
    
    TRISCbits.TRISC7 = 0;
    LATCbits.LATC7 = 0;
    
    TRISCbits.TRISC6 = 0;
    LATCbits.LC6 = 0; // chip alive inicator
    
    
    HORN_STATUS = PORTBbits.RB0;
    
    
    
}


unsigned char ButtonPressed(void){
    
    unsigned char buttonPressedState = FALSE;
    
    // Check to see if the pushbutton is pressed
    if(BTN1 == PRESSED)
    {        
        // If button wasn't previously pressed, then set current button pressed state to true
        if(buttonWasPressed == FALSE)
        {
            buttonPressedState = TRUE;
        }
        
        // Set flag to say button was previously pressed
        buttonWasPressed = TRUE;
    }
    else
    {
        // Clear flag to say button was previously not pressed
        buttonWasPressed = FALSE;
    }    
    
    // Return button pressed state
    return buttonPressedState;
}


int HornChanged(){
    if(HORN_STATUS != PORTBbits.RB0)
        if(PORTBbits.RB0 == 1){
            HORN_STATUS = 1;
            return 1;
        }
        else{
            HORN_STATUS = 0;
            return 1;
        }
    
    else{
        return 0;
    }
    


}

int MotorChanged(){
    return 0;
}


void Delay(unsigned int count)
{
    // Countdown until equal to zero and then return
    while(count--);
}