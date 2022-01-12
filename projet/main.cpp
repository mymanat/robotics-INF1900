/*
  Nom    : projet final, exec
  Description : programme qui lit les instructions inscrites sur la mémoire eeprom
                et indique ce que chaque instructions doit faire
  équipe : 115165
  Auteurs: Mymanat Mohammed         - 2068301
           Safa Ikhlef              - 2058906
           Ivan Ivanov              - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */

////////////////////////////////////////////////////////////////
//État présent   Entrée D2    D3    État suivant     Sortie D
//INIT                  1     X           E1           ETEINT
//INIT                  X     1           INIT         ETEINT
//E1                    1     X           E2           ROUGE
//E1                    X     1           E3           ROUGE
//E2                    1     X           INIT         VERT
//E2                    X     1           INIT         VERT
//E3                    X     1           E2           ETEINT
//E3                    X     1           E4           ETEINT
///////////////////////////////////////////////////////////////

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "moteur.h"
#include "memoire.h"
#include "del.h"
#include "minuterie.h"
#include "clavier.h"
#include "capteur.h"
#include "affichage7Segments.h"
#include "affichageModeDetection.h"

#define ENTREE 0x00
#define SORTIE 0xff

#define SECONDE 7811
#define DEMI_SECONDE 3905
#define QUART_SECONDE 1952
#define CENTIEME_SECONDE 77

#define DANGER 0
#define ATTENTION 1
#define OK 2

#define BOUTON_C2_APPUYE (PINC & (1 << PC2))
#define BOUTON_C3_APPUYE (PINC & (1 << PC3))
#define BOUTON_C4_APPUYE (PINC & (1 << PC4))
#define BOUTON_C5_APPUYE (PINC & (1 << PC5))
#define BOUTON_C6_APPUYE (PINC & (1 << PC6))
#define BOUTON_C7_APPUYE (PINC & (1 << PC7))

volatile uint8_t minuterieExpiree = 0;
volatile uint8_t compteurCentiemeSeconde = 0;
volatile uint8_t compteurSeconde = 0;
volatile uint8_t compteurMinute = 0;

volatile bool isDecimal = true;
volatile uint16_t frequence = SECONDE;
volatile char modeAffichage = 'R';

enum ETAT
{
    ModeDemarrage,
    ModeDetection,
    ModeManoeuvre
};

volatile ETAT etat = ModeDemarrage;

// Routine d'interruption pour le clavier sur le port C
ISR(PCINT2_vect)
{
    uint8_t message1[] = {"\nLe bouton "};
    uint8_t message2[] = {" du clavier a ete appuye.\n"};
    if (BOUTON_C2_APPUYE)
    {
        initialisationPD4aPD2Output();
        if (BOUTON_C5_APPUYE)
        {
            while (BOUTON_C5_APPUYE)
            {
                continue;
            }
            frequence = QUART_SECONDE;
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = '4';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
        else if (BOUTON_C6_APPUYE)
        {
            while (BOUTON_C6_APPUYE)
            {
                continue;
            }
            modeAffichage = 'C';
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = 'C';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
        else if (BOUTON_C7_APPUYE)
        {
            while (BOUTON_C7_APPUYE)
            {
                continue;
            }
            isDecimal = !isDecimal;
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = '#';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
    }
    if (BOUTON_C3_APPUYE)
    {
        initialisationPD4aPD2Output();
        if (BOUTON_C5_APPUYE)
        {
            while (BOUTON_C5_APPUYE)
            {
                continue;
            }
            frequence = DEMI_SECONDE;
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = '2';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
        else if (BOUTON_C6_APPUYE)
        {
            while (BOUTON_C6_APPUYE)
            {
                continue;
            }
            modeAffichage = 'V';
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = 'V';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
        else if (BOUTON_C7_APPUYE)
        {
            while (BOUTON_C7_APPUYE)
            {
                continue;
            }
            PORTA |= (1 << PA0);
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = 'E';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
    }
    if (BOUTON_C4_APPUYE)
    {
        initialisationPD4aPD2Output();
        if (BOUTON_C5_APPUYE)
        {
            while (BOUTON_C5_APPUYE)
            {
                continue;
            }
            frequence = SECONDE;
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = '1';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
        else if (BOUTON_C6_APPUYE)
        {
            while (BOUTON_C6_APPUYE)
            {
                continue;
            }
            modeAffichage = 'R';
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = 'R';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
        else if (BOUTON_C7_APPUYE)
        {
            while (BOUTON_C7_APPUYE)
            {
                continue;
            }
            PORTA &= ~(1 << PA0);
            transmettreChainePc(message1, sizeof(message1) / sizeof(uint8_t), 1);
            uint8_t bouton = 'I';
            transmissionUSART(bouton);
            transmettreChainePc(message2, sizeof(message2) / sizeof(uint8_t), 1);
            initialisationPD7aPD5Output();
            initialisationInterruptPCINT2();
        }
    }
}

void initialisationBoutonD2(void)
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontroleur n'est pas prêt...
    cli();
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA = 0;
    // EICRA |= (1 << ISC11) | (1 << ISC10);
    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

ISR(INT0_vect)
{
    // code a completer pour interruption bouton D2
    // boutonPoussoir = 1;
    if (etat == ModeDetection)
    {
        etat = ModeManoeuvre;
        EIFR |= (1 << INTF0);
    }
}

ISR(TIMER1_COMPA_vect)
{
    minuterieExpiree = 1;
}

ISR(TIMER0_COMPA_vect)
{
    compteurCentiemeSeconde++;
    if (compteurCentiemeSeconde == 100)
    {
        compteurSeconde++;
        compteurCentiemeSeconde = 0;
    }
    if (compteurSeconde == 60)
    {
        compteurMinute++;
        compteurSeconde = 0;
    }
}

void ininialiserInputOutput()
{
    DDRA = SORTIE;
    DDRA &= ~(1 << PA1);

    DDRB = SORTIE;
    DDRB &= ~(1 << PB1);

    DDRC = 1 << PC7 | 1 << PC6 | 1 << PC5 | 1 << PC1 | 1 << PC0;
    PORTC = 1 << PC7 | 1 << PC6 | 1 << PC5;

    DDRD = SORTIE;
    DDRD &= ~(1 << PD2);
}

char affichageMinutes[11];
char affichageSecondes[11];
char affichageCenitiemeSecondes[11];

void affichageTempsEcoule()
{
    if (compteurMinute < 10)
    {
        transmissionUSART('0');
        dtostrf(compteurMinute, 2, 0, affichageMinutes);
        for (uint8_t j = 1; j < 7; j++)
        {
            transmissionUSART(affichageMinutes[j]);
        }
    }
    else
    {
        dtostrf(compteurMinute, 3, 0, affichageMinutes);
        for (uint8_t j = 1; j < 7; j++)
        {
            transmissionUSART(affichageMinutes[j]);
        }
    }
    transmissionUSART(':');

    if (compteurSeconde < 10)
    {
        transmissionUSART('0');
        dtostrf(compteurSeconde, 2, 0, affichageSecondes);
        for (uint8_t j = 1; j < 7; j++)
        {
            transmissionUSART(affichageSecondes[j]);
        }
    }
    else
    {
        dtostrf(compteurSeconde, 3, 0, affichageSecondes);
        for (uint8_t j = 1; j < 7; j++)
        {
            transmissionUSART(affichageSecondes[j]);
        }
    }
    transmissionUSART('.');

    if (compteurCentiemeSeconde < 10)
    {
        transmissionUSART('0');
        dtostrf(compteurCentiemeSeconde, 2, 0, affichageCenitiemeSecondes);
        for (uint8_t j = 1; j < 7; j++)
        {
            transmissionUSART(affichageCenitiemeSecondes[j]);
        }
    }
    else
    {
        dtostrf(compteurCentiemeSeconde, 3, 0, affichageCenitiemeSecondes);
        for (uint8_t j = 1; j < 7; j++)
        {
            transmissionUSART(affichageCenitiemeSecondes[j]);
        }
    }
}

char manoeuvre;

int main()
{
    etat = ModeDemarrage;
    initialisationMinuterie();
    partirMinuterieTimer0ModeCTCPrescaler1024(CENTIEME_SECONDE);
    ininialiserInputOutput();
    initialisationInterruptPCINT2();
    initialisationBoutonD2();

    float distance1;
    float distance2;
    float distance3;

    float lastDistance1;
    float lastDistance2;
    float lastDistance3;

    bool lastDistance1Read = false;
    bool lastDistance2Read = false;
    bool lastDistance3Read = false;

    bool premiereLectureCaseV = false;
    bool premiereLectureCaseC = false;

    char affichageDistance1[11];
    char affichageDistance2[11];
    char affichageDistance3[11];

    //Case c declaration
    const char *categories[] = {"DANGER", "ATTENTION", "OK"};

    bool categorieDifferente = false;

    uint8_t categorieDistance1;
    uint8_t categorieDistance2;
    uint8_t categorieDistance3;

    uint8_t lastCategorieDistance1;
    uint8_t lastCategorieDistance2;
    uint8_t lastCategorieDistance3;

    bool transmissionDistanceFaite = false;
    bool transmissionFaite = false;

    uint16_t vitesse;
    
    uint8_t bps[6] = " bps\n";
    float baudRate;
    char affichagebaudRate[11];

    ininialiserInputOutput();
    initialisationInterruptPCINT2();
    initialisationUART8Bits1StopBitNoneParity();

    while (1)
    {
        switch (etat)
        {
        case ModeDemarrage:
            baudRate = F_CPU/(16*(UBRR0+1));
            dtostrf(baudRate, 5, 0, affichagebaudRate);
            for (uint8_t i = 1; i < 5; i++)
            {
                transmissionUSART(affichagebaudRate[i]);
            }
            transmettreChainePc(bps, 6, 1);
            afficher7SegmentsDemarrage();
            _delay_ms(2000);
            desactiver7Segments();

            // Moteurs PWM#####################
            PORTD |= (1 << PD3) | (1 << PD6);
            ajustementPWMmateriellePhaseCorrecte8Bits(254, 254);
            //#################################
            _delay_ms(1000);
            PORTD &= ~(1 << PD3) & ~(1 << PD6);
            _delay_ms(1000);
            ajustementPWMmateriellePhaseCorrecte8Bits(0, 0);
            PORTD &= ~(1 << PD4) & ~(1 << PD5);
            DDRD &= ~(1 << PD4) & ~(1 << PD5);
            etat = ModeDetection;
            break;

        case ModeDetection:
            switch (modeAffichage)
            {
            case 'R':
                initialisationMinuterie();
                minuterieExpiree = 0;
                partirMinuterieTimer1ModeCTCPrescaler1024(frequence);
                do
                {
                    if (!transmissionDistanceFaite)
                    {
                        affichageTempsEcoule();
                        affichageModeDetection(frequence);
                        transmissionDistanceFaite = true;
                    }
                } while (minuterieExpiree == 0);
                transmissionDistanceFaite = false;
                break;

            case 'V':
                //Lecture du premier capteur
                PORTA &= ~(1 << PA2) & ~(1 << PA3);
                if (!lastDistance1Read)
                {
                    lastDistance1 = lectureDistanceCAN();
                    lastDistance1Read = true;
                }
                else
                {
                    distance1 = lectureDistanceCAN();
                    lastDistance1Read = false;
                }
                //Lecture du deuxieme capteur
                PORTA &= ~(1 << PA3);
                PORTA |= 1 << PA2;
                if (!lastDistance2Read)
                {
                    lastDistance2 = lectureDistanceCAN();
                    lastDistance2Read = true;
                }
                else
                {
                    distance2 = lectureDistanceCAN();
                    lastDistance2Read = false;
                }
                //Lecture du troisieme capteur
                PORTA &= ~(1 << PA2);
                PORTA |= 1 << PA3;
                if (!lastDistance3Read)
                {
                    lastDistance3 = lectureDistanceCAN();
                    lastDistance3Read = true;
                }
                else
                {
                    distance3 = lectureDistanceCAN();
                    lastDistance3Read = false;
                }

                if (distance1 != lastDistance1 && premiereLectureCaseV)
                {
                    affichageTempsEcoule();
                    affichageModeDetection(frequence);
                }
                else if (distance2 != lastDistance2 && premiereLectureCaseV)
                {
                    affichageTempsEcoule();
                    affichageModeDetection(frequence);
                }
                else if (distance3 != lastDistance3 && premiereLectureCaseV)
                {
                    affichageTempsEcoule();
                    affichageModeDetection(frequence);
                }
                premiereLectureCaseV = true;
                break;

            case 'C':
                //Lecture du premier capteur
                PORTA &= ~(1 << PA2) & ~(1 << PA3);
                if (!lastDistance1Read)
                {
                    lastDistance1 = lectureDistanceCAN();
                    lastDistance1Read = true;
                }
                else
                {
                    distance1 = lectureDistanceCAN();
                    lastDistance1Read = false;
                }
                //Lecture du deuxieme capteur
                PORTA &= ~(1 << PA3);
                PORTA |= 1 << PA2;
                if (!lastDistance2Read)
                {
                    lastDistance2 = lectureDistanceCAN();
                    lastDistance2Read = true;
                }
                else
                {
                    distance2 = lectureDistanceCAN();
                    lastDistance2Read = false;
                }
                //Lecture du troisieme capteur
                PORTA &= ~(1 << PA2);
                PORTA |= 1 << PA3;
                if (!lastDistance3Read)
                {
                    lastDistance3 = lectureDistanceCAN();
                    lastDistance3Read = true;
                }
                else
                {
                    distance3 = lectureDistanceCAN();
                    lastDistance3Read = false;
                }

                if (getCategorie(distance1) != getCategorie(lastDistance1) && premiereLectureCaseC)
                {
                    affichageTempsEcoule();
                    affichageModeDetection(frequence);
                }
                else if (getCategorie(distance2) != getCategorie(lastDistance2) && premiereLectureCaseC)
                {
                    affichageTempsEcoule();
                    affichageModeDetection(frequence);
                }
                else if (getCategorie(distance3) != getCategorie(lastDistance3) && premiereLectureCaseC)
                {
                    affichageTempsEcoule();
                    affichageModeDetection(frequence);
                }
                premiereLectureCaseC = true;
                break;

            default:
                break;
            }
            break;

        case ModeManoeuvre:
            activer7Segments();
            //Lecture du premier capteur
            PORTA &= ~(1 << PA2) & ~(1 << PA3);
            distance1 = lectureDistanceCAN();
            //Lecture du deuxieme capteur
            PORTA &= ~(1 << PA3);
            PORTA |= 1 << PA2;
            distance2 = lectureDistanceCAN();
            //Lecture du troisieme capteur
            PORTA &= ~(1 << PA2);
            PORTA |= 1 << PA3;
            distance3 = lectureDistanceCAN();
            manoeuvre = getManoeuvreAFaire(getCategorie(distance1), getCategorie(distance2), getCategorie(distance3));
            if (!transmissionFaite)
            {
                transmettreChainePc2("Manoeuvre ", 11, 1);
                transmissionUSART(manoeuvre);
                transmissionFaite = true;
            }

            switch (manoeuvre)
            {
            case '1':
                vitesse = 35;
                DDRD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD4) | (1 << PD5);
                PORTD &= ~(1 << PD3); // -35% donc on inverse
                PORTD |= (1 << PD6);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                ajustementPWMPourcentage(vitesse, vitesse);
                _delay_ms(1500);

                PORTD |= (1 << PD3);
                _delay_ms(2000);

                PORTD &= ~(1 << PD6);
                _delay_ms(1500);

                PORTD |= (1 << PD6);
                while (vitesse <= 95)
                {
                    _delay_ms(125);
                    ajustementPWMPourcentage(vitesse, vitesse);
                    afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                    vitesse += 5;
                }

                _delay_ms(2000);
                ajustementPWMPourcentage(0, 0);
                PORTD &= ~(1 << PD4) & ~(1 << PD5);
                DDRD &= ~(1 << PD4) & ~(1 << PD5);
                desactiver7Segments();
                transmissionUSART('\n');
                etat = ModeDetection;
                break;

            case '2':
                vitesse = 35;
                DDRD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD3);
                PORTD &= ~(1 << PD6); // -35% donc on inverse
                ajustementPWMPourcentage(vitesse, vitesse);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                _delay_ms(1500);

                PORTD |= (1 << PD6);
                _delay_ms(2000);

                PORTD &= ~(1 << PD3);
                _delay_ms(1500);

                PORTD |= (1 << PD3);
                while (vitesse <= 95)
                {
                    _delay_ms(125);
                    ajustementPWMPourcentage(vitesse, vitesse);
                    afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                    vitesse += 5;
                }

                _delay_ms(2000);
                ajustementPWMPourcentage(0, 0);
                PORTD &= ~(1 << PD4) & ~(1 << PD5);
                DDRD &= ~(1 << PD4) & ~(1 << PD5);
                desactiver7Segments();
                transmissionUSART('\n');
                etat = ModeDetection;
                break;

            case '3':
                vitesse = 50;
                DDRD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD4) | (1 << PD5);
                PORTD &= ~(1 << PD3);
                PORTD &= ~(1 << PD6);
                ajustementPWMPourcentage(vitesse, vitesse);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                _delay_ms(1000);

                vitesse = 70;
                PORTD |= (1 << PD6);
                ajustementPWMPourcentage(vitesse, vitesse);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                _delay_ms(1500);

                vitesse = 0;
                PORTD |= (1 << PD3);
                ajustementPWMPourcentage(vitesse, vitesse);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                while (vitesse <= 99)
                {
                    _delay_ms(50);
                    ajustementPWMPourcentage(vitesse, vitesse);
                    afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                    vitesse += 3;
                }

                vitesse = 99;
                while (vitesse >= 74)
                {
                    _delay_ms(500);
                    ajustementPWMPourcentage(vitesse, vitesse);
                    afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                    vitesse -= 5;
                }
                _delay_ms(2000);

                ajustementPWMPourcentage(0, 0);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                PORTD &= ~(1 << PD4) & ~(1 << PD5);
                DDRD &= ~(1 << PD4) & ~(1 << PD5);
                desactiver7Segments();
                transmissionUSART('\n');
                etat = ModeDetection;
                break;

            case '4':
                vitesse = 78;
                DDRD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD3);
                PORTD |= (1 << PD6);
                ajustementPWMPourcentage(vitesse, vitesse);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);

                while (vitesse >= 48)
                {
                    _delay_ms(250);
                    ajustementPWMPourcentage(78, vitesse);
                    afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(78, moteurDroite, isDecimal);
                    vitesse -= 2;
                }
                _delay_ms(1500);

                vitesse = 48;
                while (vitesse <= 78)
                {
                    _delay_ms(250);
                    ajustementPWMPourcentage(78, vitesse);
                    afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(78, moteurDroite, isDecimal);
                    vitesse += 2;
                }
                _delay_ms(2000);

                ajustementPWMPourcentage(0, 0);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                PORTD &= ~(1 << PD4) & ~(1 << PD5);
                DDRD &= ~(1 << PD4) & ~(1 << PD5);
                desactiver7Segments();
                transmissionUSART('\n');
                etat = ModeDetection;
                break;

            case '5':
                vitesse = 78;
                DDRD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD4) | (1 << PD5);
                PORTD |= (1 << PD3);
                PORTD |= (1 << PD6);
                ajustementPWMPourcentage(vitesse, vitesse);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);

                while (vitesse >= 48)
                {
                    _delay_ms(250);
                    ajustementPWMPourcentage(vitesse, 78);
                    afficher7SegmentsChoix(78, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                    vitesse -= 2;
                }
                _delay_ms(1500);

                vitesse = 48;
                while (vitesse <= 78)
                {
                    _delay_ms(250);
                    ajustementPWMPourcentage(vitesse, 78);
                    afficher7SegmentsChoix(78, moteurGauche, isDecimal);
                    afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                    vitesse += 2;
                }
                _delay_ms(2000);

                ajustementPWMPourcentage(0, 0);
                afficher7SegmentsChoix(vitesse, moteurGauche, isDecimal);
                afficher7SegmentsChoix(vitesse, moteurDroite, isDecimal);
                PORTD &= ~(1 << PD4) & ~(1 << PD5);
                DDRD &= ~(1 << PD4) & ~(1 << PD5);
                desactiver7Segments();
                transmissionUSART('\n');
                etat = ModeDetection;
                break;

            default:
                break;
            }

            break;
        }
    }
    return 0;
}
