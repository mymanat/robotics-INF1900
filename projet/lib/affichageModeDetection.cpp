#define F_CPU 8000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "memoire.h"
#include "capteur.h"

const char *categories[] = {"DANGER", "ATTENTION", "OK"};
uint8_t categorie[3];

uint8_t getCategorie(float valeur)
{
    if (float(valeur) > 10 && float(valeur) < 20)
    {
        return 0;
    }
    else if (float(valeur) > 20 && float(valeur) < 50)
    {
        return 1;
    }
    else if (float(valeur) > 50)
    {
        return 2;
    }
}

uint8_t getLenght(uint8_t categorie)
{
    if (categorie == 0)
        return 7;
    else if (categorie == 1)
        return 10;
    else
        return 3;
}

bool isEqual(uint8_t manoeuvre[3], uint8_t categorieRecues[3])
{
    for (uint8_t i = 0; i < 3; i++)
    {
        if (manoeuvre[i] != categorieRecues[i])
            return false;
    }
    return true;
}

char getManoeuvreAFaire(uint8_t categorie1, uint8_t categorie2, uint8_t categorie3)
{
    char manoeuvreAFaire;
    uint8_t manoeuvre1[3] = {2, 1, 1};
    uint8_t manoeuvre2[3] = {1, 1, 2};
    uint8_t manoeuvre3[3] = {0, 0, 0};
    uint8_t manoeuvre4[3] = {2, 2, 0};
    uint8_t manoeuvre5[3] = {0, 2, 2};
    // uint8_t categorieRecues[3] = {2, 1, 1};
    uint8_t categorieRecues[3] = {categorie1, categorie2, categorie3};

    if (isEqual(manoeuvre1, categorieRecues))
        manoeuvreAFaire = '1';

    else if (isEqual(manoeuvre2, categorieRecues))
        manoeuvreAFaire = '2';

    else if (isEqual(manoeuvre3, categorieRecues))
        manoeuvreAFaire = '3';

    else if (isEqual(manoeuvre4, categorieRecues))
        manoeuvreAFaire = '4';

    else if (isEqual(manoeuvre5, categorieRecues))
        manoeuvreAFaire = '5';

    else
        manoeuvreAFaire = '-';

    return manoeuvreAFaire;
}

void affichageModeDetection(uint8_t frequence)
{
    char affichageDistance1[11];
    char affichageDistance2[11];
    char affichageDistance3[11];
    transmissionUSART('-');
    transmissionUSART(' ');
    transmissionUSART('G');
    transmissionUSART(':');
    // Lecture du premier capteur
    PORTA &= ~(1 << PA2) & ~(1 << PA3);
    float distance1 = lectureDistanceCAN();
    dtostrf(distance1, 5, 1, affichageDistance1);
    for (uint8_t i = 1; i < 5; i++)
    {
        transmissionUSART(affichageDistance1[i]);
    }
    transmissionUSART(' ');
    transmissionUSART('C');
    transmissionUSART(':');
    // Lecture du deuxieme capteur
    PORTA &= ~(1 << PA3);
    PORTA |= 1 << PA2;
    float distance2 = lectureDistanceCAN();
    dtostrf(distance2, 5, 1, affichageDistance2);
    for (uint8_t i = 1; i < 5; i++)
    {
        transmissionUSART(affichageDistance2[i]);
    }
    transmissionUSART(' ');
    transmissionUSART('D');
    transmissionUSART(':');
    // Lecture du troisieme capteur
    PORTA &= ~(1 << PA2);
    PORTA |= 1 << PA3;
    float distance3 = lectureDistanceCAN();
    dtostrf(distance3, 5, 1, affichageDistance3);
    for (uint8_t i = 1; i < 5; i++)
    {
        transmissionUSART(affichageDistance3[i]);
    }
    transmissionUSART('-');
    transmissionUSART(' ');
    transmettreChainePc2(categories[getCategorie(distance1)], getLenght(getCategorie(distance1)), 1);
    transmissionUSART('|');
    transmettreChainePc2(categories[getCategorie(distance2)], getLenght(getCategorie(distance2)), 1);
    transmissionUSART('|');
    transmettreChainePc2(categories[getCategorie(distance3)], getLenght(getCategorie(distance3)), 1);
    transmissionUSART('(');
    transmissionUSART(getManoeuvreAFaire(getCategorie(distance1), getCategorie(distance2), getCategorie(distance3)));
    transmissionUSART(')');
    transmissionUSART('\n');
}