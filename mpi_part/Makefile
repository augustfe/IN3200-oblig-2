CC = mpicc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = $(addprefix ../serial_part/,allocate_2D_array.o compute_numerical_error.o deallocate_2D_array.o) $(patsubst %.c,%.o,$(wildcard *.c))
TARGET = mpi_main.exe

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean :
	rm -f *.o *.out

print-%  : ; @echo $* = $($*)