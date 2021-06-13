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

#define SEMIKOLON 59													//Makro zur �bersichtlichkeit; 59 entspricht  Semikolon in ASCII


struct username *username_list()
{


	FILE* datei_users_ptr = NULL;										//FILE* pointer zum �ffnen der Usernames.txt Datei

	char dummy_zeichen = ' ';											//Zum einlesen von Leerzeichen
	int c = 0;															//Char Platzhalter zum auslesen der Datei
	int u = 0;															//Variable benutzt in Erstellung User verkettete Liste
	int t = 0;															//Variable f�r Vergleich der Nutzernamen (Merker: ist Name bereits bekannt?)

	struct username *user_ptr = NULL;									//Pointer auf struct username um unbegrenzte Useranzahl zu realisieren
	struct username *user_help_ptr = NULL;								//Pointer zum anlegen der Liste (festhalten des letzen users)
	struct username *user_first_ptr = NULL;								//Pointer auf ersten User in der Liste
	struct username *entered_user_ptr = NULL;							//Pointer auf aktuell gew�hlten User (eventuell R�ckgabewert)


	//ZUGRIFF AUF DIE DATEI Usernames.txt
	datei_users_ptr = fopen("Usernames.txt", "r+");								//Versuch Usernames.txt lesend und schreibend zu�ffnen
		if (datei_users_ptr == NULL)											//Wenn Versuch fehlschl�gt
		{

			printf("Noch keine Nutzer bekannt! \nBitte einen neuen Nutzernamen eingeben: ");

			entered_user_ptr = malloc(sizeof(struct username));					//Setze entered_user_ptr auf neu erstelltes Element (ersten User)
			scanf("%[^\r\n]", entered_user_ptr->name);							//Es k�nnen auch Leerzeichen eingegeben werden
			scanf("%c", &dummy_zeichen);										//Leeren des Puffers
			if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
			{
				scanf("%c", &dummy_zeichen);
			}


			datei_users_ptr = fopen("Usernames.txt", "w+");						//Wenn Usernames.txt Datei also nicht existiert, erstelle sie
						if(datei_users_ptr != 0)								//aber erst nachdem ein User eingegeben wurde
						{
							printf("Datei Usernames.txt konnte erstellt werden\n");
						}

			fprintf(datei_users_ptr, entered_user_ptr->name);					//Eingegebenen Nutzernamen in die Datei Usernames.txt schreiben
			fprintf(datei_users_ptr, ";");										//Anh�ngen des Semikolons in Datei Usernames.txt f�r Konformit�t
			printf("Nutzer erfolgreich angelegt!\n");
			fclose(datei_users_ptr);
			return(entered_user_ptr);											//return 1 f�r neuer Nutzer erstellt
		}
		else																	//Wenn Datei existiert (und entsprechend schon ein User bekannt ist); alle bekannten User auflisten
		{
			printf("Bitte einen der folgenden Nutzer auswaehlen, oder einen neuen Nutzernamen anlegen: \n");


			user_ptr = malloc(sizeof(struct username));							//erstmaliges anlegen eines user-platzes auf der Liste (mindestens ein User existiert wenn Datei Usernames.txt existiert)
			user_first_ptr = user_ptr;											//user_first_ptr h�lt den Anfang der Liste fest (ersten Nutzer)


						//ANLEGEN EINER VERKETTETEN LISTE MIT ALLEN BESTEHENDEN USER
						while(	(c = fgetc(datei_users_ptr) ) != EOF)					//Schleife f�r das auflisten aller Usernames, solange nicht end of file erreicht
								{

									if( c != SEMIKOLON )								//Wenn KEIN Semikolon kommt
									{
										user_ptr->name[u] = c;							//Buchstabe einlesen
										u++;											//N�chste Stelle im Namensarray belegen
									}
									else												//Wenn strichpunkt: n�chsten Nutzer anlegen
									{
										user_help_ptr = user_ptr;						//Hilfspointer zeigt auf letzten User
										user_ptr = malloc(sizeof(struct username));		//Neuer User wird angelegt (IMMER nach Semikolon, auch wenn keiner Folgt f�hrt zu zus�tzlichem Zeilenumbruch)
										user_help_ptr->next_user = user_ptr;			//Neuer User wird an letzten User angeh�ngt
										u = 0;											//R�cksetzen der Variable zum wieder-verwenden in der oberen if-Bedingung
									}
								}

						free(user_ptr);												//L�schen des �berfl�ssigen letzten User-Elements


						user_help_ptr->next_user = NULL;							////CRASHED HIER wenn Usernames.txt leer ist: Next Pointer des jetzt letzten Elements (nachdem leerer User gel�scht wurde) wird geerdet
						user_ptr = NULL;
						user_help_ptr = NULL;




						//Ausgeben aller Nutzer aus der verketteten Liste
						user_ptr = user_first_ptr;										//Beginn am Anfang der verketteten Liste
						while (user_ptr != NULL)										//Solang bis Liste zuende ist
							{
							printf("%s\n", user_ptr->name);								//Gib den aktuellen Namen aus
							user_ptr = user_ptr->next_user;								//n�chsten Namen ausw�hlen
							}

		}


		printf("\nBitte einen Nutzernamen auswaehlen, oder einen neuen Namen eingeben: ");			//Aufforderung einen Namen festzulegen

		entered_user_ptr = malloc(sizeof(struct username));											//Festlegen des Pointers f�r den aktuell gew�hlten User

		scanf("%[^\r\n]", entered_user_ptr->name);													//User mit Leerzeichen eingeben
		scanf("%c", &dummy_zeichen);																//Leeren des Puffers
		if(dummy_zeichen == '\r')																	//auch auf anderen OS (haben evtl mehr Zeichen)
			{
				scanf("%c", &dummy_zeichen);
			}


		//Es erfolgt die �berpr�fung auf die Existenz (Doppelnennung) des Namens

		user_ptr = user_first_ptr;


		while(user_ptr != NULL && t == 0)												//Abbruch wenn Liste vollst�ndig durchlaufen ODER Doppelter Name gefunden wurde
			{
				if( strcmp(user_ptr->name,entered_user_ptr->name) == 0 )				//Wenn Namen gleich sind
					{
					printf("Bestehender Nutzer wurde erfolgreich ausgewaehlt.\n");
					t = 1;																//Merker, dass Nutzer bereits existiert
					}
				else																	//Wenn Namen unterschiedlich sind
					{
					user_ptr = user_ptr->next_user;										//N�chsten user in der Liste testen
					}
			}


		if(t == 0)																		//Wenn eingegebener Nutzer noch nicht existiert
		{
			fprintf(datei_users_ptr, entered_user_ptr->name);							//Angelegter Name wird  in Usernames.txt angeh�ngt
			fprintf(datei_users_ptr, ";");												//Semikolon wird angeh�ngt
			printf("Neuer Nutzer wurde erfolgreich angelegt.\n");
		}


	fclose(datei_users_ptr);
	return(entered_user_ptr);
}
