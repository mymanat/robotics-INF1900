/*
  Nom    : tp7, exec
  Description : programme qui teste que la librairie créée
                fonctionne correctement en incluant les .h de la librairie
                et en appelant des fonctions de la librairie (main bidon)
  équipe : 115165
  Auteurs: Mymanat Mohammed - 2068301
           Safa Ikhlef      - 2058906
           Ivan Ivanov      - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "del.h"
#include "moteur.h"
#include "memoire.h"
#include "minuterie.h"
#include "ajusterDel.h"
#define F_CPU 8000000
#define SORTIE 0xff
#define ENTREE 0x00
#define VERT 0x01
#define ROUGE 0x02
#define DELAIS 10
#define PALIER_VERT 0x00
#define PALIER_AMBRE 0x05
#define PALIER_ROUGE 0x08
#define adresse 0x0000
#define D4 0x10
#define D5 0x20
#define SECONDE 1000


int main()
{
    DDRB = SORTIE; // PORT B est en mode sortie
    DDRA = ENTREE; // PORT A est en mode entrée

    uint16_t lumBasse = 2.4/4*255; //seuil où la lumière est très basse
    uint16_t lumAmbiante = 3.0/4*255;

    initialisationUART8Bits1StopBitNoneParity();
    uint8_t stringOfData[48] = "Le simulateur SimulIDE en INF1900\n";
    eeprom_write_block((const void *)&stringOfData, (void *)adresse, sizeof(stringOfData));
    lireEepromAPc(adresse, 48, 50);
    uint8_t mots[35] = "Le simulateur SimulIDE en INF1900\n";
    transmettreChainePc(mots, 35, 100);
    ecrireLireEepromAPc(mots, adresse, 35, 50);

    
    for (;;)
    {
        allumerDel(VERT, PORTA);
        allumerDelAmbre(PORTA);
        allumerDelBouton(VERT, PIND, PORTA);
        ajusterDelCan(PALIER_VERT, PALIER_AMBRE, PALIER_ROUGE);
        ajustementPWMmateriellePhaseCorrecte8Bits(0, 0); //0 = 0%
        changerVitesseAvecLuminosite(lumBasse, lumAmbiante);
        ajusterDelPWM(191, D4);
    }
    initialisationMinuterie1();
    partirMinuterieTimer1ModeCTCPrescaler1024(SECONDE);
    return 0;
}