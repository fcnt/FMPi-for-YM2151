# Makefile
CC  = gcc
TARGET  = fmpi
SRCS = main.c rpi_mcp23s17.c YM2151_spi.c bcm2835/bcm2835.c
OBJS    = $(SRCS:.c=.o)

# インクルードファイルのあるディレクトリパス
INCDIR  = 

# ライブラリファイルのあるディレクトリパス
LIBDIR  = 

# 追加するライブラリファイル
LIBS    = -lm

$(TARGET):
	$(CC) -o $(TARGET) $(SRCS) $(LIBDIR) $(LIBS)

clean:
	$(RM) -rf $(OBJS) $(TARGET)
