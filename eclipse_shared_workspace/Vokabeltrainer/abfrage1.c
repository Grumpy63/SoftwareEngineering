/*
 * abfrage1.c
 *
 *  Created on: 08.06.2021
 *      Author: Alexander Hein
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"																//Einbinden der Header-Dateien
#include <time.h>    																	// Headerfile für die Verwendung der Funktion: time()


/*	aktualisiert 16.06.21: Flags ersetzt durch verkettete Liste
 * +bessere Performance besonders bei der Laufzeit
 *
 *
 * Funktion zur Abfrage der Vokabeln: Richtung/Modus 1: Sprache 1 -> Sprache 2
 *
 *	sie erhält die Kategorie, die abgefragt werden soll sowie anzahl der abzufragenden Vokabeln
 * 	fragt nach zufallsprinzip den Nutzer Vokabeln ab und vergleicht Eingabe
 * 	gibt nach jeder Eingabe Feedback
 * 	liefert als Rückgabe einen Integer Wert mit der Anzahl der richtigen Vokabeln
 *
 */



int abfrage1(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{


int anzahl_korrekter_voc = 0;
struct vokabel* cursor_ptr = NULL; 														//Cursor soll auf die abzufragende Vokabel zeigen
struct vokabel* help_ptr = NULL;														// Hilfszeiger soll auf vorherige Vokabel in Liste zeigen


int zufall = 0;																			// Variable zum Abspeichern der Zufallszahl
char dummy_zeichen = ' ';																// Dummy zeichen zum Realisieren von Leerzeichen
char dummy_array[255];
char eingabe [256];																		// Array zum Zwischenspeichern der Eingabe


	scanf("%c", &dummy_zeichen);														//Leeren des Puffers
			if(dummy_zeichen == '\r')													//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}



 for(int i=0; i<number_abzufragende_voc; i++)											//Abfragezyklus mit Laufvariable i = Anzahl der abzufragenden Vok/Zyklen
 {

	 cursor_ptr = abzufragende_kategorie->erste_vokabel;								// BEide Pointer zeigen erstmal auf Listenanfang und somit erste Vokabel
	 help_ptr = abzufragende_kategorie->erste_vokabel;


	 srand(time(NULL));																	//Zufallzahl unabhängig von System!!! Sehr wichtig sonst kein Zufall
	 zufall =irand(0, abzufragende_kategorie->anzahl_in_kategorie-1);					//Generieren der Zufallszahl für abfragereihenfolge mit irand funktion


	 for(int i=0; i<zufall; i++)														// For schleife um Liste je nach Zufallszahl durchzugehen bis gewünschte vok erreicht ist
	 {
		 cursor_ptr = cursor_ptr->next_vokabel;
	 }

	 if(zufall>1)																		//Sobald dritte Vok abgefragt wird also zafall =2 -> 3. Vok: bewegt sich Helppointer
	 {
		 for(int i=0; i<zufall-1;i++)													//Pointer wandert cursor immer eine vok hinterher
		 {
			 help_ptr = help_ptr->next_vokabel;
		 }
	 }

	 if (zufall != 0 && zufall != abzufragende_kategorie->anzahl_in_kategorie-1)				//zu entfernende Vok befindet sich mittendrin
	 {
		 abfrage11:
		printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);// Aufforderung zur Eingabe
		eingabe[0] = ' ';
		scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
		scanf("%c", &dummy_zeichen);										//Leeren des Puffers
					if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}
		if(eingabe[0] == ' ')
		{
			printf("Bitte geben Sie eine gültige Antwort an.\n");
			goto abfrage11;
		}


		strlwr(eingabe);																		// Umwandlung in einen lower String; Groß-Kleinschreibung egal

		if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache2)) == 0)  						//Vergleich der beiden Strings groß/kleinschreibung egal.
		 {
			printf("Ihre Eingabe war richtig! ");												//Ausgabe eines Feedbacks
			anzahl_korrekter_voc++;																// Counter für richtige Vokabeln wird hochgesetzt
		 }
		 else
		 {
		 	printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache2);   //Feedback mit richtiger Übersetzung
		 }
		help_ptr->next_vokabel =cursor_ptr->next_vokabel;											//weiterouten der vorherigen vok auf die Übernächste => vok auf die cursor ptr zeigt wird gelöscht bzw. nicht mehr berücksichtigt
		abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;	//Angleich der Anzahl in Kategorie nach Löschen einer Vok.
		printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));
	 }

	 else if(zufall == 0)																			// Vok am listenanfang die entfernt wird
	 {
		 abfrage12:
	 	printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);	// Aufforderung zur Eingabe
	 	eingabe[0] = ' ';
	 	scanf("%[^\r\n]", eingabe);																	//Es können auch Leerzeichen eingegeben werden
	 	scanf("%c", &dummy_zeichen);										//Leeren des Puffers
	 				if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
	 				{
	 					scanf("%c", &dummy_zeichen);
	 				}
	 	if(eingabe[0] == ' ')
	 			{
	 				printf("Bitte geben Sie eine gültige Antwort an.\n");
	 				goto abfrage12;
	 			}


	 	strlwr(eingabe);																			// Umwandlung in einen lower String; Groß-Kleinschreibung egal

	 	if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache2)) == 0)  									//Vergleich der beiden Strings mit feedback und zählen der Richtigen
	 	{
	 		printf("Ihre Eingabe war richtig! ");
	 		anzahl_korrekter_voc++;
	 	}
	 	else
	 	{
	 		printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache2);
	 	}
	 	abzufragende_kategorie->erste_vokabel = cursor_ptr->next_vokabel;							//erste Vokabel wird eins weitergesetzt, somit neuer listenanfang und alte erste vokabel wird gelöscht
	 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;	//Angleich der Vokabelanzahl
	 	printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));
	 }

	 else if(zufall ==abzufragende_kategorie->anzahl_in_kategorie-1)								//die zu löschende Vokabel ist die letzte der liste
	 {
		 abfrage13:
	 	printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);	//Aufforderung zur eingabe
	 	eingabe[0] = ' ';
	 	scanf("%[^\r\n]", eingabe);
	 	scanf("%c", &dummy_zeichen);										//Leeren des Puffers
	 				if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
	 				{
	 					scanf("%c", &dummy_zeichen);
	 				}
	 	if(eingabe[0] == ' ')
	 			{
	 				printf("\nBitte geben Sie eine gültige Antwort an.");
	 				goto abfrage13;
	 			}


	 	strlwr(eingabe);																					//Umwandlung in Lower string, groß/kleinschreibung spielt keine rolle mehr

	 	if(strcmp(eingabe, strlwr( cursor_ptr->vokabel_sprache2)) == 0)												//Vergleich der eingabe mit lösung aus liste
	 	{
	 		printf("Ihre Eingabe war richtig! ");															//positives feedback
	 		anzahl_korrekter_voc++;																			//Zahl der richtigen wird erhöht
	 	}
	 	else
	 	{
	 		printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache2);			//anzeigen der Verbesserung
	 	}
	 	help_ptr->next_vokabel = NULL;																		//neues listenende wird realisiert! ehemalige letzte Vokabel von cursor ptr spielt keine rolle mehr
	 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;			//Angleich der Vokabelanzahl in kategorie
	 	printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));
	 }

	 cursor_ptr = NULL;																						//Beide verwendeten Pointer werden genullt für nächsten abfragezyklus/durchlauf der forschleife
	help_ptr = NULL;


 }
	return(anzahl_korrekter_voc);																			//Rückgabe der Anzahl der Richtigen Vokabel für die Auswertung sowie Highscore liste sehr wichtig!
}
