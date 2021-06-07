/*
 * Main.c
 *
 *  Created on: 02.06.2021
 *      Author: David
 */
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int richtung;

int main(){

	struct kategorie * abzufragende_kategorie = NULL;
	int maximale_vokabelzahl = 0;

	//verzeichnis_auslesen();
	abzufragende_kategorie = kategorie_waehlen(liste_einlesen());
	richtung = richtung_waehlen();
	maximale_vokabelzahl = vokabelzahl_feststellen(abzufragende_kategorie);

	getchar();
	return(0);
}
