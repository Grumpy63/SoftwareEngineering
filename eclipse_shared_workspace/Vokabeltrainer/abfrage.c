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

//srand(time(NULL));										//Initialisieren des Seeds mit der Systemzeit, vor jedem Aufruf von irand verwenden!
		int irand( int a, int e)								//Funktion zum Erzeugen von Zufallszahlen im Intervall a-e
		{
			double r = e - a + 1;
			return a + (int)(r * rand()/(RAND_MAX+1.0));
		}


void abfrage(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc, int modus) //Definition der Abfrage-Fkt
{
		switch (modus)											//Realisierung der verschiedenen Abfragerichtungen
		{
			case 1: break;										//Sprache1 -> Sprache2 in extra Funktionen seperat c files!
			case 2: break;										//Sprache2 -> Sprache1
			case 3: break;										//Gemischt per Zufall
			default: printf("Programminterner Fehler. Bitte starte die Anwendung erneut!");
		}
}
