/*
 * Main.c
 *
 *  Created on: 06.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include "voc_functions.h"


int vokabelzahl_feststellen(struct kategorie *abzufragende_kategorie){
	int x = 0;
	int anzahl = 0;

	setbuf(stdout, NULL);
	printf("\nDie abzufragende Kategorie \"%s\" enhaelt %d Vokabeln.\n\n",abzufragende_kategorie->kategorie_name,abzufragende_kategorie->anzahl_in_kategorie);
	printf("Moechten Sie ueber:\n");
	printf("(1) alle Vokabeln abgefragt werden oder\n");
	printf("(2) nur ueber eine bestimmte Anzahl abgefragt werden?\n");
	while(1)
	{
		scanf("%d", &x);
		if(x == 1)
		{
			return(abzufragende_kategorie->anzahl_in_kategorie);
		}
		else if(x == 2)
		{
			while(1)
			{
				printf("Wie viele Vokabeln moechten Sie abgefragt werden?:\n");
				scanf("%d", &anzahl);
				if(anzahl <= 0 || anzahl > abzufragende_kategorie->anzahl_in_kategorie)
				{
					printf("Die Eingabe ist ungueltig.\n");

				}
				else
				{
					return(anzahl);
				}
			}

		}
		else{
			printf("Die Eingabe ist ungueltig bitte geben Sie Ihre Auswahl erneut ein.\n");

		}

	}







	return anzahl;
}
