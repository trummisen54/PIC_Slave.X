#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ECAN.h"
#include "Other.h"
#include "init.h"




void Delay(unsigned int count)
{
    // Countdown until equal to zero and then return
    while(count--);
}