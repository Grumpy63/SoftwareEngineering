/*
 * abfrage3.c
 *
 *  Created on: 08.06.2021
 *      Author: Luca
 */

#include<stdio.h>
#include<stdlib.h>
#include"voc_functions.h"
#include <string.h>


int abfrage3(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{
	int anzahl_korrekter_voc = 0;
	struct vokabel* cursor_ptr = NULL; 										//Hilfsptr auf aktuelle Vokabel
	struct vokabel* help_ptr = NULL;
	int zufall_voc = 0;														//Randomzahl für Vokabelabfragenreihenfolge
	int zufall_sprache = 0;													//Zufalls Zahl für die zufällige Sprachreihenfolge
	char dummy_zeichen = ' ';												//Dummy zum Leerzeichen einlesen
	char eingabe[256];														//Platzhalter für User Vokabeleingabe


	scanf("%c", &dummy_zeichen);											//Leeren des Puffers
				if(dummy_zeichen == '\r')									//auch auf anderen OS (haben evtl mehr Zeichen)
						{
							scanf("%c", &dummy_zeichen);
						}


		for (int i=0; i < number_abzufragende_voc; i++)						//Schleife für die Abfragezyklen, i ist Laufvariable
		{


				srand(time(NULL));											//Generieren einer Zufallszahl von int in Bereich 0 bis Anzahl in Kategorie minus 1
				zufall_voc = irand(0, abzufragende_kategorie->anzahl_in_kategorie-1);

				cursor_ptr = abzufragende_kategorie->erste_vokabel;			//Hilfszeiger auf Beginn der abzufragenden Vokabelliste
				help_ptr = abzufragende_kategorie->erste_vokabel;

				for(int x = 0; x < zufall_voc; x++) 							//Zeiger jeweils Vielfaches der Zufallszahl Weitersetzen auf die nächsten Listenelemente
				{
					cursor_ptr = cursor_ptr->next_vokabel;
				}

				if(zufall_voc>1)
					 {
						 for(int i=0; i<zufall_voc-1;i++)
						 {
							 help_ptr = help_ptr->next_vokabel;
						 }
					 }



				//Nun die zufällige Sprachreihenfolge

				srand(time(NULL));											//Generieren einer von zwei Zufallszahl
				zufall_sprache = irand(0, 1);

				switch(zufall_sprache)
				{
				case 0: //Sprach1->Sprache2

					 if (zufall_voc != 0 && zufall_voc != abzufragende_kategorie->anzahl_in_kategorie-1)																	//zu entfernende Vok befindet sich mittendrin
					 {
						printf("\nBitte geben sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);// Aufforderung zur Eingabe
						scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
						scanf("%c", &dummy_zeichen);															//Leeren des Puffers
						if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
						 {
						 	scanf("%c", &dummy_zeichen);
						 }
						strlwr(eingabe);																		// Umwandlung in einen lower String; Groß-Kleinschreibung egal
						if(strcmp(eingabe, cursor_ptr->vokabel_sprache2) == 0)  								//Vergleich der beiden Strings.
						 {
						 printf("Ihre Eingabe war richtig!\n");											//Ausgabe eines Feedbacks
						 anzahl_korrekter_voc++;															// Counter für richtige Vokabeln wird hochgesetzt
						 }
						 else
						 {
						 	printf("Leider falsch! Korrekte waere gewesen: %s\n", cursor_ptr->vokabel_sprache2);   //Feedback mit richtiger Übersetzung
						 }
						help_ptr->next_vokabel =cursor_ptr->next_vokabel;
						abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;
					 }

					 else if(zufall_voc == 0)																// Vok am listenanfang
					 {
					 	printf("\nBitte geben sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);// Aufforderung zur Eingabe
					 	scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
					 	scanf("%c", &dummy_zeichen);															//Leeren des Puffers
					 	if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
					 	{
					     	scanf("%c", &dummy_zeichen);
					 	}
					 	strlwr(eingabe);																		// Umwandlung in einen lower String; Groß-Kleinschreibung egal
					 	if(strcmp(eingabe, cursor_ptr->vokabel_sprache2) == 0)  								//Vergleich der beiden Strings.
					 	{
					 		printf("Ihre Eingabe war richtig!\n");
					 		anzahl_korrekter_voc++;
					 	}
					 	else
					 	{
					 		printf("Leider falsch! Korrekte waere gewesen: %s\n", cursor_ptr->vokabel_sprache2);
					 	}
					 	abzufragende_kategorie->erste_vokabel = cursor_ptr->next_vokabel;	//erste Vokabel wird eins weitergesetzt
					 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;
					 }

					 else if(zufall_voc ==abzufragende_kategorie->anzahl_in_kategorie-1)
					 {
					 	printf("\nBitte geben sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);
					 	scanf("%[^\r\n]", eingabe);
					 	scanf("%c", &dummy_zeichen);
					 	if(dummy_zeichen == '\r')
					 	{
					 		scanf("%c", &dummy_zeichen);
					 	}
					 	strlwr(eingabe);
					 	if(strcmp(eingabe, cursor_ptr->vokabel_sprache2) == 0)
					 	{
					 		printf("Ihre Eingabe war richtig!\n");
					 		anzahl_korrekter_voc++;
					 	}
					 	else
					 	{
					 		printf("Leider falsch! Korrekte waere gewesen: %s\n", cursor_ptr->vokabel_sprache2);
					 	}
					 	help_ptr->next_vokabel = NULL;
					 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;
					 }

				break;


				case 1: //Sprache2 ->Sprache1

					 if (zufall_voc != 0 && zufall_voc != abzufragende_kategorie->anzahl_in_kategorie-1)																	//zu entfernende Vok befindet sich mittendrin
						 {
							printf("\nBitte geben sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);// Aufforderung zur Eingabe
							scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
							scanf("%c", &dummy_zeichen);															//Leeren des Puffers
							if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
							 {
							 	scanf("%c", &dummy_zeichen);
							 }
							strlwr(eingabe);																		// Umwandlung in einen lower String; Groß-Kleinschreibung egal
							if(strcmp(eingabe, cursor_ptr->vokabel_sprache1) == 0)  								//Vergleich der beiden Strings.
							 {
							 printf("Ihre Eingabe war richtig!\n");											//Ausgabe eines Feedbacks
							 anzahl_korrekter_voc++;															// Counter für richtige Vokabeln wird hochgesetzt
							 }
							 else
							 {
							 	printf("Leider falsch! Korrekte waere gewesen: %s\n", cursor_ptr->vokabel_sprache1);   //Feedback mit richtiger Übersetzung
							 }
							help_ptr->next_vokabel =cursor_ptr->next_vokabel;
							abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;
						 }

						 else if(zufall_voc == 0)																// Vok am listenanfang
						 {
						 	printf("\nBitte geben sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);// Aufforderung zur Eingabe
						 	scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
						 	scanf("%c", &dummy_zeichen);															//Leeren des Puffers
						 	if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
						 	{
						     	scanf("%c", &dummy_zeichen);
						 	}
						 	strlwr(eingabe);																		// Umwandlung in einen lower String; Groß-Kleinschreibung egal
						 	if(strcmp(eingabe, cursor_ptr->vokabel_sprache1) == 0)  								//Vergleich der beiden Strings.
						 	{
						 		printf("Ihre Eingabe war richtig!\n");
						 		anzahl_korrekter_voc++;
						 	}
						 	else
						 	{
						 		printf("Leider falsch! Korrekte waere gewesen: %s\n", cursor_ptr->vokabel_sprache1);
						 	}
						 	abzufragende_kategorie->erste_vokabel = cursor_ptr->next_vokabel;	//erste Vokabel wird eins weitergesetzt
						 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;
						 }

						 else if(zufall_voc ==abzufragende_kategorie->anzahl_in_kategorie-1)
						 {
						 	printf("\nBitte geben sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);
						 	scanf("%[^\r\n]", eingabe);
						 	scanf("%c", &dummy_zeichen);
						 	if(dummy_zeichen == '\r')
						 	{
						 		scanf("%c", &dummy_zeichen);
						 	}
						 	strlwr(eingabe);
						 	if(strcmp(eingabe, cursor_ptr->vokabel_sprache1) == 0)
						 	{
						 		printf("Ihre Eingabe war richtig!\n");
						 		anzahl_korrekter_voc++;
						 	}
						 	else
						 	{
						 		printf("Leider falsch! Korrekte waere gewesen: %s\n", cursor_ptr->vokabel_sprache1);
						 	}
						 	help_ptr->next_vokabel = NULL;
						 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;
						 }


				break;


				default: printf("Interner Random Fehler!\n");
				}

		}




	return(anzahl_korrekter_voc);
}
