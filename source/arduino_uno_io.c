/*
Basic hardware abstraction for arduino uno board with atmega328p
*/
#include "arduino_uno_io.h"
// Address location of registers in the atmega
#define PINB 0x23
#define DDRB 0x24
#define PORTB 0x25

#define PINC 0x26
#define DDRC 0x27
#define PORTC 0x28

#define PIND 0x29
#define DDRD 0x2A
#define PORTD 0x2B

// Arduino digital pins

struct DigitalPin
{
    unsigned int register_address;
    unsigned char offset;
};

static inline struct DigitalPin get_digital_pin_from_number(unsigned char arduino_pin_number)
{
    // Assumes pin_number range is [0,13]
    struct DigitalPin digital_pin;
    digital_pin.offset = arduino_pin_number & 0b00000111; // Grab last three bits
    // If the fourth bit is set, then its pin B, otherwise its D
    if (arduino_pin_number & 0b00001000)
    {
        digital_pin.register_address = PINB;
    }
    else
    {

        digital_pin.register_address = PIND;
    }
    return digital_pin;
}

static unsigned int get_pin_register_address(struct DigitalPin digital_pin)
{
    return digital_pin.register_address;
};

static unsigned int get_port_register_address(struct DigitalPin digital_pin)
{
    return digital_pin.register_address + 1;
};

static unsigned int get_data_direction_register_address(struct DigitalPin digital_pin)
{
    return digital_pin.register_address + 2;
};

static inline void write_register_bit(unsigned int register_address,
                                      unsigned char bit_offset,
                                      enum Level level_to_set)
{
    unsigned char mask = 0b00000001 << bit_offset;
    volatile unsigned char *register_pointer = (volatile unsigned char *)register_address;
    if (level_to_set == HIGH)
    {
        *register_pointer |= mask;
    }
    else
    {
        *register_pointer &= ~mask;
    }
};
static inline enum Level read_register_bit(unsigned int register_address,
                                           unsigned char bit_offset)
{
    unsigned char mask = 0b00000001 << bit_offset;
    volatile unsigned char *register_pointer = (volatile unsigned char *)register_address;
    if (*register_pointer & mask) // Dereference and compare against mask
    {
        return HIGH;
    }
    return LOW;
};

void pinMode(unsigned char arduino_pin_number, enum Mode mode)
{
    /*
        Usage:
            pinMode(D0|D2|..|D13, OUTPUT|INPUT_PULLUP|INPUT_TRISTATE)
    */
    struct DigitalPin digital_pin = get_digital_pin_from_number(arduino_pin_number);
    unsigned int ddr_address = get_data_direction_register_address(digital_pin);
    unsigned int port_address = get_port_register_address(digital_pin);
    switch (mode)
    {
    case OUTPUT:
        write_register_bit(ddr_address,
                           digital_pin.offset,
                           HIGH);
        break;
    case INPUT_PULLUP:
        write_register_bit(ddr_address,
                           digital_pin.offset,
                           LOW);

        write_register_bit(port_address,
                           digital_pin.offset,
                           HIGH);
        break;

    case INPUT_TRISTATE:
        write_register_bit(ddr_address,
                           digital_pin.offset,
                           LOW);

        write_register_bit(port_address,
                           digital_pin.offset,
                           LOW);
        break;
    }
};

void digitalWrite(unsigned char arduino_pin_number, enum Level level)
{
    /*
        Usage:
            digitalWrite(0..13, LOW|HIGH)
            assumes the pin is already set as output
    */
    struct DigitalPin digital_pin = get_digital_pin_from_number(arduino_pin_number);
    unsigned int port_register_address = get_port_register_address(digital_pin);
    write_register_bit(port_register_address, digital_pin.offset, level);
};

enum Level digitalRead(unsigned char arduino_pin_number)
{
    /*
        Usage:
            digitalRead(0..13)
            assumes the pin is already set as input
    */
    struct DigitalPin digital_pin = get_digital_pin_from_number(arduino_pin_number);
    unsigned int pin_register_address = get_pin_register_address(digital_pin);
    return read_register_bit(pin_register_address, digital_pin.offset);
};
