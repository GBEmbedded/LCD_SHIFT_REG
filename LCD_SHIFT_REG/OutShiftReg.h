/*
 * OutShiftReg.h
 *
 * Created: 10/10/2015 9:31:23 PM
 *  Author: MoHaMeD
 */ 


/*
Author Mohamed Gobran
*/
#ifndef OUTSHIFTREG_H_
#define OUTSHIFTREG_H_


void shiftInit();
void shiftPulse();
void shiftLatch();
void shiftWrite(uint8_t data);
void Wait();



#endif /* OUTSHIFTREG_H_ */