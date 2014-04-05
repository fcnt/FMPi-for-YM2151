/* MCP23S17 Registers */
#define MCP23S17_IODIRA     (0x00)
#define MCP23S17_IPOLA      (0x02)
#define MCP23S17_GPINTENA   (0x04)
#define MCP23S17_DEFVALA    (0x06)
#define MCP23S17_INTCONA    (0x08)
#define MCP23S17_IOCONA     (0x0A)
#define MCP23S17_GPPUA      (0x0C)
#define MCP23S17_INTFA      (0x0E)
#define MCP23S17_INTCAPA    (0x10)
#define MCP23S17_GPIOA      (0x12)
#define MCP23S17_OLATA      (0x14)

#define MCP23S17_IODIRB     (0x01)
#define MCP23S17_IPOLB      (0x03)
#define MCP23S17_GPINTENB   (0x05)
#define MCP23S17_DEFVALB    (0x07)
#define MCP23S17_INTCONB    (0x09)
#define MCP23S17_IOCONB     (0x0B)
#define MCP23S17_GPPUB      (0x0D)
#define MCP23S17_INTFB      (0x0F)
#define MCP23S17_INTCAPB    (0x11)
#define MCP23S17_GPIOB      (0x13)
#define MCP23S17_OLATB      (0x15)

/* Definition of IOCON register bit */
#define IOCON_UNUSED        (0x01)
#define IOCON_INTPOL        (0x02)
#define IOCON_ODR           (0x04)
#define IOCON_HAEN          (0x08)
#define IOCON_DISSLW        (0x10)
#define IOCON_SEQOP         (0x20)
#define IOCON_MIRROR        (0x40)
#define IOCON_BANK_MODE     (0x80)

/* Definition of MCP23S17 Command */
#define MCP23S17_CMD_RD      (0x41)
#define MCP23S17_CMD_WR      (0x40)

/* Definition of SPI */
#define SPI_OK		 0
#define SPI_ERROR	-1

#define SPI_DEVICE    "/dev/spidev0.0"  /* SPI デバイス */
#define SPI_SPEED     4000000           /* クロック 4MHz */
#define SPI_BITS      8                 /* ビット数（8bit のみ可能）*/
#define SPI_BLOCKSIZE 2048              /* 転送ブロックのバイト数 */
#define SPI_DELAY     0                 /* データリード時のアドレスセット後のディレイ(us) */

/* public API */
void MCP23s17_WriteGPIO_A(unsigned char data);
void MCP23s17_WriteGPIO_B(unsigned char data);
void MCP23s17_ReadGPIO_A(unsigned char *data);
void MCP23s17_ReadGPIO_B(unsigned char *data);
int MCP23s17_Init(void);

