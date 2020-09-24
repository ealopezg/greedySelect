
CC = gcc
CFLAGS = -Wall
TARGET = optimal

IDIR = ./include
ODIR = ./obj
SDIR = ./src


TARGET_DEBUG := $(TARGET)_debug
EXT = out
DEL_CMD = rm -f
SRCS := $(shell find $(SDIR) -name *.c)

ifeq ($(OS),Windows_NT)
	EXT = exe
	DEL_CMD = del
endif


main: clean
	@$(CC) $(CFLAGS) -I$(IDIR) $(SRCS)  -o $(TARGET).$(EXT)

debug:
	@$(CC) -DDEBUG -I$(IDIR) $(CFLAGS) $(SRCS) -o $(TARGET_DEBUG).$(EXT)

clean:
	@$(DEL_CMD) $(TARGET).$(EXT) $(TARGET_DEBUG).$(EXT)