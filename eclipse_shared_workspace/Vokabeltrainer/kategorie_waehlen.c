/*
 * kategorie_waehlen.c
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

/*In der Funktion wird durch den Nutzer festgelegt ob er über alle Vokabeln oder nur eine bestimmte Kategorie abgefragt wird, sofern es Kategorien gibt.
 * Sind keine Kategorien vorhanden wird der Nutzer automatisch über alle Vokabeln abgefragt und diese Auswahl wird vom Programm selbst getroffen*/

struct kategorie *kategorie_waehlen(struct kategorie *k_alle_erste_ptr)
{
	printf("_______________________________________________________________________________________________________________________________\n\n");

	struct kategorie *rueckgabe_help_ptr = NULL;																								//pointer der struct kategorie auf NULL gesetzt
	int i_max = 1;																																//Variable i_max auf 1 gesetzt
	int i = 1;																																	//Variable i auf 1 gesetzt
	int a = 1;																																	//Variable a auf 1 gesetzt
	char dummy_zeichen;																															//dummy_zeichen

	setbuf(stdout, NULL);																														//Outpput Buffer auf NULL gesetzt
	if(k_alle_erste_ptr->next_kategorie == NULL)																								//If-Verzweigung, wenn der pointer k_alle_erste_ptr->next_kategorie auf NULL zeigt
	{
		printf("Kategorie %s wird abgefragt, da es keine anderen Kategorien in der Vokabelliste gibt.\n\n", k_alle_erste_ptr->kategorie_name);	//Ausgabe einer Informationsnachricht für den Nutzer
		return(k_alle_erste_ptr);																												//Rückgabe des pointers k_alle_erste_ptr aus der Funktion
	}
	else if(k_alle_erste_ptr->next_kategorie->next_kategorie == NULL)																			//Else If-Verweigung, wenn der pointer
	{
		printf("Kategorie %s wird abgefragt.\n\n", k_alle_erste_ptr->next_kategorie->kategorie_name);											//Ausgabe einer Informationsnachricht für den Nutzer
		return(k_alle_erste_ptr->next_kategorie);																								//Rückgabe des pointers k_alle_erste_ptr->next_kategorie aus der Funktion
	}

	printf("\nFolgende Kategorien können gewählt werden: \n\n");																				//Ausgabe einer Informationsnachricht für den Nutzer

	rueckgabe_help_ptr = k_alle_erste_ptr;																										//Pointer rueckgabe_help_ptr auf pointer k_alle_erste_ptr gesetzt

	while(rueckgabe_help_ptr != NULL)																											//While-Schleife solange der Pointer rueckgabe_help_ptr nicht NULL ist
	{
		printf("(%d) %s\n", i, rueckgabe_help_ptr->kategorie_name);																				//Ausgabe einer Informationsnachricht für den Nutzer
		i++;																																	//Variable i um eins inkrementieren
		rueckgabe_help_ptr = rueckgabe_help_ptr->next_kategorie;																				//Pointer rueckgabe_help_ptr auf rueckgabe_help_ptr->next_kategorie gesetzt
	}

	i_max = i-1;																																//Variable i_max auf i-1 gesetzt


	while(1){																																	//While-Schleife
		printf("\nBitte wählen Sie die Kategorie aus, welche abgefragt werden soll, \nindem Sie die entsprechende Nummer eingeben und mit der Enter-Taste bestätigen:");//Ausgabe einer Informationsnachricht für den Nutzer
		scanf("%d", &i);																														//Einlesen der Nutzereingabe zur Auswahl der Liste
		if(i<1 || i>i_max){																														//If-Verzweigung, wenn i kleiner 1 ist oder i größer als der Wert der Variablen i_max ist
			printf("\nUngültige Eingabe. Wählen Sie bitte eine Kategorie mit einer Eingabe einer Zahl zwischen 1 und %d.\n",i_max);				//Ausgabe einer Informationsnachricht für den Nutzer
			while ((dummy_zeichen = getchar()) != '\n' && dummy_zeichen != EOF) {}																//While-Schleife zum Buffer leeren
			continue;																															//erneuter Durchlauf der Schleife
		}
		break;																																	//Abbruch der While-Schleife
	}//Ende Schleife für User Eingabe der Kategoriezahl




	rueckgabe_help_ptr = k_alle_erste_ptr;																										//Pointer rueckgabe_help_ptr auf Pointer k_alle_erste_ptr gesetzt


	while(a != i)																																//While-Schleife solange Variable a ungleich der Variablen i ist
	{
		rueckgabe_help_ptr = rueckgabe_help_ptr->next_kategorie;																				//Pointer rueckgabe_help_ptr auf Pointer rueckgabe_help_ptr->next_kategorie gesetzt
		a++;																																	//Variable a um 1 inkrementiert
	}
	printf("\nEs wurde die Kategorie \"%s\" ausgewählt.\n", rueckgabe_help_ptr->kategorie_name);												//Ausgabe einer Informationsnachricht für den Nutzer


	return(rueckgabe_help_ptr);																													//Rückgabe des Pointers rueckgabe_help_ptr aus der Funktion
}
