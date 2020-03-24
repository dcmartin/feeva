###
# makefile
###

DIR_FONTS = ./Fonts
DIR_OBJ = ./obj
DIR_BIN = ./bin

OBJ_C = $(wildcard ${DIR_FONTS}/*.c ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

CC := gcc

CFLAGS := -g -O0 -Wall

# USELIB = USE_WIRINGPI_LIB
# USELIB = USE_DEV_LIB
USELIB = USE_BCM2835_LIB

ifeq ($(USELIB), USE_BCM2835_LIB)
    TARGET += bcm2835
    LIB = -lbcm2835
else ifeq ($(USELIB), USE_WIRINGPI_LIB)
    TARGET += wiringpi
    LIB = -lwiringPi
endif

TARGET += main
CFLAGS += -D$(USELIB)
LIB += -lm

default: ${TARGET}

wiringpi:
	sudo apt install -qq -y wiringpi

bcm2835:
	cd bcm2835-1.60 && sudo ./setup.sh

main: $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)

${DIR_BIN}/%.o : $(DIR_OBJ)/%.c 
	$(CC) $(CFLAGS) -c  $< -o $@ -I $(DIR_FONTS)

${DIR_BIN}/%.o:$(DIR_FONTS)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@ 
	
clean :
	make -C bcm2835-1.60 clean
	$(RM) $(DIR_BIN)/*.* $(TARGET) $(DIR_OBJ)/.*.sw?

.PHONY : wiringpi bcm2835 clean default
