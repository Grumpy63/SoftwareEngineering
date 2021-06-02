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
	int korrekte_vokablen = 0;								//counter für Anzahl der Korrekt eingegebenen Vokabeln
	int *korrekte_vokabeln = &korrekte_vokablen;			//Pointer auf counter um in der Funktion die Anzahl hoch zu zählen

	struct username *aktueller_nutzer = NULL;				//Erstelle pointer auf struct username um Rückgabewert der Funktion username_list verwenden zu können

	aktueller_nutzer = username_list();						//Funktion zeigt alle bestehenden Nutzer auf bzw. legt Usernames.txt Datei an, liest aktuellen Nutzernamen ein und returned Pointer auf den aktuellen Nutzer

	printf("Willkommen in der Main %s", aktueller_nutzer->name);
	int a = 0;
	scanf("%d", &a);

	verzeichnis_auslesen();

	return 0;
}
