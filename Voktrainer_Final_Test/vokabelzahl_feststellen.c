/*
 * Main.c
 *
 *  Created on: 06.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int vokabelzahl_feststellen(struct kategorie *abzufragende_kategorie){
	int x = 0;
	int anzahl = 0;

	setbuf(stdout, NULL);
	printf("\nDie abzufragende Kategorie \"%s\" enhält %d Vokabeln.\n\n",abzufragende_kategorie->kategorie_name,abzufragende_kategorie->anzahl_in_kategorie);
	printf("Möchten Sie über:\n");
	printf("(1) alle Vokabeln abgefragt werden oder\n");
	printf("(2) nur über eine bestimmte Anzahl abgefragt werden?\n");
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
				printf("Wie viele Vokabeln möchten Sie abgefragt werden?:\n");
				scanf("%d", &anzahl);
				if(anzahl <= 0 || anzahl > abzufragende_kategorie->anzahl_in_kategorie)
				{
					printf("Die Eingabe ist ungültig.\n");

				}
				else
				{
					return(anzahl);
				}
			}

		}
		else{
			printf("Die Eingabe ist ungültig bitte geben Sie Ihre Auswahl erneut ein.\n");

		}

	}


	return anzahl;
}
