/*
 * main.c
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */

#include <stdio.h>
#include <stdlib.h>
#include "voc_functions.h"



int main()
{


	int modus = 0;											//Richtungsmodus 0 f�r Sprache1->Sprache2; 1 S2->S1; 2 f�r Zufall
	int korrekte_vokablen = 0;								//counter f�r Anzahl der Korrekt eingegebenen Vokabeln
	struct kategorie * abzufragende_kategorie = NULL;		//Pointer auf abzufragende Kategorie
	int user_vokabelzahl = 0;							//User gew�hlte Abzufragende Vokabelzahl
	struct username *aktueller_nutzer = NULL;				//Erstelle pointer auf struct username um R�ckgabewert der Funktion username_list verwenden zu k�nnen

	int test = 0;


	printf("Willkommen zum Vokabeltrainer!\n\nVorab ein paar kurze Infos:\n"
			"-Nach der Auswahl der abzufragenden Vokabeldatei, Abfragemodus und Anzahl der Vokabeln erfolgt die eigentliche Abfrage\n" //Begr��ung mit Ablauf des Programms
			"-Du bekommst ein Feedback zum Festhalten deines Lernerfolgs\n"
			"-Du kannst dein Koennen beweisen, indem du es in die Top3 der besten Vokabelpauker schaffst!\n"
			"Und jetzt viel Spass!\n\n");


	aktueller_nutzer = username_list();						//Funktion zeigt alle bestehenden Nutzer auf bzw. legt Usernames.txt Datei an, liest aktuellen Nutzernamen ein und returned Pointer auf den aktuellen Nutzer


	printf("Willkommen in der Main %s\n", aktueller_nutzer->name);


	//verzeichnis_auslesen();
	abzufragende_kategorie = kategorie_waehlen(liste_einlesen());
	modus = richtung_waehlen();
	user_vokabelzahl = vokabelzahl_feststellen(abzufragende_kategorie);

	printf("Ihre Auswahl lautet:\nModus: %d; Abzufragende Vokablen: %d", modus, user_vokabelzahl);

	getchar();
	int a = 0;
	scanf("%d", &a);


	test = abfrage("hier kommt ein Pointer auf Kategorie rein", 2, 3);


	return 0;
}