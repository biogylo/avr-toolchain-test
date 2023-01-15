enum Mode
{
    OUTPUT,
    INPUT_TRISTATE,
    INPUT_PULLUP,
};

enum Level
{
    LOW,
    HIGH
};

void pinMode(unsigned char arduino_pin_number, enum Mode mode);
enum Level digitalRead(unsigned char arduino_pin_number);
void digitalWrite(unsigned char arduino_pin_number, enum Level level);