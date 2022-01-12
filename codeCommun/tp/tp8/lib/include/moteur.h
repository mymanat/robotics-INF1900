/*
  Nom    : tp7, lib
  Description : programme qui regroupe plusieurs fonctions
                utiles en lien le moteur comme faire tourner 
                les roues 
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov      - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

#pragma once
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

void ajustementPWMmateriellePhaseCorrecte8Bits(uint16_t pourcentage1, uint16_t pourcentage2);
void changerVitesseAvecLuminosite(uint8_t lumBasse, uint8_t lumAmbiante);
