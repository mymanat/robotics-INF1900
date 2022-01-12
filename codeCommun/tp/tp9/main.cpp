/*
  Nom    : tp9, exec
  Description : programme qui lit les instructions inscrites sur la mémoire eeprom
                et indique ce que chaque instructions doit faire
  équipe : 115165
  Auteurs: Mymanat Mohammed         - 2068301
           Safa Ikhlef              - 2058906
           Ivan Ivanov              - 2087256
           Eliott Schuhmacher-Wantz - 2081542
 */
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include "moteur.h"
#include "memoire.h"
#include "del.h"
#include "instructions.h"

#define DBT 0x01
#define ATT 0x02
#define DAL 0x44
#define DET 0x45
#define MON 0x18
#define MOF 0x19
#define MAR 0x60
#define MAR2 0x61
#define MAV 0x62
#define MRE 0x63
#define TRD 0x64
#define TRG 0x65
#define DBC 0xC0
#define FBC 0xC1
#define FIN 0xFF
#define SORTIE 0xff
#define ENTREE 0x00
#define DELAISAFFICHAGE 250
#define DELAISMOTEUR 30
#define DIRECTIONAVANCER 0x48
#define DIRECTIONRECULER 0x00
#define DIRECTIONDROITE 0x08
#define DIRECTIONGAUCHE 0x40
#define NORD 0x97
#define SUD 0x37
#define EST 0x5b
#define OUEST 0x4c

int main()
{
    DDRA = SORTIE;
    DDRB = SORTIE;
    DDRC = SORTIE;

    //[ Écriture des donnees en EEPROM
    transmissionUSART(0); // transmission vide juste pour que la vitesse de simulation (real speed) ne tombe à 0%
    transmissionUSART(0); // transmission vide juste pour que la vitesse de simulation (real speed) ne tombe à 0%
    uint16_t addr = 0x0000;
    initialisationUART8Bits1StopBitNoneParity();
    uint16_t nInstructions, temp;
    nInstructions = recevoirUSART();
    temp = nInstructions;
    eeprom_write_byte((uint8_t *)addr, nInstructions);
    addr += 0x0001;
    nInstructions = recevoirUSART();
    temp += nInstructions;
    eeprom_write_byte((uint8_t *)addr, nInstructions);
    nInstructions = temp - 2;
    addr += 0x0001;
    for (unsigned int i = 0; i < nInstructions; i++)
    {
        eeprom_write_byte((uint8_t *)addr, recevoirUSART());
        addr += 0x0001;
    }
    addr = 0x0000;
    lireEepromAPc(addr, nInstructions + 3, 1);
    //] Fin de l'écriture des donnees en EEPROM #############

    // Attendre de presser le bouton pour dire au programme de commancer à lire les instructions dans la EEPROM
    DDRD = ENTREE;
    uint8_t boutonPoussoir = 0;
    while (boutonPoussoir == 0)
    {
        if (PIND & 0x04)
        {
            boutonPoussoir = 1;
        }
        continue;
    }
    DDRD = SORTIE;
    //#######################################################

    addr = 0x0000;
    uint16_t addrBoucle = 0x0000;
    uint8_t compteurBoucle = 0x00;
    //Lire la taille du bytecode#############################
    uint8_t nInstructionsLues = eeprom_read_byte((uint8_t *)addr);
    addr += 0x0001;
    nInstructionsLues += eeprom_read_byte((uint8_t *)addr);
    addr += 0x0001;
    //Vérification de début du programme#####################
    bool isStart = false;
    while (isStart == false)
    {
        uint8_t instructionsLues[2];
        instructionsLues[0] = eeprom_read_byte((uint8_t *)addr); // on lit l'instruction
        addr += 0x0001;
        instructionsLues[1] = eeprom_read_byte((uint8_t *)addr); // on lit l'opérande
        addr += 0x0001;
        isStart = estDebutProgramme(instructionsLues[0]);
        if (isStart == true || addr == nInstructions)
        {
            transmissionUSART(instructionsLues[0]);
            PORTB = DBT;
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;
        }
    }
    //Vérification de fin du programme#####################
    bool isEnd = false;
    //Switchcase avec les instructions#######################################################
    for (uint8_t i = addr; i < nInstructions; i++)
    {
        if (isEnd == true)
            break;
        uint8_t instructionsLues[2];
        instructionsLues[0] = eeprom_read_byte((uint8_t *)addr);
        addr += 0x0001;
        instructionsLues[1] = eeprom_read_byte((uint8_t *)addr);
        addr += 0x0001;

        switch (instructionsLues[0])
        {
        case ATT:
            PORTB = ATT;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            attendre25MsFois(instructionsLues[1]);
            // _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case DAL:
            PORTB = DAL;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            allumerDelInstruction(instructionsLues[1], PORTC);
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case DET:
            PORTB = DET;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            eteindreDelInstruction(PORTC);
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case MON:
            PORTB = MON;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            allumerMatriceDelAffichage(instructionsLues[1], PORTA);
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case MOF:
            PORTB = MOF;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            eteindreMatriceDelAffichage(PORTA);
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case MAR:
        case MAR2:
            PORTB = instructionsLues[0];
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            PORTC = 0x00;                                    //On eteint la boussole
            ajustementPWMmateriellePhaseCorrecte8Bits(0, 0); //On eteint les moteurs
            _delay_ms(DELAISAFFICHAGE);                      //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case MAV:
            PORTB = MAV;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            PORTD = DIRECTIONAVANCER;       //On met les deux moteurs en direction avancer (vert)
            PORTC = NORD;                   //On allume la boussole vers le nord
            if (instructionsLues[1] == 255) //À 255 la vitesse est de 0 à la place dans simulIDE
                instructionsLues[1]--;
            ajustementPWMmateriellePhaseCorrecte8Bits(instructionsLues[1], instructionsLues[1]);
            attendre25MsFois(DELAISMOTEUR); //petit delais pour montrer que les roues tournent dans le simulateur
            break;

        case MRE:
            PORTB = MRE;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            PORTD = DIRECTIONRECULER;       //On met les deux moteurs en direction reculer (rouge)
            PORTC = SUD;                    //On allume la boussole vers le sud
            if (instructionsLues[1] == 255) //À 255 la vitesse est de 0 à la place dans simulIDE
                instructionsLues[1]--;
            ajustementPWMmateriellePhaseCorrecte8Bits(instructionsLues[1], instructionsLues[1]);
            attendre25MsFois(DELAISMOTEUR); //petit delais pour montrer que les roues tournent dans le simulateur
            break;

        case TRD:
            PORTB = TRD;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            PORTD = DIRECTIONDROITE; //On met le premier moteur en direction avancer (vert) et le deuxième en direction reculer (rouge)
            PORTC = EST;             //On allume la boussole vers l'est
            ajustementPWMmateriellePhaseCorrecte8Bits(128, 128);
            attendre25MsFois(DELAISMOTEUR); //petit delais pour montrer que les roues tournent dans le simulateur
            break;

        case TRG:
            PORTB = TRG;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            PORTD = DIRECTIONGAUCHE; //On met le premier moteur en direction reculer (rouge) et le deuxième en direction avancer (vert)
            PORTC = OUEST;           //On allume la boussole vers l'ouest
            ajustementPWMmateriellePhaseCorrecte8Bits(128, 128);
            attendre25MsFois(DELAISMOTEUR); //petit delais pour montrer que les roues tournent dans le simulateur
            break;

        case DBC:
            PORTB = DBC;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            addrBoucle = addr;
            compteurBoucle = instructionsLues[1];
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case FBC:
            PORTB = FBC;
            transmissionUSART(instructionsLues[0]);
            transmissionUSART(instructionsLues[1]);
            if (compteurBoucle > 0)
            {
                addr = addrBoucle;
            }
            compteurBoucle--;
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            break;

        case FIN:
            PORTB = FIN;
            transmissionUSART(instructionsLues[0]);
            _delay_ms(DELAISAFFICHAGE); //Petit délais pour donner le temps à l'affichage d'apparaître
            isEnd = true;
            break;

        default:
            break;
        }
    }
    PORTB = 0x00;
    return 0;
}