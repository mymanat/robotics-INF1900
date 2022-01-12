#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <math.h>
#include "can.h"
#include "memoire.h"
#include "minuterie.h"
#define SORTIE 0xff

float lectureDistanceCANInterne()
{
  can objet = can();
  uint16_t adcVal = objet.lecture(1); // lecture --> entre 0 et 1023
  // règle pour interpréter la distance :
  // Y = 29,28*X^(-0,1,156)
  // Y : distance (cm) et X : analog voltage output (V)
  float distance = float(adcVal);
  distance = distance / 1023.0 * 4.5;   //met valeur sur 1023 en volt pour la fonction
  if ((distance >= 0.4)&&(distance <= 0.54) )
    distance = 29.46047* (pow(distance, (-1.16838))); //calcul la distance entre 60cm et 80 cm
  else if ((distance > 0.54)&&(distance <= 0.62)) 
    distance = 29.17351* (pow(distance, (-1.14990)));      //calcul la distance entre 50 cm et 60 cm
  else if ((distance > 0.62)&&(distance <= 0.75)) 
    distance = 28.9957933 * (pow(distance, (-1.1392422)));  //calcul la distance entre 40 cm et 50 cm
  else
    distance = 29.27995* (pow(distance, (-1.15612)));  //calcul la distance entre 10cm et 40 cm
  return distance;
}

float lectureDistanceCANExterne()
{
  uint8_t sommeDistance;

  //D7
  //PORTB = 1 << PB2 | 1 << PB3 | 1 << PB4;
  PORTB |= 1 << PB2 | 1 << PB3 | 1 << PB4;
  _delay_ms(1);
  uint8_t distanceD7 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance = distanceD7 << PB0;

  //D6
  //PORTB = 1 << PB3 | 1 << PB4;
  PORTB |= 1 << PB3 | 1 << PB4;
  PORTB &= ~(1 << PB2);
  _delay_ms(1);
  uint8_t distanceD6 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance |= distanceD6 << PB1;

  //D5
  //PORTB = 1 << PB2 | 1 << PB4;
  PORTB |= 1 << PB2 | 1 << PB4;
  PORTB &= ~(1 << PB3);
  _delay_ms(1);
  uint8_t distanceD5 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance |= distanceD5 << PB2;

  //D4
  //PORTB = 1 << PB4;
  PORTB |= 1 << PB4;
  PORTB &= ~(1 << PB2) & ~(1 << PB3);
  _delay_ms(1);
  uint8_t distanceD4 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance |= distanceD4 << PB3;

  //D3
  //PORTB = 1 << PB2 | 1 << PB3;
  PORTB |= 1 << PB2 | 1 << PB3;
  PORTB &= ~(1 << PB4);
  _delay_ms(1);
  uint8_t distanceD3 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance |= distanceD3 << PB4;

  //D2
  //PORTB = 1 << PB3;
  PORTB |= 1 << PB3;
  PORTB &= ~(1 << PB2) & ~(1 << PB4);
  _delay_ms(1);
  uint8_t distanceD2 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance |= distanceD2 << PB5;

  //D1
  //PORTB = 1 << PB2;
  PORTB |= 1 << PB2;
  PORTB &= ~(1 << PB3) & ~(1 << PB4);
  _delay_ms(1);
  uint8_t distanceD1 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance |= distanceD1 << PB6;

  //D0
  //PORTB = 0;
  PORTB &= ~(1 << PB2) & ~(1 << PB3) & ~(1 << PB4);
  _delay_ms(1);
  uint8_t distanceD0 = (PINB & (1 << PB1)) >> PB1;
  sommeDistance |= distanceD0 << PB7;

  float distance = float(sommeDistance);
  distance = distance / 255.0 * 4.5;    //met valeur sur 1023 en volt pour la fonction
  if ((distance >= 0.4)&&(distance <= 0.54) )
    distance = 29.46047* (pow(distance, (-1.16838))); //calcul la distance entre 60cm et 80 cm
  else if ((distance > 0.54)&&(distance <= 0.62)) 
    distance = 29.17351* (pow(distance, (-1.14990)));      //calcul la distance entre 50 cm et 60 cm
  else if ((distance > 0.62)&&(distance <= 0.75)) 
    distance = 28.9957933 * (pow(distance, (-1.1392422)));  //calcul la distance entre 40 cm et 50 cm
  else
    distance = 29.27995* (pow(distance, (-1.15612)));  //calcul la distance entre 10cm et 40 cm
  return distance;
}

float lectureDistanceCAN()
{
  float distance;
  if ((PINA & (1 << PA0)) >> PA0)
  {
    //Lecture des capteurs avec le CAN externe
    distance = lectureDistanceCANExterne();
  }
  else
  {
    //Lecture des capteurs avec le CAN interne
    distance = lectureDistanceCANInterne();
  }

  return distance;
}
