/*
 * abfrage3.c
 *
 *  Created on: 08.06.2021
 *      Author: Luca
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"voc_functions.h"
#include <string.h>
#include <time.h>



/*	aktualisiert 16.06.21: Flags ersetzt durch verkettete Liste
 * +bessere Performance besonders bei der Laufzeit
 *
 *aktualisiert 20.06.21: Realisierung eines Eingabeschutzes: Einfügen von Sprüngen
 *
 *
 *
 * Funktion zur Abfrage der Vokabeln: Richtung/Modus 3: Sprache 1 -> Sprache 2 oder Sprache 2 -> Sprache 1
 *
 *	sie erhält die Kategorie, die abgefragt werden soll sowie anzahl der abzufragenden Vokabeln
 * 	fragt nach zufallsprinzip den Nutzer Vokabeln ab und vergleicht Eingabe PLUS zufällige Abfragerichtung
 * 	gibt nach jeder Eingabe Feedback
 * 	liefert als Rückgabe einen Integer Wert mit der Anzahl der richtigen Vokabeln
 *
 */



int abfrage3(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{
	int anzahl_korrekter_voc = 0;
	struct vokabel* cursor_ptr = NULL; 										//Cursor auf aktuelle abzufragende Vokabel
	struct vokabel* help_ptr = NULL;										//Hilfszeiger auf vorherige Vokabel, wichtig beim Löschen von Elementen
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

				cursor_ptr = abzufragende_kategorie->erste_vokabel;			//Beide Pointer zeigen auf die erste Vokabel
				help_ptr = abzufragende_kategorie->erste_vokabel;

				for(int x = 0; x < zufall_voc; x++) 						//Zeiger jeweils Vielfaches der Zufallszahl Weitersetzen auf die nächsten Listenelemente
				{
					cursor_ptr = cursor_ptr->next_vokabel;
				}

				if(zufall_voc>1)											//Sobald zweite Vokabel aus Liste gewählt wird, setzt sich Helppointer in Bewegung
				{
					for(int i=0; i<zufall_voc-1;i++)						//Schleife: Help_ptr wandert Cursor immer eine Vokabel hinterher
					{
						help_ptr = help_ptr->next_vokabel;
					}
				}



		//Beginn zufälliger Sprachreihenfolge (1 oder 2) mit Switch case Struktur

				srand(time(NULL));																								//Generieren einer von Zufallszahl für Sprachreihenfolge
				zufall_sprache = irand(0, 1);

				switch(zufall_sprache)
				{
				case 0: 																										// Zufallszahl 0 entspricht: Sprach1->Sprache2

					 if (zufall_voc != 0 && zufall_voc != abzufragende_kategorie->anzahl_in_kategorie-1)						//zu entfernende Vok befindet sich mittendrin
					 {
						 abfrage31:
						printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);					// Aufforderung zur Eingabe
					 	eingabe[0]	= ' ';
					 	scanf("%[^\r\n]", eingabe);
					 	scanf("%c", &dummy_zeichen);																			//Leeren des Puffers
					 	if(dummy_zeichen == '\r')																				//auch auf anderen OS (haben evtl mehr Zeichen)
					 		{
					 		scanf("%c", &dummy_zeichen);
					 		}
					 	if(eingabe[0] == ' ' || eingabe[0] == '\t')																					//Eingabeschutz mit Sprung zu Marker
					 		{
					 		printf("Bitte geben Sie eine gültige Antwort an.\n");
					 		goto abfrage31;
					 	}
						strlwr(eingabe);																						// Umwandlung in einen lower String; Groß-Kleinschreibung egal

						if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache2)) == 0)  										//Vergleich der beiden Strings.
						 {
							printf("Ihre Eingabe: %s war richtig! ", cursor_ptr->vokabel_sprache2);								//Ausgabe eines Feedbacks
							anzahl_korrekter_voc++;																				// Counter für richtige Vokabeln wird hochgesetzt
						 }
						 else
						 {
						 	printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache2);   				//Feedback mit richtiger Übersetzung
						 }
						printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));						//Ausgabe der Anzahl übriger Vokabeln
						help_ptr->next_vokabel =cursor_ptr->next_vokabel;														//Weiterrouten von help_ptr auf Übernächstes Element: hiermit wird abzufragende Vok gelöscht
						abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;				// Angleichen der Anzahl von Vok in Liste, eins weniger
					 }

					 else if(zufall_voc == 0)																					// zu entfernende Vok am listenanfang
					 {
						 abfrage32:
					 	printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);					// Aufforderung zur Eingabe
					 	eingabe[0]	= ' ';
					 	scanf("%[^\r\n]", eingabe);
					 	scanf("%c", &dummy_zeichen);																			//Leeren des Puffers
					 	if(dummy_zeichen == '\r')																				//auch auf anderen OS (haben evtl mehr Zeichen)
					 		{
					 		scanf("%c", &dummy_zeichen);
					 		}
					 	if(eingabe[0] == ' ' || eingabe[0] == '\t')																					//Eingabeschutz mit Sprung zu Marker
					 		{
					 		printf("Bitte geben Sie eine gültige Antwort an.\n");
					 		goto abfrage32;
					 	}

					 	strlwr(eingabe);																						// Umwandlung in einen lower String; Groß-Kleinschreibung egal

					 	if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache2)) == 0)  										//Vergleich der beiden Strings.
					 	{
					 		printf("Ihre Eingabe: %s war richtig! ", cursor_ptr->vokabel_sprache2);								//positives Feedback, Anzahl der Richtigen wird erhöht
					 		anzahl_korrekter_voc++;
					 	}
					 	else
					 	{
					 		printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache2);
					 	}
					 	printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));						//Ausgabe der Anzahl übriger Vokabeln
					 	abzufragende_kategorie->erste_vokabel = cursor_ptr->next_vokabel;										//erste Vokabel wird eins weitergesetzt, neuer Listenanfang
					 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;				//Angleich der Vokabelanzahl in Liste nach rauslöschen
					 }

					 else if(zufall_voc ==abzufragende_kategorie->anzahl_in_kategorie-1)										//zu entfernende Vok am Listenende
					 {
						 abfrage33:
					 	printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache1);					//Beginn der eigentlichen Abfrage
					 	eingabe[0]	= ' ';
					 	scanf("%[^\r\n]", eingabe);
					 	scanf("%c", &dummy_zeichen);																			//Leeren des Puffers
					 	if(dummy_zeichen == '\r')																				//auch auf anderen OS (haben evtl mehr Zeichen)
					 		{
					 		scanf("%c", &dummy_zeichen);
					 		}
					 	if(eingabe[0] == ' ' || eingabe[0] == '\t')																					//Eingabeschutz mit Sprung zu Marker
					 		{
					 		printf("Bitte geben Sie eine gültige Antwort an.\n");
					 		goto abfrage33;
					 	}

					 	strlwr(eingabe);
					 	if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache2)) == 0)											//Vergleich der eingabe mit Listenelement
					 	{
					 		printf("Ihre Eingabe: %s war richtig! ", cursor_ptr->vokabel_sprache2);
					 		anzahl_korrekter_voc++;
					 	}
					 	else
					 	{
					 		printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache2);
					 	}
					 	printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));						//Ausgabe der Anzahl übriger Vokabeln
					 	help_ptr->next_vokabel = NULL;																			//Neues Listenende wird festgelegt, letzte Vok wird rausgelöscht
					 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1; 				//Angleich der Anzahl
					 }

				break;

				case 1: 										// Zufallszahl gleich 1 entspricht: Sprache2 ->Sprache1

					 if (zufall_voc != 0 && zufall_voc != abzufragende_kategorie->anzahl_in_kategorie-1)						//zu entfernende Vok mittendrin in Liste											//zu entfernende Vok befindet sich mittendrin
						 {
						 	 abfrage34:
							printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);				// Aufforderung zur Eingabe
						 	eingabe[0]	= ' ';
						 	scanf("%[^\r\n]", eingabe);
						 	scanf("%c", &dummy_zeichen);																		//Leeren des Puffers
						 	if(dummy_zeichen == '\r')																			//auch auf anderen OS (haben evtl mehr Zeichen)
						 		{
						 		scanf("%c", &dummy_zeichen);
						 		}
						 	if(eingabe[0] == ' ' || eingabe[0] == '\t')																				//Eingabeschutz mit Sprung zu Marker
						 		{
						 		printf("Bitte geben Sie eine gültige Antwort an.\n");
						 		goto abfrage34;
						 	}

							strlwr(eingabe);																					// Umwandlung in einen lower String; Groß-Kleinschreibung egal
							if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache1)) == 0)  									//Vergleich der beiden Strings.
							 {
								printf("Ihre Eingabe: %s war richtig! ", cursor_ptr->vokabel_sprache1);							//Ausgabe eines Feedbacks
								anzahl_korrekter_voc++;																			// Counter für richtige Vokabeln wird hochgesetzt
							 }
							 else
							 {
							 	printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache1);   			//Feedback mit richtiger Übersetzung
							 }
							printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));					//Ausgabe der Anzahl übriger Vokabeln
							help_ptr->next_vokabel =cursor_ptr->next_vokabel;													//Zeiger auf nächstes Listenelement weiterleiten
							abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;
						 }

						 else if(zufall_voc == 0)																				// Vok am listenanfang
						 {
							 abfrage35:
						 	printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);				// Aufforderung zur Eingabe
						 	eingabe[0]	= ' ';
						 	scanf("%[^\r\n]", eingabe);
						 	scanf("%c", &dummy_zeichen);																		//Leeren des Puffers
						 	if(dummy_zeichen == '\r')																			//auch auf anderen OS (haben evtl mehr Zeichen)
						 		{
						 		scanf("%c", &dummy_zeichen);
						 		}
						 	if(eingabe[0] == ' ' || eingabe[0] == '\t')																				//Eingabeschutz mit Sprung zu Marker
						 		{
						 		printf("Bitte geben Sie eine gültige Antwort an.\n");
						 		goto abfrage35;
						 	}

						 		strlwr(eingabe);																				// Umwandlung in einen lower String; Groß-Kleinschreibung egal
						 		if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache1)) == 0)  								//Vergleich der beiden Strings.
						 	{
						 		printf("Ihre Eingabe: %s war richtig! ", cursor_ptr->vokabel_sprache1);
						 		anzahl_korrekter_voc++;
						 	}
						 	else
						 	{
						 		printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache1);
						 	}
						 	printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));					//Ausgabe der Anzahl übriger Vokabeln
						 	abzufragende_kategorie->erste_vokabel = cursor_ptr->next_vokabel;									//erste Vokabel wird eins weitergesetzt
						 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;			//Anzahl wird um eins verringert
						 }

						 else if(zufall_voc ==abzufragende_kategorie->anzahl_in_kategorie-1)									//letzte Vok wird entfernt
						 {
							 abfrage36:
						 	printf("\nBitte geben Sie die Übersetzung von %s ein: ", cursor_ptr->vokabel_sprache2);				//Beginn Abfrage
						 	eingabe[0]	= ' ';
						 	scanf("%[^\r\n]", eingabe);
						 	scanf("%c", &dummy_zeichen);																		//Leeren des Puffers
						 	if(dummy_zeichen == '\r')																			//auch auf anderen OS (haben evtl mehr Zeichen)
						 		{
						 		scanf("%c", &dummy_zeichen);
						 		}
						 	if(eingabe[0] == ' ' || eingabe[0] == '\t')																				//Eingabeschutz mit Sprung zu Marker
						 		{
						 		printf("Bitte geben Sie eine gültige Antwort an.\n");
						 		goto abfrage36;
						 	}

						 	strlwr(eingabe);

						 	if(strcmp(eingabe, strlwr(cursor_ptr->vokabel_sprache1)) == 0)										//Vergleich der Eingabe mit Lösung
						 	{
						 		printf("Ihre Eingabe: %s war richtig! ", cursor_ptr->vokabel_sprache1);							//positves feedback mit wdh der  korrekten eingabe
						 		anzahl_korrekter_voc++;
						 	}
						 	else
						 	{
						 		printf("Leider falsch! Korrekt wäre gewesen: %s. ", cursor_ptr->vokabel_sprache1);				//falsch mit verbesserung
						 	}
						 	printf("Es verbleiben %d abzufragende Vokabeln.\n", number_abzufragende_voc-(i+1));					//Ausgabe der Anzahl übriger Vokabeln
						 	help_ptr->next_vokabel = NULL;																		//neues Listenende wird festgelegt
						 	abzufragende_kategorie->anzahl_in_kategorie=abzufragende_kategorie->anzahl_in_kategorie-1;			//Angleich der Vokabelanzahl
						 }

				break;

				default: printf("Interner Random Fehler!\n");
				}
														// Ende der Switchcase Struktur
		}

		return(anzahl_korrekter_voc);																							//Rückgabe der Anzahl der Korrekten Vokabel wichtig für sich anschließende Auswertung
}
