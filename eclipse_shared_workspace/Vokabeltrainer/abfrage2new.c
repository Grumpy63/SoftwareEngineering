/*
 * abfrage2new.c
 *
 *  Created on: 15.06.2021
 *      Author: Alexander Hein
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"																		//Einbinden der Header-Dateien


/*	aktualisiert 16.06.21: Flags ersetzt durch verkettete Liste
 * +bessere Performance besonders bei der Laufzeit
 *
 *
 * Funktion zur Abfrage der Vokabeln: Richtung/Modus 2: Sprache 2 -> Sprache 1
 *
 *	sie erhält die Kategorie, die abgefragt werden soll sowie anzahl der abzufragenden Vokabeln
 * 	fragt nach zufallsprinzip den Nutzer Vokabeln ab und vergleicht Eingabe
 * 	gibt nach jeder Eingabe Feedback
 * 	liefert als Rückgabe einen Integer Wert mit der Anzahl der richtigen Vokabeln
 *
 */


int abfrage2(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{

int anzahl_korrekter_voc = 0;
struct vokabel* cursor_ptr = NULL; 																//Cursor soll auf die abzufragende Vokabel zeigen
struct vokabel* help_ptr = NULL;																// Hilfszeiger soll auf vorherige Vokabel in Liste zeigen


int zufall = 0;																					// Variable zum Abspeichern der Zufallszahl
char dummy_zeichen = ' ';																		// Dummy zeichen zum Realisieren von Leerzeichen
char eingabe [256];																				// Array zum Zwischenspeichern der Eingabe


	scanf("%c", &dummy_zeichen);																//Leeren des Puffers
			if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}



 for(int i=0; i<number_abzufragende_voc; i++)													//Abfragezyklus mit Laufvariable i = Anzahl der abzufragenden Vok/Zyklen
 {

	 cursor_ptr = abzufragende_kategorie->erste_vokabel;										// BEide Pointer zeigen erstmal auf Listenanfang und somit erste Vokabel
	 help_ptr = abzufragende_kategorie->erste_vokabel;


	 srand(time(NULL));																			//Zufallzahl unabhängig von System!!! Sehr wichtig sonst kein Zufall
	 zufall =irand(0, abzufragende_kategorie->anzahl_in_kategorie-1);							//Generieren der Zufallszahl für abfragereihenfolge mit irand funktion

	 for(int i=0; i<zufall; i++)																// For schleife um Lste je nach Zufallszahl durchzugehen bis gewünschte vok erreicht ist
	 {
		 cursor_ptr = cursor_ptr->next_vokabel;
	 }

	 if(zufall>1)																				//Sobald dritte Vok abgefragt wird also zafall =2 -> 3. Vok: bewegt sich Helppointer
	 {
		 for(int i=0; i<zufall-1;i++)															//Pointer wandert cursor immer eine vok hinterher
		 {
			 help_ptr = help_ptr->next_vokabel;
		 }
	 }

	 if (zufall != 0 && zufall != abzufragende_kategorie->anzahl_in_kategorie-1)				//zu entfernende Vok befindet sich mittendrin
	 {
		 abfrage21:																				//Beginn abfrage
		printf("\nBitte geben Sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);// Aufforderung zur Eingabe
		eingabe[0]	= ' ';
		scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
		scanf("%c", &dummy_zeichen);										//Leeren des Puffers
		if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
			{
			scanf("%c", &dummy_zeichen);
			}
		if(eingabe[0] == ' ')
			{
			printf("Bitte geben Sie eine gueltige Antwort an.\n");
			goto abfrage21;
			}
		strlwr(eingabe);																		// Umwandlung in einen lower String; Groß-Kleinschreibung egal
		if(strcmp(eingabe, cursor_ptr->vokabel_sprache1) == 0)  								//Vergleich der beiden Strings.
		 {
			printf("Ihre Eingabe war richtig!\n");												//Ausgabe eines Feedbacks
			anzahl_korrekter_voc++;																// Counter für richtige Vokabeln wird hochgesetzt
		 }
		 else
		 {
		 	printf("Leider falsch! Korrekt waere gewesen: %s\n", cursor_ptr->vokabel_sprache1);   //Feedback mit richtiger Übersetzung
		 }

		help_ptr->next_vokabel =cursor_ptr->next_vokabel;										//Weiterrouten vorletztes Element auf übernächstes Listenelement => Löschen des Jetzigen Elements (cursor ptr)
		abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;	//Angleichen der Vokabelanzahl nach Löschen
	 }

	 else if(zufall == 0)																		// Vok am listenanfang wird entfernt
	 {
		 abfrage22:
	 	printf("\nBitte geben Sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);// Aufforderung zur Eingabe
	 	eingabe[0]	= ' ';
	 	scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
	 	scanf("%c", &dummy_zeichen);										//Leeren des Puffers
	 	if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
	 		{
	 		scanf("%c", &dummy_zeichen);
	 		}
	 	if(eingabe[0] == ' ')
	 		{
	 		printf("Bitte geben Sie eine gueltige Antwort an.\n");
	 		goto abfrage22;
	 		}

	 	strlwr(eingabe);																		// Umwandlung in einen lower String; Groß-Kleinschreibung egal

	 	if(strcmp(eingabe, cursor_ptr->vokabel_sprache1) == 0)  								//Vergleich der beiden Strings mit feedback etc.
	 	{
	 		printf("Ihre Eingabe war richtig!\n");
	 		anzahl_korrekter_voc++;
	 	}
	 	else
	 	{
	 		printf("Leider falsch! Korrekt waere gewesen: %s\n", cursor_ptr->vokabel_sprache1);
	 	}

	 	abzufragende_kategorie->erste_vokabel = cursor_ptr->next_vokabel;						//erste Vokabel wird eins weitergesetzt, neuer Listenanfang
	 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1; //Angleich der Anzahl nach Löschen des ersten Elements
	 }

	 else if(zufall ==abzufragende_kategorie->anzahl_in_kategorie-1)							//letztes Element wird entfernt
	 {
		 abfrage23:
	 	printf("\nBitte geben Sie die Uebersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);// Aufforderung zur Eingabe. Rest siehe oben
	 	eingabe[0]	= ' ';
	 	scanf("%[^\r\n]", eingabe);
	 	scanf("%c", &dummy_zeichen);										//Leeren des Puffers
	 	if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
	 		{
	 		scanf("%c", &dummy_zeichen);
	 		}
	 	if(eingabe[0] == ' ')
	 		{
	 		printf("Bitte geben Sie eine gueltige Antwort an.\n");
	 		goto abfrage23;
	 	}

	 	strlwr(eingabe);																		//Umwandlung in Lowerstring; hiermit spielt Groß und kleinschreibung keine Rolle mehr

	 	if(strcmp(eingabe, cursor_ptr->vokabel_sprache1) == 0)									//Vergleich der Eingabe mit Listenelement inkl. Feedback etc.
	 	{
	 		printf("Ihre Eingabe war richtig!\n");
	 		anzahl_korrekter_voc++;
	 	}
	 	else
	 	{
	 		printf("Leider falsch! Korrekt waere gewesen: %s\n", cursor_ptr->vokabel_sprache1);
	 	}

	 	help_ptr->next_vokabel = NULL;																	//Bestimmen eines neuen Listenende, Herauslöschen des letzten Elements
	 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;		//Angleich der Vokabelanzahl in Kategorie
	 }

	cursor_ptr = NULL;													//Verwendete Zeiger werden wieder geerdet
	help_ptr = NULL;






 }
	return(anzahl_korrekter_voc);			//Rückgabe der Anzahl der richtigen Vokabel, wichtig für die sich anschließende Auswertung mit Highscore liste.
}


