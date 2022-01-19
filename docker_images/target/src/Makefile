TARGET = main
CC = gcc
CFLAGS = -pthread -Wall -m32 -g

OBJ = main.o
DEPS = main.h

all: $(TARGET)

%o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(TARGET) *.o
