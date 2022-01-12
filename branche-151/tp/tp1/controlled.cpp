#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  unsigned short vert = 0b01;
  unsigned short rouge = 0b10;
  double delay = 3000;
  
  for(;;) // boucle sans fin
  {
    PORTA = vert;
    _delay_ms (delay);
    PORTA = rouge;
    _delay_ms (delay);
    }
    return 0;
}
