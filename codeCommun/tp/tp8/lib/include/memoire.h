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
#include <avr/io.h>
#include <util/delay.h>

void initialisationUART8Bits1StopBitNoneParity(void);
void transmissionUART(uint8_t donnee);
void transmettreChainePc(char mots[], uint8_t nCaractere, uint8_t nTransmissions);
void lireEepromAPc(uint8_t adresse, uint8_t nCaractere, uint8_t nTransmissions);
void ecrireLireEepromAPc(uint8_t tableauAEcrire[], uint8_t adresse, uint8_t nCaractere, uint8_t nTransmissions);
