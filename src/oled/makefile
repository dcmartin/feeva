DIR_FONTS = ./Fonts
DIR_OBJ = ./obj
DIR_BIN = ./bin

OBJ_C = $(wildcard ${DIR_FONTS}/*.c ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = main
#BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG)

BCM2835 =  -Ibcm2835-16.0/src -Lbcm2835-16.0/src
CFLAGS += $(BCM2835)

USELIB = USE_BCM2835_LIB
# USELIB = USE_WIRINGPI_LIB
# USELIB = USE_DEV_LIB
DEBUG = -D $(USELIB)
ifeq ($(USELIB), USE_BCM2835_LIB)
    LIB = -lbcm2835 -lm 
else ifeq ($(USELIB), USE_WIRINGPI_LIB)
    LIB = -lwiringPi -lm 
endif

default: ${TARGET}

bcm2835-160/libbcm2835.a:
	cd bcm2835-1.60 && ./configure && make 

${TARGET}: $(OBJ_O) bcm2835-160/libbcm2835.a
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)

${DIR_BIN}/%.o : $(DIR_OBJ)/%.c 
	$(CC) $(CFLAGS) -c  $< -o $@ -I $(DIR_FONTS) $(LIB)

${DIR_BIN}/%.o:$(DIR_FONTS)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 
	
clean :
	make -C bcm2835-1.60 clean
	$(RM) $(DIR_BIN)/*.* $(TARGET) $(DIR_OBJ)/.*.sw?

.PHONY : bcm2835-1.60 clean default
