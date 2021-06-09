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

	abzufragende_kategorie = kategorie_waehlen(liste_einlesen());
	richtung = richtung_waehlen();
	maximale_vokabelzahl = vokabelzahl_feststellen(abzufragende_kategorie);

	// OUTPUT TEST
	/*struct kategorie * help_kat = abzufragende_kategorie;
	struct vokabel * help_vok = abzufragende_kategorie->erste_vokabel;
	int i = 1;
	int j = 1;
	while(help_kat != NULL){
		help_vok = help_kat->erste_vokabel;
		printf("Kat %d: %s\n",j,help_kat->kategorie_name);
		i = 1;
		while(help_vok != NULL){
			printf("Vokpaar %d: %s -> %s\n",i,help_vok->vokabel_sprache1,help_vok->vokabel_sprache2);
			help_vok = help_vok->next_vokabel;
			i++;
		}
		help_kat = help_kat->next_kategorie;
		j++;
	}*/

	getchar();
	return(0);
}
