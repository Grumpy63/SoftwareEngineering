/*
 * usernames.c
 *
 *  Created on: 22.05.2021
 *      Author: Luca Elsesser
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"

#define SEMIKOLON 59													//Makro zur Übersichtlichkeit; 59 entspricht  Semikolon in ASCII
int Aufzaehlung = 1;													//Variable zum Aufzählen der Nutzer
int Auswahl = 0;														//Variable zum Abspeichern der eingelesenen Nutzereingabe

struct username *username_list()
{


	FILE* datei_users_ptr = NULL;										//FILE* pointer zum öffnen der Usernames.txt Datei

	char dummy_zeichen = ' ';											//Zum einlesen von Leerzeichen
	int c = 0;															//Char Platzhalter zum auslesen der Datei
	int u = 0;															//Variable benutzt in Erstellung User verkettete Liste

	struct username *user_ptr = NULL;									//Pointer auf struct username um unbegrenzte Useranzahl zu realisieren
	struct username *user_help_ptr = NULL;								//Pointer zum anlegen der Liste (festhalten des letzen users)
	struct username *user_first_ptr = NULL;								//Pointer auf ersten User in der Liste
	struct username *entered_user_ptr = NULL;							//Pointer auf aktuell gewählten User (eventuell Rückgabewert)


	//ZUGRIFF AUF DIE DATEI Usernames.txt
	datei_users_ptr = fopen("Usernames.txt", "r+");								//Versuch Usernames.txt lesend und schreibend zuöffnen
		if (datei_users_ptr == NULL)											//Wenn Versuch fehlschlägt
		{

			entered_user_ptr = malloc(sizeof(struct username));					//Setze entered_user_ptr auf neu erstelltes Element (ersten User)

			username_mark1:
			printf("Noch keine Nutzer bekannt! \nBitte einen neuen Nutzernamen eingeben: ");

			entered_user_ptr->name[0] = ' ';									//Setze den Namen auf 'Leerzeichen'
			scanf("%[^\r\n]", entered_user_ptr->name);							//Es können auch Leerzeichen eingegeben werden
			scanf("%c", &dummy_zeichen);										//Leeren des Puffers
			if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
			{
				scanf("%c", &dummy_zeichen);
			}

			if(entered_user_ptr->name[0] == ' ')								//Wenn der Name nicht geändert wurde (d.h. einfach Enter gedrückt) frage erneut den Namen
			{
				printf("Keine gueltige Eingabe! Bitte beginnen sie den Namen nicht mit einem Leerzeichen.\n");
				goto username_mark1;
			}

			datei_users_ptr = fopen("Usernames.txt", "w+");						//Wenn Usernames.txt Datei also nicht existiert, erstelle sie (nachdem ein Nutzer eingegeben wurde)
						if(datei_users_ptr == NULL)								//Überprüfung ob Erstellung erfolgreich war
						{
							printf("Datei Usernames.txt konnte NICHT erstellt werden!\n");
							return 0;
						}

			fprintf(datei_users_ptr, entered_user_ptr->name);					//Eingegebenen Nutzernamen in die Datei Usernames.txt schreiben
			fprintf(datei_users_ptr, ";");										//Anhängen des Semikolons in Datei Usernames.txt für Konformität
			printf("Nutzer erfolgreich angelegt!\n");
			fclose(datei_users_ptr);											//Schließe den Datastream um Änderung in Usernames.txt wirksam zu speichern
			return(entered_user_ptr);											//return Pointer auf den aktuellen User
		}
		else																	//Wenn Datei existiert (und entsprechend schon ein User bekannt ist); alle bekannten User auflisten
		{


			user_ptr = malloc(sizeof(struct username));							//erstmaliges anlegen eines user-platzes auf der Liste (mindestens ein User existiert wenn Datei Usernames.txt existiert)
			user_first_ptr = user_ptr;											//user_first_ptr hält den Anfang der Liste fest (ersten Nutzer)


						//ANLEGEN EINER VERKETTETEN LISTE MIT ALLEN BESTEHENDEN USER
						while(	(c = fgetc(datei_users_ptr) ) != EOF)					//Schleife für das auflisten aller Usernames, solange nicht end of file erreicht
								{

									if( c != SEMIKOLON )								//Wenn KEIN Semikolon kommt
									{
										user_ptr->name[u] = c;							//Buchstabe einlesen
										u++;											//Nächste Stelle im Namensarray belegen
									}
									else												//Wenn strichpunkt: nächsten Nutzer anlegen
									{
										user_help_ptr = user_ptr;						//Hilfspointer zeigt auf letzten User
										user_ptr = malloc(sizeof(struct username));		//Neuer User wird angelegt (IMMER nach Semikolon, auch wenn keiner Folgt führt zu zusätzlichem Zeilenumbruch)
										user_help_ptr->next_user = user_ptr;			//Neuer User wird an letzten User angehängt
										u = 0;											//Rücksetzen der Variable zum wiederverwenden in der oberen if-Bedingung
									}
								}

						free(user_ptr);													//Löschen des Überflüssigen letzten User-Elements


						user_help_ptr->next_user = NULL;								//Next Pointer des jetzt letzten Elements (nachdem leerer User gelöscht wurde) wird geerdet; Programmchrashed hier wenn Usernames.txt leer ist
						user_ptr = NULL;												//Pointer werden geerdet
						user_help_ptr = NULL;											//Pointer werden geerdet


						mark1:															//Sprungmarke mark1
						Aufzaehlung = 1;												//Variable Aufzaehlung auf 1 gesetzt
						//Ausgeben aller Nutzer aus der verketteten Liste
						user_ptr = user_first_ptr;										//Beginn am Anfang der verketteten Liste
						printf("(%d) Neuen Nutzer anlegen\n", Aufzaehlung);				//Ausgabe der Aufzählung aller Nutzer
						Aufzaehlung++;													//Variable Aufzaehlung wird um eins inkrementiert
						while (user_ptr != NULL)										//Solang bis Liste zuende ist
							{
							printf("(%d) %s\n", Aufzaehlung, user_ptr->name);			//Gib den aktuellen Namen mit Aufzählung aus
							user_ptr = user_ptr->next_user;								//nächsten Namen auswählen
							Aufzaehlung++;												//Variable Aufzaehlung wird um eins inkrementiert
							}

		}

		char dummy_array[255];
		username_mark3:

		printf("Bitte einen Nutzernamen auswaehlen, oder die Option \"Neuen Nutzer anlegen\" waehlen:\n");		//Aufforderung einen Namen festzulegen

		//Check ob tatsächlich nur eine Zahl eingegeben wurde

		scanf("%d", &Auswahl);																			//Einlesen der Nutzereingabe für Variable Auswahl

		if(Auswahl > Aufzaehlung)																		//If-Abfrage ob Variable Auswahl größer ist als die Variable Aufzaehlung
		{
			printf("FalscheEingabe");																	//Ausgeben einer Nachricht für den Nutzer
		}

		scanf("%c", &dummy_zeichen);																	//Leeren des Puffers
		if(dummy_zeichen == '\r')																		//auch auf anderen OS (haben evtl mehr Zeichen)
							{
								scanf("%c", &dummy_zeichen);
							}

		//Auswahl neuen User anlegen
		if(Auswahl == 1)																				//If-Abfrage ob Variable Auswahl 1 ist
		{

			entered_user_ptr = malloc(sizeof(struct username));											//Allokieren einer neuen struct username auf den pointer entered_user_ptr

			username_mark2:																				//Rücksprung bei fehlerhafter Namenseingabe
			printf("Bitte den Namen des neuen Users eingeben:");										//Ausgeben einer Anweisung für den Nutzer
			entered_user_ptr->name[0] = ' ';															//Setze den Namen auf 'Leerzeichen'
			scanf("%[^\r\n]", entered_user_ptr->name);													//User mit Leerzeichen eingeben

			scanf("%c", &dummy_zeichen);																//Leeren des Puffers
			if(dummy_zeichen == '\r')																	//auch auf anderen OS (haben evtl mehr Zeichen)
				{
					scanf("%c", &dummy_zeichen);
				}

			//Prüfen ob eingegebener User mit Leerzeichen beginnt, oder ob einfach Leerzeichen betätigt wurde statt einen Namen einzugeben

			if(entered_user_ptr->name[0] == ' ')														//Wenn der Name nicht geändert wurde (d.h. einfach Enter gedrückt) frage erneut den Namen
			{
				printf("Keine gueltige Eingabe! Bitte beginnen sie den Namen nicht mit einem Leerzeichen.\n");
				goto username_mark2;																	//Rücksprung zur Abfrage des Namens
			}

			//Prüfen ob eingegebener User bereits vorhanden
			user_ptr = user_first_ptr;																	//Pointer user_ptr auf den Listenanfang (Pointer user_first_ptr) setzen

			while(user_ptr != NULL)																		//While-Schleife wenn user_ptr nicht auf Null zeigt und Variable t=0 ist
			{
				if(strcmp(user_ptr->name,entered_user_ptr->name) == 0)									//Vergleich der Strings user_ptr->name und entered_user_ptr->name (überprüfen ob eingegebener String bereits vorhanden)
				{
					printf("Der eingegebene User besteht bereits!\n");									//Nutzerhinweis ausgeben
					free(entered_user_ptr);																//Allokierter Speicher wird wieder frei gegeben
					goto mark1;																			//Rücksprung zu mark1
				}
				else																					//Else-Verzweigung
				{
					user_ptr = user_ptr->next_user;														//Pointer user_ptr wird um eins weiter gesetzt auf user_ptr->next_user (Durchlaufen der Liste)
					continue;																			//Erneutes Durchlaufen der While-Schleife
				}
			}

			fprintf(datei_users_ptr, entered_user_ptr->name);											//Angelegter Name wird  in Usernames.txt angehängt
			fprintf(datei_users_ptr, ";");																//Semikolon wird angehängt
			printf("Neuer Nutzer %s wurde erfolgreich angelegt.\n", entered_user_ptr->name);			//Nutzerhinweis ausgeben
			fclose(datei_users_ptr);																	//File wird geschlossen
			return(entered_user_ptr);																	//Pointer auf den ausgewählten Nutzer wird zurückgegeben
		}
		//Bestehenden User ausgewählt
		else																							//Else-Verzweigung
		{
			if(Auswahl > (Aufzaehlung - 1) || Auswahl <= 0)												//Eingabeüberprüfung der Nutzereingabe
				{
					printf("Die Eingabe ist ungueltig! ");												//Ausgabe einer Informationsnachricht für den Nutzer
					printf("Bitte waehlen sie eine der angebotenen Zahlen.\n");							//Ausgabe einer Informationsnachricht für den Nutzer
					scanf("%[^\r\n]", dummy_array);
					goto username_mark3;																//Sprung zur Abfrage
				}

			Aufzaehlung = 2;																			//Die Variable Aufzaehlung auf 2 setzen
			user_ptr = user_first_ptr;																	//Durchlaufpointer entity_name_ptr auf die erste Struct setzen mit erste_entity_name_ptr

			while(Auswahl != Aufzaehlung)																//While-Schleife zum Durchlaufen der Struct entitiy_name bis der Pointer entity_name_ptr auf die Auswahl zeigt
			{
				user_ptr = user_ptr->next_user;															//Pointer entity_name_ptr auf das folgende Element setzen
				Aufzaehlung++;																			//Variable Aufzaehlung um eins inkrementieren
				continue;																				//Neuer Durchlauf der While-Schleife
			}

		printf("Nutzer %s wurde erfolgreich ausgewaehlt.\n", user_ptr->name);							//Nutzerhinweis ausgeben
		fclose(datei_users_ptr);																		//File wird geschlossen
		return(user_ptr);																				//Der pointer user_ptr wird aus der Funktion zurück gegeben
		}



	fclose(datei_users_ptr);																			//File wird geschlossen
	return(entered_user_ptr);																			//Pointer auf den ausgewählten Nutzer wird zurückgegeben
}
