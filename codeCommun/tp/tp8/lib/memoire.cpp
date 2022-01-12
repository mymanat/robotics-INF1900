#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#define SORTIE 0xff

void initialisationUART8Bits1StopBitNoneParity(void)
{
  // 2400 bauds. Nous vous donnons la valeur des deux
  // premier registres pour vous éviter des complications
  UBRR0H = 0;
  //UBRR0L = 0xCF;
  // permettre la réception et la transmission par le UART0
  UCSR0A = (1 << RXC0) | (1 << TXC0);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // Format des trames: 8 bits, 1 stop bits, none parity
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void transmissionUART(uint8_t donnee)
{
  // Documentation Atmel p.198
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = donnee;
}

void transmettreChainePc(char mots[], uint8_t nCaractere, uint8_t nTransmissions)
{

  for (uint8_t i = 0; i < nTransmissions; i++)
  {

    for (uint8_t j = 0; j < (nCaractere - 1); j++)
    {
      transmissionUART(mots[j]);
    }
  }
}

void lireEepromAPc(uint8_t adresse, uint8_t nCaractere, uint8_t nTransmissions)
{

  char tableauLu[nCaractere];
  eeprom_read_block((void *)&tableauLu, (const void *)adresse, nCaractere);

  transmettreChainePc(tableauLu, nCaractere, nTransmissions);
}

void ecrireLireEepromAPc(uint8_t tableauAEcrire[], uint8_t adresse, uint8_t nCaractere, uint8_t nTransmissions)
{
  char tableauLu[nCaractere];
  for (uint8_t i = 0; i < nCaractere; i++)
  {
    tableauLu[i] == tableauAEcrire[i];
  }
  eeprom_write_block((const void *)&tableauLu, (void *)adresse, sizeof(tableauLu));
  lireEepromAPc(adresse, nCaractere, nTransmissions);
}
