/*
 * Main.c
 *
 *  Created on: 02.06.2021
 *      Author: David
 */
#include <stdio.h>
#include "header.h"
#include <windows.h>


int richtung;

int main(){

	SetConsoleOutputCP (1252);
	SetConsoleCP (1252);
	struct kategorie * abzufragende_kategorie = NULL;
	int maximale_vokabelzahl = 0;

	//verzeichnis_auslesen();
	abzufragende_kategorie = kategorie_waehlen(liste_einlesen());
	richtung = richtung_waehlen();
	maximale_vokabelzahl = vokabelzahl_feststellen(abzufragende_kategorie);

	getchar();
	return(0);
}
