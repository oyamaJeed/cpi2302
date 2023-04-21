TARGET := test2
SRC := $(TARGET).c
OBJ := $(TARGET).o

CFLAGS := -g -Wall
CC := gcc $(CFLAGS)

export NAME := "/home/meit2302/cpi2302"

all : $(TARGET)

$(TARGET): $(OBJ) 
	gcc -o test2 test2.c -L. -ldlink

clean:
	rm -f $(TARGET) $(OBJ)

