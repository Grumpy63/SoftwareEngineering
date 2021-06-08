/*
 * abfrage.c
 *
 *  Created on: 08.06.2021
 *      Author: Alexander Hein
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"								//Einbinden der Header-Dateien

void abfrage(pointer, int number_abzufragende_voc, int number_voc_in_kategorie, int modus) //Definition der Abfrage-Fkt
{

	for(int i=0; i<number_abzufragende_voc; i++)
	{

		srand(time(NULL));										//Initialisieren des Seeds mit der Systemzeit
		int irand( int a, int e)								//Erzeugen einer Zufallszahl vom Datentyp int im Intervall a-e
		{
			double r = e - a + 1;
			return a + (int)(r * rand()/(RAND_MAX+1.0));
		}

		switch (modus)											//Realisierung der verschiedenen Abfragerichtungen
		{
		case 1: break;
		case 2: break;
		case 3: break;
		default: printf("Programminterner Fehler. Bitte starte die Anwendung erneut!");
		}
	}
}
