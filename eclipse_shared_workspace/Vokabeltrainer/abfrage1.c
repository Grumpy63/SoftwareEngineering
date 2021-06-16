/*
 * abfrage1.c
 *
 *  Created on: 08.06.2021
 *      Author: Alexander Hein
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"								//Einbinden der Header-Dateien


int abfrage1(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{

int anzahl_korrekter_voc = 0;
struct vokabel* cursor_ptr = NULL; 																//Cursor soll auf die abzufragende Vokabel zeigen
struct vokabel* help_ptr = NULL;														// Hilfszeiger soll auf vorherige Vokabel in Liste zeigen


int zufall = 0;
char dummy_zeichen = ' ';
char eingabe [256];


	scanf("%c", &dummy_zeichen);																//Leeren des Puffers
			if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}



 for(int i=0; i<number_abzufragende_voc; i++)
 {

	 cursor_ptr = abzufragende_kategorie->erste_vokabel;
	 help_ptr = abzufragende_kategorie->erste_vokabel;


	 srand(time(NULL));
	 zufall =irand(0, abzufragende_kategorie->anzahl_in_kategorie-1);

	 for(int i=0; i<zufall; i++)
	 {
		 cursor_ptr = cursor_ptr->next_vokabel;
	 }

	 if(zufall>1)
	 {
		 for(int i=0; i<zufall-1;i++)
		 {
			 help_ptr = help_ptr->next_vokabel;
		 }
	 }

	 if (zufall != 0 && zufall != abzufragende_kategorie->anzahl_in_kategorie-1)																	//zu entfernende Vok befindet sich mittendrin
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

	 else if(zufall == 0)																// Vok am listenanfang
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

	 else if(zufall ==abzufragende_kategorie->anzahl_in_kategorie-1)
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

	 cursor_ptr = NULL;
	help_ptr = NULL;


 }
	return(anzahl_korrekter_voc)	;
}
