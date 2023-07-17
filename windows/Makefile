CC = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -Wformat -I/usr/x86_64-w64-mingw32/include 
LDFLAGS = -L/usr/x86_64-w64-mingw32/lib/
LIBS = -lsqlite3

TARGET = ems.exe
SOURCES = main.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS) $(LIBS) 

clean:
	rm -f $(TARGET)