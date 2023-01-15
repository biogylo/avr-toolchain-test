///////////////////////////////////////////////////////////////////////////////
// Title:       arduino_uno_io.h
// Description: The source file for an input and output abstraction
//              C library for the Arduino UNO. It has basic input/output
//              hardware abstraction for an Arduino UNO board with the
//              ATmega328p microcontroller
// Author:      Juan Francisco Navarro
// Email:       navarro.juan@uabc.edu.mx
///////////////////////////////////////////////////////////////////////////////

#include "arduino_uno_io.h"

// Address location of registers in the ATmega328p
#define PINB 0x23
#define DDRB 0x24
#define PORTB 0x25

#define PINC 0x26
#define DDRC 0x27
#define PORTC 0x28

#define PIND 0x29
#define DDRD 0x2A
#define PORTD 0x2B

// A struct that has the information necessary to represent a digital pin in the ATmega328P
struct DigitalPin
{
    unsigned int register_address;
    unsigned char offset;
};

/** This method abstracts away PINx register addresses by storing relevant information in the DigitalInfo struct
 * @param arduino_pin_number A number from 0 to 13 that represents an arduino UNO's digital pin
 * @returns A DigitalPin struct that has the information necessary to represent a digital pin in the ATmega328P
 */
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

/**
 * @param digital_pin A DigitalPin struct
 * @returns The address number of the pin register the digital_pin is in
 */
static unsigned int get_pin_register_address(struct DigitalPin digital_pin)
{
    return digital_pin.register_address;
};

/**
 * @param digital_pin A DigitalPin struct
 * @returns The address number of the port register of the digital_pin
 */
static unsigned int get_port_register_address(struct DigitalPin digital_pin)
{
    return digital_pin.register_address + 1;
};

/**
 * @param digital_pin A DigitalPin struct
 * @returns The address number of the data direction register of the digital_pin
 */
static unsigned int get_data_direction_register_address(struct DigitalPin digital_pin)
{
    return digital_pin.register_address + 2;
};

/** It sets the logic level of a bit in a register to the desired value
 * @param register_address The address of a register
 * @param bit_offset The index of the bit to set in the register
 * @param level_to_set A Level enum variant (LOW, HIGH) that represent the desired level
 */
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

/** It reads the logic level of a bit in a register
 * @param register_address The address of a register
 * @param bit_offset The index of the bit to read in the register
 * @returns A Level enum variant (LOW, HIGH) that indicates the logic level of the bit in the register
 */
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
            pinMode(0..13, OUTPUT|INPUT_PULLUP|INPUT_TRISTATE)
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
