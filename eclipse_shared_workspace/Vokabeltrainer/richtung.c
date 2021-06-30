/*
 * richtung.c
 *
 *  Created on: 07.06.2021
 *      Author: David
 */


#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "voc_functions.h"

/*In der Funktion wird der Abfragemodi durch den Nutzer ausgewählt.
 * Unterscheidung ob von
 * Sprache1 zu Sprache2
 * Sprache2 zu Sprache1 oder
 * jedes Vokabelpaar zufällig abgefragt wird */

int richtung_waehlen(struct vokabel * sprache)
{
	int richtung = 0;																															//Variable richtung auf 0 gesetzt
	char dummy_zeichen;																															//Variable dummy_zeichen
	mark1:																																		//Sprungmarke mark1
	printf("Folgende Abfragemodi stehen zur Verfügung:\n\n");																					//Ausgabe einer Informationsnachricht für den Nutzer
	printf("(1) %s zu %s\n",sprache->vokabel_sprache1,sprache->vokabel_sprache2);																//Ausgabe einer Informationsnachricht für den Nutzer
	printf("(2) %s zu %s\n",sprache->vokabel_sprache2,sprache->vokabel_sprache1);																//Ausgabe einer Informationsnachricht für den Nutzer
	printf("(3) Zufällige Abfragesprache\n");																									//Ausgabe einer Informationsnachricht für den Nutzer
	printf("\nBitte wählen Sie den Abfragemodus aus, \nindem Sie die entsprechende Nummer eingeben und mit der Enter-Taste bestätigen:");		//Ausgabe einer Informationsnachricht für den Nutzer

		scanf("%d", &richtung);																													//Einlesen der Nutzergabe
		fflush(stdin);																															//Leeren des Puffers
		if(richtung < 1 || richtung > 3 || isalpha(richtung) !=0)																				//If-Verzweigung, wenn Variable richtung kleiner 1, größer 3 oder ein char ist
		{
			printf("\nUngültige Eingabe. Wählen Sie bitte eine Richtung mit einer Eingabe einer Zahl zwischen 1 und 3.\n");						//Ausgabe einer Informationsnachricht für den Nutzer
						while ((dummy_zeichen = getchar()) != '\n' && dummy_zeichen != EOF) {}													//Leeren des Puffers
						goto mark1;																												//Zur Sprungmarke mark1 gehen
		}
		switch (richtung) {																														//Switch-Anweisung der Variablen richtung
			case 1:																																//Fall, dass Variable richtung gleich 1 ist
				printf("\nDu hast dich für den Abfragemodus \"%s zu %s\" entschieden.\n",sprache->vokabel_sprache1,sprache->vokabel_sprache2);	//Ausgabe einer Informationsnachricht für den Nutzer
				break;																															//Abbruch der Switch-Anweisung
			case 2:																																//Fall, dass Variable richtung gleich 2 ist
				printf("\nDu hast dich für den Abfragemodus \"%s zu %s\" entschieden.\n",sprache->vokabel_sprache2,sprache->vokabel_sprache1);	//Ausgabe einer Informationsnachricht für den Nutzer
				break;																															//Abbruch der Switch-Anweisung
			case 3:																																//Fall, dass Variable richtung gleich 3 ist
				printf("\nDu hast dich für den zufaelligen Abfragemodus entschieden.\n");														//Ausgabe einer Informationsnachricht für den Nutzer
				break;																															//Abbruch der Switch-Anweisung
			default:																															//Anweisung für den Fall, dass Variable richtung keiner der Fälle ist
				break;																															//Abbruch der Switch-Anweisung
		}
			return(richtung);																													//Rückgabe der Variablen richtung
}
