CC = gcc
CFLAGS = -Wall -lm
LDFLAGS =
OBJFILES = $(patsubst %.c,%.o,$(wildcard *.c))
TARGET = serial_main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean :
	rm -f *.o *.out

print-%  : ; @echo $* = $($*)