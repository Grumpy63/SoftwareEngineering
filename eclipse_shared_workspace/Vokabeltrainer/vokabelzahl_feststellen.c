/*
 * Main.c
 *
 *  Created on: 06.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "voc_functions.h"


int vokabelzahl_feststellen(struct kategorie *abzufragende_kategorie){
	int x = 0;
	int anzahl = 0;
	char dummy_zeichen;

	setbuf(stdout, NULL);
	printf("\nDie abzufragende Kategorie \"%s\" enhält %d Vokabeln.\n\n",abzufragende_kategorie->kategorie_name,abzufragende_kategorie->anzahl_in_kategorie);
	printf("Möchten Sie über:\n");
	printf("(1) alle Vokabeln abgefragt werden oder\n");
	printf("(2) nur über eine bestimmte Anzahl abgefragt werden?\n");
	printf("Zur Auswahl bitte die entsprechende Nummer eingeben und mit der Enter-Taste bestätigen:");
	mark2:
		scanf("%d", &x);
		if(x == 1)
		{
			return(abzufragende_kategorie->anzahl_in_kategorie);
		}
		else if(x == 2)
		{
			mark1:
				printf("\nWie viele Vokabeln möchten Sie abgefragt werden?:");
				scanf("%d", &anzahl);
				if(anzahl <= 0 || anzahl > abzufragende_kategorie->anzahl_in_kategorie || isalpha(anzahl) !=0)
				{
					printf("\nUngültige Eingabe. Wählen Sie bitte eine Anzahl mit der Eingabe einer Zahl zwischen 1 und %d.\n",abzufragende_kategorie->anzahl_in_kategorie);
					scanf("%c", &dummy_zeichen);
					goto mark1;
				}
				else
				{
					printf("\nIm Folgenden werden/ wird %d Vokabeln abgefragt.\n", anzahl);
					return(anzahl);
				}
			}
		else if(isalpha(x) !=1){
			printf("\nUngültige Eingabe. Wählen Sie bitte Ihre Auswahl mit der Eingabe der Zahl 1 oder 2.\n");
			scanf("%c", &dummy_zeichen);
			goto mark2;
		}
		return(anzahl);
}
