#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>

int main()
{
    DDRA = 0xff;
    unsigned short eteint = 0b00;
    unsigned short vert = 0b01;
    unsigned short rouge = 0b10;
    double periodeA = 2000.0;
    double periodeB = 2000.0;
    for (;;)
    {
        PORTA = rouge;
        periodeA = 2000.0;
        periodeB = 2000.0;
        do
        {
            PORTA = rouge;
            _delay_loop_2(periodeA);
            PORTA = eteint;
            _delay_loop_2(periodeB - periodeA);
            periodeA -= 2000.0/3000.0;
        } while (periodeA>0);
        PORTA = vert;
        periodeA = 2000.0;
        periodeB = 2000.0;
        do
        {
            PORTA = vert;
            _delay_loop_2(periodeA);
            PORTA = eteint;
            _delay_loop_2(periodeB - periodeA);
            periodeA -= 2000.0/3000.0;
        } while (periodeA>0);
    }
    return 0;
}