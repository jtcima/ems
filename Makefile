CC = gcc
CFLAGS = -Wall -Wextra -Wformat -L/usr/lib/x86_64-linux-gnu 

TARGET = ems
SOURCES = main.c 


all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) $? -o $(TARGET) -lsqlite3 

main.o: $(SOURCES)
	$(CC) $(CFLAGS) -c $? -o $@

clean:
	rm -rf *.o $(TARGET)