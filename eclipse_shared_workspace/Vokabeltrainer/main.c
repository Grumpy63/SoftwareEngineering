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

	int test = 0;

	struct username *aktueller_nutzer = NULL;				//Erstelle pointer auf struct username um Rückgabewert der Funktion username_list verwenden zu können

	printf("Willkommen zum Vokabeltrainer!\n\nVorab ein paar kurze Infos:\n"
			"-Nach der Auswahl der abzufragenden Vokabeldatei, Abfragemodus und Anzahl der Vokabeln erfolgt die eigentliche Abfrage\n" //Begrüßung mit Ablauf des Programms
			"-Du bekommst ein Feedback zum Festhalten deines Lernerfolgs\n"
			"-Du kannst dein Koennen beweisen, indem du es in die Top3 der besten Vokabelpauker schaffst!\n"
			"Und jetzt viel Spass!\n\n");

	aktueller_nutzer = username_list();						//Funktion zeigt alle bestehenden Nutzer auf bzw. legt Usernames.txt Datei an, liest aktuellen Nutzernamen ein und returned Pointer auf den aktuellen Nutzer

	printf("Willkommen in der Main %s", aktueller_nutzer->name);
	int a = 0;
	scanf("%d", &a);

	test = abfrage("hier kommt ein Pointer auf Kategorie rein", 2, 3);

	return 0;
}
