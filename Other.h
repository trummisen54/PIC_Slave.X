/* 
 * File:   Other.h
 * Author: E
 *
 * Created on den 26 november 2015, 16:54
 */

#ifndef OTHER_H
#define	OTHER_H


void Delay(unsigned int count);
void heartBeat();
void danger(int errorCode);


#define DEVICE_OSC  64
#define ONE_MS      (unsigned int)(DEVICE_OSC/4)*80

#endif	/* OTHER_H */

