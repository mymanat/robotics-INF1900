#include <avr/io.h>
#define F_CPU 8000000
#include <avr/eeprom.h>
#include <util/delay.h>

int main()
{
  DDRA = 0xFF;
  int8_t vert = 0b01;
  int8_t rouge = 0b10;
  char tableau[] = {"*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*"};
  char tableauLu[sizeof(tableau) / sizeof(char)];
  eeprom_write_block((const void *)&tableau, (void *)0, sizeof(tableau));
  eeprom_read_block((void *)&tableauLu, (const void *)0, sizeof(tableau));

  // if (strncmp(*tableau, *tableauLu, sizeof(tableau)))
  //   PORTA = vert;
  // else
  //   PORTA = rouge;
  // return 0;
  for (uint8_t i = 0; i < sizeof(tableau); i++)
  {
    if (tableau[i] == tableauLu[i])
      PORTA = vert;
    else
      PORTA = rouge;
  }
}