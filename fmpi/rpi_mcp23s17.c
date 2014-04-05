#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "rpi_mcp23s17.h"

static int spi_fd;

/* Proto Type */
int spi_init(void);
void spi_quit (void);
void spi_write16(unsigned char reg_addr, unsigned char data);
void spi_read16(unsigned char reg_addr, unsigned char *data);

void MCP23s17_WriteGPIO_A(unsigned char data)
{
//    printf("debug[%s]: \n", __func__);
//    spi_write16(MCP23S17_IODIRA, 0x00);
    spi_write16(MCP23S17_GPIOA,  data);
}

void MCP23s17_WriteGPIO_B(unsigned char data)
{
//    printf("debug[%s]: \n", __func__);
//    spi_write16(MCP23S17_IODIRB, 0x00);
    spi_write16(MCP23S17_GPIOB,  data);
}

void MCP23s17_ReadGPIO_A(unsigned char *data)
{
//    printf("debug[%s]: \n", __func__);
    spi_write16(MCP23S17_IODIRB, 0xFF);
    spi_read16 (MCP23S17_GPIOB,  data);
}

void MCP23s17_ReadGPIO_B(unsigned char *data)
{
//    printf("debug[%s]: \n", __func__);
    spi_write16(MCP23S17_IODIRB, 0xFF);
    spi_read16 (MCP23S17_GPIOB,  data);
}

int MCP23s17_Init(void)
{
//    printf("debug[%s]: \n", __func__);
    spi_init();
    spi_write16(MCP23S17_IOCONA, IOCON_HAEN);
    spi_write16(MCP23S17_IOCONB, IOCON_HAEN);
    spi_write16(MCP23S17_IODIRA, 0x00);
    spi_write16(MCP23S17_IODIRB, 0x00);
    return SPI_OK;
}

/**
 * @brief SPIを初期化する
 *
 * @retval SPI_OK       初期化成功
 * @retval SPIERROR     初期化失敗
 */
int spi_init(void)
{
    int  ret;
    unsigned char mode;
    unsigned char bits;
    unsigned int speed;

    printf("debug[%s]: \n", __func__);
    /* SPI デバイスを開く */
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        printf("error[%s]: cannot open %s \n", __func__, SPI_DEVICE);
        return SPI_ERROR;
    }
    
    /* 転送モードを設定 */
    mode = SPI_MODE_0;
    ret = ioctl(spi_fd, SPI_IOC_WR_MODE, &mode);
    if (ret < 0) {
        printf("error[%s]: cannot set WR_MODE to %d\n", __func__, mode);
        close(spi_fd);
        return SPI_ERROR;
    }
    ret = ioctl(spi_fd, SPI_IOC_RD_MODE, &mode);
    if (ret < 0) {
        printf("error[%s]: cannot set RD_MODE to %d\n", __func__, mode);
        close(spi_fd);
        return SPI_ERROR;
    }
    
    /* 送信・受信ビット数を設定 */
    bits = SPI_BITS;
    ret = ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret < 0) {
        printf("error[%s]: cannot set WR_BITS_PER_WORD to %d\n", __func__, bits);
        close(spi_fd);
        return SPI_ERROR;
    }
    ret = ioctl(spi_fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret < 0) {
        printf("error[%s]: cannot set RD_BITS_PER_WORD to %d\n", __func__, bits);
        close(spi_fd);
        return SPI_ERROR;
    }
    
    /*  送信・受信速度を設定 */
    speed = SPI_SPEED;
    ret = ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret < 0) {
        printf("error[%s]: cannot set WR_MAX_SPEED_HZ to %d \n", __func__, speed);
        close(spi_fd);
        return SPI_ERROR;
    }
    ret = ioctl(spi_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret < 0) {
        printf("error[%s]: cannot set RD_MAX_SPEED_HZ to %d \n", __func__, speed);
        close(spi_fd);
        return SPI_ERROR;
    }
    
    return SPI_OK;
}

/*
 * @brief SPI閉じる
 */
void spi_quit (void)
{
    close(spi_fd);
}

/**
 * @brief SPIで2バイトのデータを送信する(MCP23S17のレジスタアドレス、データを送信する事を想定)
 * @param[in] reg_addr      レジスタアドレス
 * @param[in] data          送信データ
 *
 */
void spi_write16(unsigned char reg_addr, unsigned char data)
{
    unsigned char send_data[4];
    unsigned char recv_data[4];
    struct spi_ioc_transfer tr;
    
    send_data[0] = MCP23S17_CMD_WR;
    send_data[1] = reg_addr;
    send_data[2] = data;
    
    tr.tx_buf           = (unsigned int)send_data;
    tr.rx_buf           = (unsigned int)recv_data;
    tr.len              = 3;
    tr.speed_hz         = SPI_SPEED;
    tr.delay_usecs      = SPI_DELAY;
    tr.bits_per_word    = SPI_BITS;
    
//    printf("debug[%s]: reg=0x%02x data=0x%02x\n", __func__, reg_addr, data);
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
}

/**
 * @brief SPIで2バイトのデータを送信する(MCP23S17のレジスタアドレス、データを送信する事を想定)
 * @param[in]  reg_addr      レジスタアドレス
 * @param[out] data          送信データ
 *
 */
void spi_read16(unsigned char reg_addr, unsigned char *data)
{
    unsigned char send_data[4];
    struct spi_ioc_transfer tr;
    
    send_data[0] = MCP23S17_CMD_RD;
    send_data[1] = reg_addr;
    send_data[2] = 0;
    
    tr.tx_buf           = (unsigned int)send_data;
    tr.rx_buf           = (unsigned int)data;
    tr.len              = 3;
    tr.speed_hz         = SPI_SPEED;
    tr.delay_usecs      = SPI_DELAY;
    tr.bits_per_word    = SPI_BITS;
    
    printf("debug[%s]: \n", __func__);
    ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr);
}

