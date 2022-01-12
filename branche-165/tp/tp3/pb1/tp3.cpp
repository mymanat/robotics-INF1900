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



bool PWM(double a)
{
  if (a>=0.75)
    return false;
  else
    return true;
}

int main()
{
  const int cycle= 1;
  const int processeur_frequence= 8000000;
  double periode= cycle/processeur_frequence;

  DDRA = 0xff; // PORT A est en mode sortie
  int rouge= 0x02;
  int vert= 0x01;
  int eteint= 0x00;

  for(;;)  // boucle sans fin
  {
    PORTA= rouge;
    _delay_ms(250);
    double a=0.25;
    double b=0.75;
    double delai_a= a*periode;
    double delai_b= b*periode;

    while(PWM (a))
    {
      PORTA= eteint;
      _delay_us(delai_a);
      PORTA= rouge;
      _delay_us(delai_b);
      a+=0.025;
      b-=0.025;
    }
    PORTA=eteint;
    _delay_ms (2000);

    PORTA= vert;
    _delay_ms(500);
    a=0.25;
    b=0.75;

    while(PWM (a))
    {
      PORTA= eteint;
      _delay_us(delai_a);
      PORTA= vert;
      _delay_us(delai_b);
      a+=0.025;
      b-=0.025;
    }
    PORTA=eteint;
    _delay_ms (2000);
    

    /*_delay_ms (262.14);
    PORTA = 0x2; 

    _delay_ms (262.14);
    PORTA = 0x0;

    _delay_ms (262.14);
    PORTA = 0x1;

    _delay_ms (262.14);
    PORTA = 0x0;

    
    


   */ 

    
  }
  return 0; 
}




