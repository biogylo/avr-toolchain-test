#define PORTD *((volatile unsigned char *)0x2B)
#define DDRD *((volatile unsigned char *)0x2A)

// Create stuff to abstract away pin value setting

void setup()
{
    DDRD |= 0b01000000;
}

void loop()
{
    // by setting the 6th bit on this register to 1
    // It is setting the bit that controls physical pin 13, and setting it to high
    // using bitwise OR to turn on the 6th bit without affecting the other bits in PORTD
    PORTD |= 0b01000000;

    // go to sleep for an arbitrary amount of time
    for (long i = 0; i < 100000; i++)
    {
        // to make sure the compiler doesn't optimize this out, continue
        // setting the 6th bit of PORTD to 1
        PORTD |= 0b01000000;
    }
    // setting PORTD 6th bit to 0 sets pins PORTD controls to low
    PORTD &= 0b11011111;
    // go to sleep for an arbitrary amount of time
    for (long i = 0; i < 100000; i++)
    {
        // to make sure the compiler doesn't optimize this out, continue
        // setting PORTD 6th bit to 0
        PORTD &= 0b10111111;
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