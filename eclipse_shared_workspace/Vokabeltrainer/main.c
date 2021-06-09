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
	struct kategorie * abzufragende_kategorie = NULL;		//Pointer auf abzufragende Kategorie
	int user_vokabelzahl = 0;								//User gewählte Abzufragende Vokabelzahl
	struct username *aktueller_nutzer = NULL;				//Erstelle pointer auf struct username um Rückgabewert der Funktion username_list verwenden zu können

	int korrekte_voc = 0;


	printf("Willkommen zum Vokabeltrainer!\n\nVorab ein paar kurze Infos:\n"
			"-Nach der Auswahl der abzufragenden Vokabeldatei, Abfragemodus und Anzahl der Vokabeln erfolgt die eigentliche Abfrage\n" //Begrüßung mit Ablauf des Programms
			"-Du bekommst ein Feedback zum Festhalten deines Lernerfolgs\n"
			"-Du kannst dein Koennen beweisen, indem du es in die Top3 der besten Vokabelpauker schaffst!\n"
			"Und jetzt viel Spass!\n\n");



	aktueller_nutzer = username_list();						//Funktion zeigt alle bestehenden Nutzer auf bzw. legt Usernames.txt Datei an, liest aktuellen Nutzernamen ein und returned Pointer auf den aktuellen Nutzer

	printf("Willkommen in der Main %s\n", aktueller_nutzer->name);


	abzufragende_kategorie = kategorie_waehlen(liste_einlesen());
	modus = richtung_waehlen();
	user_vokabelzahl = vokabelzahl_feststellen(abzufragende_kategorie);

	//printf("Kritische Vokabel: %s\n", abzufragende_kategorie->erste_vokabel->next_vokabel->vokabel_sprache1);

	printf("Ihre Auswahl lautet:\nModus: %d; Abzufragende Vokablen: %d; Kategorie: %s", modus, user_vokabelzahl, abzufragende_kategorie->kategorie_name);


	korrekte_voc = abfrage(abzufragende_kategorie, user_vokabelzahl, modus);


	user_ergebnis(korrekte_voc, user_vokabelzahl);



	int b = 0;
	scanf("%d", &b);


	return 0;
}
