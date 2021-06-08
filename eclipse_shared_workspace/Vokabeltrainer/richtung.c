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


int richtung_waehlen()
{
	int richtung = 0;
	printf("Bitte wählen Sie den Abfragemodus:\n");
	printf("(1) Sprache1 zu Sprache2\n");
	printf("(2) Sprache2 zu Sprache1\n");
	printf("(3) Zufällige Abfragesprache\n");

	while(1)
	{
		scanf("%d", &richtung);
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
