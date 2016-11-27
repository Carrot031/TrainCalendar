SRCS=$(wildcard *.c)
TARGET=nextday.tcplugin
CC=gcc -fPIC `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS=-shared
$(TARGET):$(SRCS)
	$(CC) $(SRCS) $(LDFLAGS) -o $(TARGET)
