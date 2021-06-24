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
	printf("\nBitte waehlen Sie den Abfragemodus aus, indem Sie die entsprechende Nummer eingeben und mit der Enter-Taste bestaetigen:\n");
	printf("(1) %s zu %s\n",sprache->vokabel_sprache1,sprache->vokabel_sprache2);
	printf("(2) %s zu %s\n",sprache->vokabel_sprache2,sprache->vokabel_sprache1);
	printf("(3) Zufaellige Abfragesprache\n");


		scanf("%d", &richtung);
		fflush(stdin);
		if(richtung < 1 || richtung > 3 || isalpha(richtung) !=0)
		{
			printf("Ungueltige Eingabe. Waehlen Sie bitte eine Richtung mit einer Eingabe einer Zahl zwischen 1 und 3.\n");
						scanf("%c", &dummy_zeichen);
						goto mark1;
		}
		switch (richtung) {
			case 1:
				printf("Du hast dich fuer den Abfragemodus \"%s zu %s\" entschieden.",sprache->vokabel_sprache1,sprache->vokabel_sprache2);
				break;
			case 2:
				printf("Du hast dich fuer den Abfragemodus \"%s zu %s\" entschieden.",sprache->vokabel_sprache2,sprache->vokabel_sprache1);
				break;
			case 3:
				printf("Du hast dich fuer den zufaelligen Abfragemodus entschieden.");
				break;
			default:
				break;
		}
			return(richtung);
}
