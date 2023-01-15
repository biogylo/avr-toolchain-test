///////////////////////////////////////////////////////////////////////////////
// Title:       main.c
// Description: The source file for a main script that shows usage of the
//              arduino_uno_io library so that it can be tested on an Arduino UNO
// Author:      Juan Francisco Navarro
// Email:       navarro.juan@uabc.edu.mx
///////////////////////////////////////////////////////////////////////////////
#include "arduino_uno_io.h"

#include "avr/interrupt.h"

ISR_pin2
{
    digitalWrite(8, digitalRead(3));
}

void setup()
{
    enablePin2Interrupt();
    enableInterrupts();
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
}

void loop()
{
    // go to sleep for an arbitrary amount of time
    for (long i = 0; i < 1000; i++)
    {
        digitalWrite(6, HIGH);
        digitalWrite(7, LOW);
    }

    // go to sleep for an arbitrary amount of time
    for (long i = 0; i < 1000; i++)
    {
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
    }
    if (analogRead(1) > 900)
    {
        digitalWrite(9, HIGH);
    }
    else
    {
        digitalWrite(9, LOW);
    }
}

int main()
{

    setup();
    while (1)
    {
        loop();
    }
}