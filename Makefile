CC=avr-gcc
all:
	make info
	make clean
	make compile
	make launch

compile: source/main.c
	$(CC) -mmcu=atmega328p source/main.c --output build/main.o -nodevicelib

launch:
	avrdude \
		-v \
		-p atmega328p \
		-c arduino \
		-P /dev/ttyUSB0 \
		-U build/main.o

clean:
	rm -rf build/*

info:
	file source/*
	file build/*

