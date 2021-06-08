/*
 * abfrage1.c
 *
 *  Created on: 08.06.2021
 *      Author: Alexander Hein
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"								//Einbinden der Header-Dateien


int abfrage1(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{
	int anzahl_korrekter_voc = 0;
struct kategorie* help_ptr = NULL;
int zufall = 0;

	for (int i=0; i<number_abzufragende_voc; i++)
	{
		//Zufallszahl erstellen
		srand(time(NULL));
		zufall = irand(0,abzufragende_kategorie->anzahl_in_kategorie);

		for(int x=0; x<number_abzufragende_voc;x++) //pointer
		{

		}
		printf("Bitte geben sie die Übersetzung von %s ein:",abzufragende_kategorie->erste_vokabel->vokabel_sprache1);
		scanf
		//strcmp(...,...)
	}
return(0);
}
