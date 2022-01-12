#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>


int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  DDRD = 0x00; // PORT D est en mode entree
  unsigned short eteint = 0b00;
  unsigned short couleur = 0b01;
  double delay = 10;
  
  for(;;)
  {
    if(PIND & 0x04)
    {
        _delay_ms (delay);
        if(PIND & 0x04)
        {
            PORTA = couleur;
        }
        else
        {
            PORTA = eteint;
        }
        }
    }
    return 0;
}
