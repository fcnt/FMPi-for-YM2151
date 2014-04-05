#include <unistd.h>
#include <stdio.h>
#include "YM2151_spi.h"
#include "rpi_mcp23s17.h"
#include "bcm2835/bcm2835.h"

/* MPC23S17 IO Define */
#define IRQ_LOW(x)		(x = x & ~0x01); MCP23s17_WriteGPIO_B(x);
#define IRQ_HIGH(x)		(x = x |  0x01); MCP23s17_WriteGPIO_B(x);
#define IC_LOW(x)		(x = x & ~0x02); MCP23s17_WriteGPIO_B(x);
#define IC_HIGH(x)		(x = x |  0x02); MCP23s17_WriteGPIO_B(x);
#define A0_LOW(x)		(x = x & ~0x04); MCP23s17_WriteGPIO_B(x);
#define A0_HIGH(x)		(x = x |  0x04); MCP23s17_WriteGPIO_B(x);
#define WR_LOW(x)		(x = x & ~0x08); MCP23s17_WriteGPIO_B(x);
#define WR_HIGH(x)		(x = x |  0x08); MCP23s17_WriteGPIO_B(x);
#define RD_LOW(x)		(x = x & ~0x10); MCP23s17_WriteGPIO_B(x);
#define RD_HIGH(x)		(x = x |  0x10); MCP23s17_WriteGPIO_B(x);

unsigned char ctrl = 0x00;

/* write a register on YM2151 chip number 'n' */
void YM2151WriteReg(void *_chip, int r, int v)
{
	int *chip = _chip;
	unsigned char addr;
	unsigned char data;

//	printf("debug[%s]: \n", __func__);

	/* adjust to 8 bits */
	addr = r & 0xff;
	data = v & 0xff;

	/* RD Disable */
	RD_HIGH(ctrl);

	/* A0 Enable */
	A0_LOW(ctrl);

	/* Addr Write */
    MCP23s17_WriteGPIO_A(addr);
	bcm2835_delayMicroseconds(17);
	WR_LOW(ctrl);

	/* Write Address */
	bcm2835_delayMicroseconds(17);
	WR_HIGH(ctrl);
	bcm2835_delayMicroseconds(17);
	A0_HIGH(ctrl);
	bcm2835_delayMicroseconds(17);
	
	/* Write Data */
	MCP23s17_WriteGPIO_A(data);

	bcm2835_delayMicroseconds(17);
	WR_LOW(ctrl);
	bcm2835_delayMicroseconds(17);
	WR_HIGH(ctrl);
	bcm2835_delayMicroseconds(17);
}

int YM2151ReadStatus( void *_chip )
{
	return 0;
}

void YM2151Shutdown(void *_chip)
{
}

void YM2151ResetChip(void *_chip)
{
	printf("debug[%s]: \n", __func__);
	IC_LOW(ctrl);
	usleep(10);
	IC_HIGH(ctrl);
	usleep(10);
}

void * YM2151Init(int index, int clock, int rate)
{
	char *chip;
	printf("debug[%s]: \n", __func__);
	YM2151ResetChip(chip);
}

void YM2151UpdateOne(void *chip, SAMP **buffers, int length)
{
}
