#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "YM2151_spi.h"
#include "rpi_mcp23s17.h"
#include "bcm2835/bcm2835.h"

#define FMPI_OK			0
#define FMPI_ERR			-1

int sigcatch(void);

#define BUF_SIZE	(64*1024)

int main(int argc, char *argv[])
{
	FILE *fp;
	char *buf;
	char read_data[2];
	char reg, data;
	int ret, i;
	uint64_t delay;
	
	if(argc != 3)
	{
		printf("missing file argument.\n");
		printf("usage: fmpi <cym fime>\n");
		return FMPI_ERR;
	}
	
	if((fp = fopen(argv[1], "rb")) == NULL)
	{
		printf("can't open %s\n", argv[1]);
		return FMPI_ERR;
	}
	
	delay = atoi(argv[2]);
	
	buf = (char *)malloc(BUF_SIZE);
	if(buf == NULL)
	{
		printf("can't alloc memory.\n");
		fclose(fp);
		return FMPI_ERR;
	}
	
	setvbuf(fp, buf, _IOFBF, BUF_SIZE);
	
	ret = MCP23s17_Init();
	if(ret == SPI_ERROR)
	{
		printf("can't init SPI.\n");
		fclose(fp);
		free(buf);
		return FMPI_ERR;
	}
	/*
	if (SIG_ERR == signal(SIGINT, sigcatch))
	{
		printf("failed to set signal handler.n");
		return FMPI_ERR;
	}
	*/
	bcm2835_init();
	YM2151Init(0, 0, 0);
	
	while(1)
	{
		ret = fread(read_data, sizeof(char), 2, fp);
		reg  = read_data[0];
		data = read_data[1];
		YM2151WriteReg(NULL, (int)reg, (int)data);
		bcm2835_delayMicroseconds(delay);

		if(ret <= 0)
			break;
	}
	
	fclose(fp);
	free(buf);
	return FMPI_OK;
}

int sigcatch(void)
{
	printf("stop\n");
	YM2151Init(0, 0, 0);
	return FMPI_OK;
}
