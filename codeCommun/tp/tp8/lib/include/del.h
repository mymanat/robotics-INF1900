/*
  Nom    : tp7, lib
  Description : programme qui regroupe plusieurs fonctions
                utiles en lien les del comme les allumer ou
                changer leur couleur
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov      - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

#pragma once
#include <avr/io.h>
#include <util/delay.h>

void allumerDel(const uint8_t couleur, volatile uint8_t &port);

void allumerDelAmbre(volatile uint8_t &port);

void allumerDelBouton(const uint8_t couleur, const uint8_t bouton, volatile uint8_t &port);

bool antiRebond(const uint8_t bouton);
