/*
  Nom    : tp7, exec
  Description : programme qui fait varier la couleur d'une DEL
                en fonction de l'intensité lumineuse 
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov      - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include "can.h"

void ajusterDelCan(const uint8_t palier1, const uint8_t palier2, const uint8_t palier3);
void ajusterDelPWM(uint16_t pourcentage, uint16_t signal);
