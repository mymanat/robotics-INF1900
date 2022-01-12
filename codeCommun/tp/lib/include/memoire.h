/*
  Nom    : tp7, lib
  Description : programme qui regroupe plusieurs fonctions
                utiles en lien la mémoire, comme comment écrire
                ou lire de la mémoire eeprom et la transmettre
                au PC
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov      - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

void initialisationUART8Bits1StopBitNoneParity(void);
void transmissionUSART(uint8_t donnee);
uint8_t recevoirUSART(void);
void transmettreChainePc(uint8_t mots[], uint8_t nCaractere, uint8_t nTransmissions);
void lireEepromAPc(uint16_t adresse, uint8_t nCaractere, uint8_t nTransmissions);
void ecrireLireEepromAPc(uint8_t tableauAEcrire[], uint16_t adresse, uint8_t nCaractere, uint8_t nTransmissions);
