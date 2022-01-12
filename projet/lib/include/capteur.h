/*
  Nom    : projet
  Description : programme qui lit les données de distance à l'aide des capteurs 
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

// IL faut régler le port A du ciruit dans le main pour choisir quel capteur lire
float lectureDistanceCANInterne();
float lectureCANExterne(uint8_t pos);
float lectureDistanceCANExterne();
float lectureDistanceCAN();
