TARGET := display
SRC := $(TARGET).c
OBJ := $(TARGET).o
SO := libdlink.so


CFLAGS := -g -Wall
LFLAGS := -lm -pthread
SHAREDS := -shared
CC := gcc $(CFLAGS) $(LFLAGS) 


all : $(TARGET)


$(TARGET): $(OBJ) 
	$(CC) $(SHAREDS) $(SRC) -fPIC -o $(SO)
.c.o:
	$(CC) -c $^
clean:
	rm -f $(TARGET) $(OBJ)
	rm -f libdlink $(SO)

