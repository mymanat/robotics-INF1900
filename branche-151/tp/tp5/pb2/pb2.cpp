#include <avr/io.h>
#define F_CPU 8000000
#include <avr/eeprom.h>
#include <util/delay.h>

void initialisationUART(void)
{
  // 2400 bauds. Nous vous donnons la valeur des deux
  // premier registres pour vous éviter des complications
  UBRR0H = 0;
  UBRR0L = 0xCF;
  // permettre la réception et la transmission par le UART0
  UCSR0A = (1 << UDRE0);
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // Format des trames: 8 bits, 1 stop bits, none parity
  UCSR0C = (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
}

// De l'USART vers le PC
void transmissionUART(uint8_t donnee)
{
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  UDR0 = donnee;
}

int main()
{
  initialisationUART();
  DDRA = 0xFF;
  int8_t vert = 0b01;
  int8_t rouge = 0b10;
  char mots[37] = "Le simulateur SimulIDE en INF1900!\n\n";
  uint8_t i, j;
  for (i = 0; i < 100; i++)
  {
    for (j = 0; j < 35; j++)
    {
      transmissionUART(mots[j]);
    }
  }
  PORTA = rouge;
  _delay_ms(500);
  PORTA = vert;
}
