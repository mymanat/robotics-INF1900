/*
  Nom    : tp7, lib
  Description : programme qui regroupe plusieurs fonctions
                utiles en lien la minuterie comme l'initialiser 
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov      - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

#pragma once
#include <avr/io.h>
#include <util/delay.h>

void initialisationMinuterie1(void);
void partirMinuterieTimer1ModeCTCPrescaler1024(uint16_t duree);
