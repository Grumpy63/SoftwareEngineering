/*
 * usernames_test.c
 *
 *  Created on: 31.05.2021
 *      Author: Luca
 */

#include "test_header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEMIKOLON 59

struct username *usernames(){


FILE *datei_users_ptr;												//FILE pointer zum �ffnen der Usernames.txt Datei

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
			datei_users_ptr = fopen("Usernames.txt", "w+");						//Wenn Usernames.txt Datei also nicht existiert, erstelle sie
			printf("Usernames.txt wurde erstellt.\n");
			printf("Noch keine Nutzer bekannt! \nBitte einen neuen Nutzernamen eingeben: ");

			entered_user_ptr = malloc(sizeof(struct username));					//Setze entered_user_ptr auf neu erstelltes Element (ersten User)
			scanf("%s", entered_user_ptr->name);								//Es k�nnen noch keine Leerzeichen eingescannt werden
			fprintf(datei_users_ptr, entered_user_ptr->name);					//Eingegebenen Nutzernamen in die Datei Usernames.txt schreiben
			fprintf(datei_users_ptr, ";");										//Anh�ngen des Semikolons in Datei Usernames.txt f�r Konformit�t
			printf("Nutzer erfolgreich angelegt!\n");
			printf("Ende der Erstellung von Usertext.txt\n");
			return(entered_user_ptr);															//return pointer auf aktuellen User
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
										//BEHEBEN? Neuer Nutzer wird auch dann nach einem Semikolon angelegt, wenn kein Name mehr folgt
										user_help_ptr = user_ptr;						//Hilfspointer zeigt auf letzten User
										user_ptr = malloc(sizeof(struct username));		//Neuer User wird angelegt (IMMER nach Semikolon, auch wenn keiner Folgt f�hrt zu zus�tzlichem Zeilenumbruch)
										user_help_ptr->next_user = user_ptr;			//Neuer User wird an letzten User angeh�ngt
										u = 0;											//R�cksetzen der Variable zum wieder-verwenden in der oberen if-Bedingung
									}
								}

						free(user_ptr);												//L�schen des �berfl�ssigen letzten User-Elements
						user_help_ptr->next_user = NULL;							//Next Pointer des jetzt letzten Elements (nachdem leerer User gel�scht wurde) wird geerdet
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


		printf("Bitte einen Nutzernamen auswaehlen, oder einen neuen Namen eingeben: ");			//Aufforderung einen Namen festzulegen

		entered_user_ptr = malloc(sizeof(struct username));											//Festlegen des Pointers f�r den aktuell gew�hlten User

		scanf("%s", entered_user_ptr->name);														//Einlesen des gew�hlten Users


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



		if(t == 0)																		//Wenn eingegebener Nutzer noch nicht existiert, erweitere die verkettete Liste und�berschreibe die existierende Usernames.txt
		{
			fprintf(datei_users_ptr, entered_user_ptr->name);							//Angelegter Name wird  in Usernames.txt angeh�ngt
			fprintf(datei_users_ptr, ";");												//Semikolon wird angeh�ngt
			printf("Neuer Nutzer wurde erfolgreich angelegt.\n");
		}


		return(entered_user_ptr);
}



