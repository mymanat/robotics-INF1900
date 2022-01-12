
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h> 


void PWM( double pourcentage, double frequence)
{
  const double temps= 2000;
  double cycle= frequence*temps;
  const int processeur_frequence= 8000000;
  double periode= (1/frequence)*1000;
  double a = pourcentage;
  double b = 1-pourcentage;

  double delai_a= a*periode;
  double delai_b= b*periode;

  int compteur= 0;

  while(compteur< (temps/periode))
  {
    PORTB=0x01;
    _delay_loop_2(delai_a);
    PORTB=0x00;
    _delay_loop_2(delai_b);
    compteur++;
  } 
}

/*void PWM( double pourcentage, double frequence)
{
  const double temps= 2000.0;
  double p = (1/frequence)*1000.0;
  double periode = frequence/800000;
  double a = pourcentage;
  double b = 1.0 - pourcentage;
  double delai_a = a*periode;
  double delai_b = b*periode;

  int compteur = 0;
  //while(compteur < (temps/periode))
  for(int i=0; i < 10; i++)
  {
    PORTB=0x01;
    PORTA = 0x01;
    _delay_loop_2(delai_a);
    PORTB=0x00;
    _delay_loop_2(delai_b);
    compteur++;
    PORTA = 0x02;
  } 
}*/

int main()
{
  DDRB = 0xff;
  PORTB = 0x02;

  for(;;)
  {
    PWM(0.0, 60);
    PWM(0.25, 60);
    PWM(0.50, 60);
    PWM(0.75, 60);
    PWM(1.0, 60);
    PWM(0.0, 400);
    PWM(0.25, 400);
    PWM(0.50, 400);
    PWM(0.75, 400);
    PWM(1.0, 400); 
  }

  return 0; 
}




