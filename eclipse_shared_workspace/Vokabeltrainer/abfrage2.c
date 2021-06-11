/*
 * abfrage2.c
 *
 *  Created on: 08.06.2021
 *      Author: Alexander Hein
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"																		//Einbinden der Header-Dateien


/*	Funktion zur Abfrage der Vokabeln: Richtung/Modus 2: Sprache 2 -> Sprache 1
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
struct vokabel* help_hinterher_ptr = NULL;														// Hilfszeiger soll auf vorherige Vokabel in Liste zeigen
struct kategorie* listenanfang_ptr =NULL;														// Zeiger um den Listenanfang zu verändern
struct vokabel* merker_ptr = NULL;																// Merker für die "Löschen-Fkt"
int zufall = 0;
char dummy_zeichen = ' ';
char eingabe [256];


	scanf("%c", &dummy_zeichen);																//Leeren des Puffers
			if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}


	for (int i=0; i<number_abzufragende_voc; i++)												//Schleife für die Abfragezyklen, i ist Laufvariable
	{
			//reroll:																			// Auskommentiert weil alte Lösung
			srand(time(NULL));																	//Generieren einer Zufallszahl von int in Bereich 0 bis x
			zufall = irand(0, abzufragende_kategorie->anzahl_in_kategorie);


			cursor_ptr = abzufragende_kategorie->erste_vokabel;									//Hilfszeiger auf Beginn der Vokabelliste
			help_hinterher_ptr = abzufragende_kategorie->erste_vokabel;
			listenanfang_ptr = abzufragende_kategorie;

			for(int x=0; x < (zufall-1); x++) 													//Cursor-Zeiger jeweils Vielfaches der Zufallszahl Weitersetzen auf die nächsten Listenelemente
				{
					cursor_ptr = cursor_ptr->next_vokabel;										//Cursor zeigt immer auf die abzufragende Vokabel
				}

			if(zufall>= 2) 																		// erst wenn cursor auf drittes Listenelement zeigt bewegt sich hinterher_ptr
				{
					for(int z=0; z < (zufall-1); z++)											//Hilfszeiger wandert Cursor immer eins hinterher
						{
							help_hinterher_ptr = help_hinterher_ptr->next_vokabel;				//zeigt also auf vorherige Vok in Liste
						}
				}

/*																								//optional, eleganter als if, else if..., noch nicht fertig
 * switch (zufall)
			{
			limit festlegen
			case 0: listenanfang_ptr->erste_vokabel = cursor_ptr->next_vokabel; break;
			case limit: help_hinterher_ptr->next_vokabel = NULL;  break;
			default: help_hinterher_ptr->next_vokabel = cursor_ptr->next_vokabel;
			}
*/

			if (zufall != 0 && zufall != abzufragende_kategorie->anzahl_in_kategorie)																	//zu entfernende Vok befindet sich mittendrin
				{
					merker_ptr =cursor_ptr->next_vokabel;										//merken der Restliste
					help_hinterher_ptr->next_vokabel = merker_ptr;								//weiterrouten auf die Restliste
				}

			else if(zufall == 0)																// Vok am listenanfang
				{
					listenanfang_ptr->erste_vokabel = cursor_ptr->next_vokabel;					//erste Vokabel wird eins weitergesetzt
				}

			else if(zufall ==abzufragende_kategorie->anzahl_in_kategorie)						//Vok zu löschen am listenende
				{
					help_hinterher_ptr->next_vokabel = NULL;										//generieren eines neuen Listenendes mit Erdung
				}

abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;

/*	alte Lösung: langsamer mit Überprüfung der Flags
 *
 * if(help_ptr->flag == 1)																		//Wenn ausgewählte Vokabel bereits abgefragt ist
			{
				goto reroll;																	//Suche eine neue Vokabel
			}
			else
			{
				help_ptr->flag = 1;  															//Flag der Ausgewählten Vokabel setzen
			}


		help_ptr->flag = 1;									  									//Flag der Ausgewählten Vokabel setzen
*
*/

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

		cursor_ptr = NULL;																		//Zeiger wird wieder geerdet
		listenanfang_ptr = NULL;																//Zeiger wird wieder geerdet
		help_hinterher_ptr = NULL;																//Zeiger wird wieder geerdet
		merker_ptr = NULL;
	}

	return(anzahl_korrekter_voc);																	//Rückgabe der Richtigen
}


