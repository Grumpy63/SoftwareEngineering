/*
 * richtung.c
 *
 *  Created on: 07.06.2021
 *      Author: David
 */


#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "voc_functions.h"


int richtung_waehlen(struct vokabel * sprache)
{
	int richtung = 0;
	char dummy_zeichen;
	mark1:
	printf("Folgende Abfragemodi stehen zur Verfügung:\n\n");
	printf("(1) %s zu %s\n",sprache->vokabel_sprache1,sprache->vokabel_sprache2);
	printf("(2) %s zu %s\n",sprache->vokabel_sprache2,sprache->vokabel_sprache1);
	printf("(3) Zufällige Abfragesprache\n");
	printf("\nBitte wählen Sie den Abfragemodus aus, \nindem Sie die entsprechende Nummer eingeben und mit der Enter-Taste bestätigen:");

		scanf("%d", &richtung);
		fflush(stdin);
		if(richtung < 1 || richtung > 3 || isalpha(richtung) !=0)
		{
			printf("\nUngültige Eingabe. Wählen Sie bitte eine Richtung mit einer Eingabe einer Zahl zwischen 1 und 3.\n");
						while ((dummy_zeichen = getchar()) != '\n' && dummy_zeichen != EOF) {}
						goto mark1;
		}
		switch (richtung) {
			case 1:
				printf("\nDu hast dich für den Abfragemodus \"%s zu %s\" entschieden.\n",sprache->vokabel_sprache1,sprache->vokabel_sprache2);
				break;
			case 2:
				printf("\nDu hast dich für den Abfragemodus \"%s zu %s\" entschieden.\n",sprache->vokabel_sprache2,sprache->vokabel_sprache1);
				break;
			case 3:
				printf("\nDu hast dich für den zufaelligen Abfragemodus entschieden.\n");
				break;
			default:
				break;
		}
			return(richtung);
}
