/* 
 * File:   Other.h
 * Author: E
 *
 * Created on den 26 november 2015, 16:54
 */

#ifndef OTHER_H
#define	OTHER_H

#ifdef	__cplusplus
extern "C" {
#endif

void InitDevice(void);
void Delay(unsigned int count);
unsigned char ButtonPressed(void);
int HornChanged();
int MotorChanged();

int HORN_STATUS;

#ifdef	__cplusplus
}
#endif

#endif	/* OTHER_H */

