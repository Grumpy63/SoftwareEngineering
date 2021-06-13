/*
 * richtung.c
 *
 *  Created on: 07.06.2021
 *      Author: David
 */


#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "voc_functions.h"


int richtung_waehlen(struct vokabel * sprache)
{
	int richtung = 0;
	printf("Bitte wählen Sie den Abfragemodus:\n");
	printf("(1) %s zu %s\n",sprache->vokabel_sprache1,sprache->vokabel_sprache2);
	printf("(2) %s zu %s\n",sprache->vokabel_sprache2,sprache->vokabel_sprache1);
	printf("(3) Zufällige Abfragesprache\n");

	while(1)
	{
		scanf("%d", &richtung);
		fflush(stdin);
		if(richtung < 1 || richtung > 3)
		{
			printf("Die Eingabe ist ungültig bitte geben Sie Ihre Auswahl erneut ein.\n");
		}
		else
		{
			return(richtung);
		}
	}
}
