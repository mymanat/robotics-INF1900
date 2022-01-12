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

void initialisationUART(void)
{
  // 2400 bauds. Nous vous donnons la valeur des deux
  // premier registres pour vous éviter des complications
  UBRR0H = 0;
  UBRR0L = 0xCF;
  // permettre la réception et la transmission par le UART0
  UCSR0A = (1<<RXC0)|(1<<TXC0);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  // Format des trames: 8 bits, 1 stop bits, none parity
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

// De l'USART vers le PC
void transmissionUART(uint8_t donnee)
{
  // Documentation Atmel p.198
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) );
  /* Put data into buffer, sends the data */
  UDR0 = donnee;
}

int main()
{
  DDRA = 0xff; // PORT A est en mode sortie

  initialisationUART();

  uint8_t adresse = 0x0000;

  uint8_t stringOfData[48] = "Le simulateur SimulIDE en INF1900\n";
  eeprom_write_block((const void *)&stringOfData, (void *)adresse, sizeof(stringOfData));


  uint8_t mots[255];
  eeprom_read_block((void *)&mots, (const void *)adresse, 255);


  uint8_t i, j;

  for (i = 0; i < 100; i++)
  {

    for (j = 0; j < 34; j++)
    {
      transmissionUART(mots[j]);
    }
  }

  return 0;
}
