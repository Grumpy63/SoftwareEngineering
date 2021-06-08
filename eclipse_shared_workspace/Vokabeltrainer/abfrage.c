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


int abfrage(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc, int modus) //Definition der Abfrage-Fkt
{
	int anzahl_korrekter_voc = 0;

		switch (modus)											//Realisierung der verschiedenen Abfragerichtungen
		{
			case 1:anzahl_korrekter_voc = abfrage1(abzufragende_kategorie,number_abzufragende_voc);  //Sprache1 -> Sprache2 in extra Funktionen seperat c files!
			break;
			case 2: //Sprache2 -> Sprache1
			break;
			case 3: //Gemischt per Zufall
			break;
			default: printf("Programminterner Fehler. Bitte starte die Anwendung erneut!");
		}

		return(anzahl_korrekter_voc);
}
