# Embedded toolchain test
In order to practice working with the GNU avr toolchain, I am working on creating and testing my own arduino board io abstraction and tests.

Things required in order to run this project:
- An arduino uno
- GNU avr toolchain installed (tested on linux/wsl)
    - GNU make
    - avr-gcc
    - avrdude
    - avr-libc (not used yet)

What I've done up to this point
- Implemented my own io abstraction library (`arduino_uno_io.h`) with basic functions emulating the ones in Arduino C++
    - pinMode
    - digitalWrite
    - digitalRead
- A simple blink program (`main.c`)

To run, update the relevant makefile constants and from the command line run `make`


TODO
- Add some unit testing to be run in the AVR
- Add some unit testing to be run in the PC