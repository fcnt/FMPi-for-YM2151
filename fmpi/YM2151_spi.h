/*
**
** File: YM2151_spi.h - header file for YM2151 FM Operator Type-M(OPM)
**
** (c) 2014 Taisuke Watanabe
*/

#ifndef _H_YM2151_
#define _H_YM2151_

typedef unsigned char UINT8;
typedef char INT8;
typedef short INT16;
typedef unsigned short UINT16;
typedef unsigned int UINT32;
typedef int INT32;
typedef unsigned char SAMP;

/*
** Initialize YM2151 emulator(s).
**
** 'num' is the number of virtual YM2151's to allocate
** 'clock' is the chip clock in Hz
** 'rate' is sampling rate
*/
void *YM2151Init(int index, int clock, int rate);

/* shutdown the YM2151 emulators*/
void YM2151Shutdown(void *chip);

/* reset all chip registers for YM2151 number 'num'*/
void YM2151ResetChip(void *chip);

/* write 'v' to register 'r' on YM2151 chip number 'n'*/
void YM2151WriteReg(void *chip, int r, int v);

/* read status register on YM2151 chip number 'n'*/
int YM2151ReadStatus(void *chip);

#endif /*_H_YM2151_*/
