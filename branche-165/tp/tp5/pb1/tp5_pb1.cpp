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
#include <avr/eeprom.h>

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie
  const uint8_t ROUGE = 0x01;
  const uint8_t VERT = 0x02;
  const uint8_t ETEINT = 0x00;

  uint8_t stringOfData[48] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*\0";
  eeprom_write_block((const void *)&stringOfData, (void *)0x0000, sizeof(stringOfData));


  uint8_t stringOfData2[48];
  eeprom_read_block((void *)&stringOfData, (const void *)0x0000, 44);

  
  bool identique = false;

  for(int i=0; i < sizeof(stringOfData); i++)
  {
    if (stringOfData[i] == stringOfData2[i])
    {
      identique = true;
    }
    else
    {
      identique = false;
      break;
    }
  }

  if (identique == true)
  {
    PORTA = VERT;
  }
  else
  {
    PORTA = ROUGE;
  }

  return 0;
}


