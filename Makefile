# compiler
CC = g++

# compiler flags
# -Wall flag turns on compiler warnings
CFLAGS = -Wall -w
INCLUDES = -I/home/sdp19/rpi_ws281x -L/home/sdp19/tflite/tflite-dist/libs/linux_x64
LIBS = -lws2811 -lwiringPi -lm -ldl -ltensorflowlite -lcurl

# building the file
SOURCES = main.cpp display.cpp numbers.cpp upper.cpp lower.cpp sketches.cpp ssd1306.cpp classify_input.cpp client.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJECTS) $(LIBS)

$(OBJECTS):%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o  $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)