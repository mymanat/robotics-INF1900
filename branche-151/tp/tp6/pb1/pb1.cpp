#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include "can.h"

int main()
{
  can can1 = can();
  DDRA = 0xff;
  DDRB = 0x00;
  const uint8_t VERT = 0b01;
  const uint8_t ROUGE = 0b10;
  const uint8_t DELAIS = 10;
  const uint8_t PALIER_VERT= 0x00;
  const uint8_t PALIER_AMBRE= 0x05;
  const uint8_t PALIER_ROUGE= 0x08;

  while (true)
  {
    uint16_t adcVal = can1.lecture(0);
    if (adcVal >= PALIER_VERT && adcVal < PALIER_AMBRE)
    {
      PORTB = VERT;
    }
    else if (adcVal >= PALIER_AMBRE && adcVal < PALIER_ROUGE)
    {
      while (adcVal >= PALIER_AMBRE && adcVal < PALIER_ROUGE)
      {
        PORTB = ROUGE;
        _delay_ms(DELAIS);
        PORTB = VERT;
        _delay_ms(DELAIS);
        uint16_t adcVal = can1.lecture(0);
        if (adcVal < PALIER_AMBRE || adcVal >= PALIER_ROUGE)
        {
          break;
        }
      }
    }
    else if (adcVal >= PALIER_ROUGE)
    {
      PORTB = ROUGE;
    }
  }
}