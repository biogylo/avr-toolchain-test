#include "arduino_uno_io.h"

void setup()
{
    pinMode(6, OUTPUT);
    pinMode(8, OUTPUT);
}

void loop()
{
    // go to sleep for an arbitrary amount of time
    for (long i = 0; i < 1000; i++)
    {
        digitalWrite(6, HIGH);
        digitalWrite(8, HIGH);
    }

    // go to sleep for an arbitrary amount of time
    for (long i = 0; i < 1000; i++)
    {
        digitalWrite(6, LOW);
        digitalWrite(8, LOW);
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