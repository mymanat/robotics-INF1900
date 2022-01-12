#pragma once
#define F_CPU 8000000
#include <avr/io.h>
#include <memoire.h>

#define moteurGauche 0
#define moteurDroite 1

void activer7Segments();
void desactiver7Segments();
void afficher7SegmentsChoix(uint8_t pourcentageMoteur, uint8_t moteur, bool isDecimal);
int puissanceSegmentDroit(uint8_t puissance, bool isDecimal);
int puissanceSegmentGauche(uint8_t puissance, bool isDecimal);
void afficher7SegmentsDemarrage();
