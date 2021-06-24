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

	struct vokabel * sprache = NULL;
	sprache = malloc(sizeof(struct vokabel));

	char dummy_zeichen;
	int modus = 0;											//Richtungsmodus 0 f�r Sprache1->Sprache2; 1 S2->S1; 2 f�r Zufall
	struct kategorie * abzufragende_kategorie = NULL;		//Pointer auf abzufragende Kategorie
	int user_vokabelzahl = 0;								//User gew�hlte Abzufragende Vokabelzahl
	struct username *aktueller_nutzer = NULL;				//Erstelle pointer auf struct username um R�ckgabewert der Funktion username_list verwenden zu k�nnen

	int korrekte_voc = 0;


	printf("äöü?ß=}");
	printf("_______________________________________________________________________________________________________________________________\n\n");
	printf("Willkommen zum Vokabeltrainer!\n\nVorab ein paar kurze Infos:\n"
			"-Nach der Auswahl der abzufragenden Vokabeldatei, dem Abfragemodus und der Anzahl der Vokabeln erfolgt die eigentliche Abfrage\n" //Begr��ung mit Ablauf des Programms
			"-Sie bekommen ein Feedback zum Festhalten Ihres Lernerfolgs\n"
			"-Sie können Ihr Können beweisen, indem Sie es in die Top 3 der besten Vokabelpauker schaffen!\n"
			"-Mit ENTER kommen Sie ins Hauptmenue\n"
			"Und jetzt viel Spass!\n");
	printf("_______________________________________________________________________________________________________________________________\n\n");


	scanf("%c", &dummy_zeichen);							//warten auf enter-befehl des Users

	aktueller_nutzer = username_list();						//Funktion zeigt alle bestehenden Nutzer auf bzw. legt Usernames.txt Datei an, liest aktuellen Nutzernamen ein und returned Pointer auf den aktuellen Nutzer


	printf("_______________________________________________________________________________________________________________________________\n\n");
	printf("Willkommen beim Vokabeltrainer, %s!\n", aktueller_nutzer->name);
	printf("_______________________________________________________________________________________________________________________________\n\n");


	abzufragende_kategorie = kategorie_waehlen(liste_einlesen(sprache));


	modus = richtung_waehlen(sprache);
	user_vokabelzahl = vokabelzahl_feststellen(abzufragende_kategorie);

	//printf("Kritische Vokabel: %s\n", abzufragende_kategorie->erste_vokabel->next_vokabel->vokabel_sprache1);

	//printf("\nIhre Auswahl lautet:\nModus: %d; Abzufragende Vokablen: %d; Kategorie: %s", modus, user_vokabelzahl, abzufragende_kategorie->kategorie_name);


	korrekte_voc = abfrage(abzufragende_kategorie, user_vokabelzahl, modus);

	scanf("%c", &dummy_zeichen);									//warten auf enter-befehl des Users

	user_ergebnis(korrekte_voc, user_vokabelzahl);

	highscore_list(aktueller_nutzer, korrekte_voc, user_vokabelzahl);

	scanf("%c", &dummy_zeichen);									//warten auf enter-befehl des Users

	printf("\nSchön, dass Sie sich Zeit zum Lernen genommen haben.\n");
	printf("Bis bald!\n");
	printf("Das Programm lässt sich durch Betätigung der Enter-Taste schließen...");

	scanf("%c", &dummy_zeichen);									//warten auf enter-befehl des Users


	return 0;
}
