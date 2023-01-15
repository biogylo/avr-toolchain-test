CC=avr-gcc
ARDUINO_SERIAL_PORT=/dev/ttyUSB0

all:
	make clean
	make compile
	make info
	make launch

compile: 
	mkdir -p build
	$(CC) -mmcu=atmega328p source/*.c --output build/main.o -nodevicelib

launch:
	avrdude \
		-v \
		-p atmega328p \
		-c arduino \
		-P ${ARDUINO_SERIAL_PORT} \
		-U build/main.o

clean:
	rm -rf build/*

info:
	file source/*
	file build/*

