///////////////////////////////////////////////////////////////////////////////
// Title:       arduino_uno_io.h
// Description: The header file for an input and output abstraction
//              C library for the Arduino UNO
// Author:      Juan Francisco Navarro
// Email:       navarro.juan@uabc.edu.mx
///////////////////////////////////////////////////////////////////////////////

#define ISR_pin2 ISR(INT1_vect)
// An enumeration that represents the mode of an Arduino UNO pin.
enum Mode
{
    OUTPUT,
    INPUT_TRISTATE,
    INPUT_PULLUP,
};

// An enumeration that represents a logic level value.
enum Level
{
    LOW,
    HIGH
};

/** Sets the mode of a digital pin in the Arduino UNO.
 * @param arduino_pin_number A number from 0 to 13 that represents an arduino UNO's digital pins
 * @param mode Can be any of: OUTPUT, INPUT_PULLUP, INPUT_TRISTATE (Variants of the Mode enum)
 */
void pinMode(unsigned char arduino_pin_number, enum Mode mode);

/** Reads the logic level of a digital pin in the Arduino UNO.
 * @param arduino_pin_number A number from 0 to 13 that represents an arduino UNO's digital pins
 * @returns The logic level of the pin, which can be either the LOW, or HIGH variants of the Level enum
 */
enum Level digitalRead(unsigned char arduino_pin_number);

/** Writes the logic level of a digital pin in the Arduino UNO.
 * Assumes the digital pin was set as OUTPUT via pinMode()
 * @param arduino_pin_number A number from 0 to 13 that represents an arduino UNO's digital pins
 * @param level The logic level to set the pin, which can be either the LOW, or HIGH variants of the Level enum
 */
void digitalWrite(unsigned char arduino_pin_number, enum Level level);

void enablePin2Interrupt(); // TODO: require a function pointer and bind it to the interrupt

// Globally enables interrupts in the MCU
void enableInterrupts();
unsigned short analogRead(unsigned char analog_pin);