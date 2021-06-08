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
	int modus = 0;											//Richtungsmodus 0 für Sprache1->Sprache2; 1 S2->S1; 2 für Zufall
	int korrekte_vokablen = 0;								//counter für Anzahl der Korrekt eingegebenen Vokabeln
	struct kategorie * abzufragende_kategorie = NULL;		//Pointer auf abzufragende Kategorie
	int user_vokabelzahl = 0;							//User gewählte Abzufragende Vokabelzahl
	struct username *aktueller_nutzer = NULL;				//Erstelle pointer auf struct username um Rückgabewert der Funktion username_list verwenden zu können


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

	return 0;
}
