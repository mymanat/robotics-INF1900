/*
 * Nom: compteur 32 bits
 * Copyright (C) 2005 Matthew Khouzam
 * License http://www.gnu.org/copyleft/gpl.html GNU/GPL
 * Description: Ceci est un exemple simple de programme 
 * Version: 1.1
 */



// signed char     int8_t 

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 


int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  rouge= 0x01;
  vert=0x02;
  eteint=0x00;


  for(;;)  // boucle sans fin
  {
    int a=1000;
    int const b=1000;


    while(a>0)
    {
      PORTA= rouge;
      _delay_ms (a);
      PORTA= eteint;
      _delay_ms(b-a);
      a--;
    }

    /*_delay_ms (262.14);
    PORTA = 0x2; 

    _delay_ms (262.14);
    PORTA = 0x0;

    _delay_ms (262.14);
    PORTA = 0x1;

    _delay_ms (262.14);
    PORTA = 0x0;

    
    
    for(int i=0;i<=50;++i)
    {
        PORTA= 0x2;
        _delay_ms (10);

        PORTA=0x1;
        _delay_ms (10);
    
    }

    

    
  }
  return 0; 
}

*/


