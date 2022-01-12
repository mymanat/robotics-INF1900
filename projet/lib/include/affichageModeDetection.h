#pragma once
#define F_CPU 8000000
#include <avr/io.h>

uint8_t getCategorie(float valeur);
uint8_t getLenght(uint8_t categorie);
void affichageModeDetection(uint8_t frequence);
uint8_t getCategorie(float valeur);
char getManoeuvreAFaire(uint8_t categorie1, uint8_t categorie2, uint8_t categorie3);
