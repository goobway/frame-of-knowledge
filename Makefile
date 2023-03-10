# compiler
CC = gcc

# compiler flags
# -Wall flag turns on compiler warnings
CFLAGS = -Wall
INCLUDES = -I/home/sdp19/rpi_ws281x
LIBS= -lws2811 -lwiringPi -lm

# building the file
SOURCES = main.c matrix.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

.$(OBJECTS):%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o  $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)