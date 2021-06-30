/*
 * abfrage.c
 *
 *  Created on: 08.06.2021
 *      Author: Alexander Hein
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"

/*In dieser Funktion wird die jeweilige Abfragefunktion aufgerufen, die der Nutzer gewählt hat*/


		int irand( int a, int e)																		//Funktion zum Erzeugen von Zufallszahlen im Intervall a-e, wird in abfrage1-3 benötigt
		{
			double r = e - a + 1;
			return a + (int)(r * rand()/(RAND_MAX+1.0));
		}

// Funktion prüft den Eingegebenen Modus und verzweigt anschließend in jeweilige Unterfunktion (in den einzelnen c-Files)


int abfrage(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc, int modus) 			//Definition der Abfrage-Fkt
{

	int anzahl_korrekter_voc = 0;

		switch (modus)																					//Realisierung der verschiedenen Abfragerichtungen in seperaten c-files (abfrage1.c , abfrage2new.c, abfrage3.c)
		{
			case 1: anzahl_korrekter_voc = abfrage1(abzufragende_kategorie,number_abzufragende_voc);  	//Sprache1 -> Sprache2 in extra Funktionen seperat c files!
			break;																						//Abbruch der Switch-Anweisung
			case 2: anzahl_korrekter_voc = abfrage2(abzufragende_kategorie,number_abzufragende_voc);	//Sprache2 -> Sprache1
			break;																						//Abbruch der Switch-Anweisung
			case 3: anzahl_korrekter_voc = abfrage3(abzufragende_kategorie,number_abzufragende_voc);	//Gemischt per Zufall
			break;																						//Abbruch der Switch-Anweisung
			default: printf("Programminterner Fehler. Bitte starte die Anwendung erneut!");				//Ausgabe einer Hinweisnachricht an den Nutzer
		}

		return(anzahl_korrekter_voc);																	//Rückgabe der Richtigen an main-fkt für Highscore liste
}
