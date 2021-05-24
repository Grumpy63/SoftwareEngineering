/*
 * usernames.c
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */


#include <stdio.h>
#include <stdlib.h>
#include "voc_functions.h"


int username_list()
{
	FILE *datei_users_ptr;										//FILE pointer zum öffnen der Usernames.txt Datei
	int c = 0;													//Char Platzhalter zum auslesen der Datei

	struct username{											//Struct um Nutzernamen zu managen; um zu überprüfen ob neuer Nutzername bereits besteht
		char name[255];											//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;								//Pointer zeigt auf nächsten Nutzer in der verketteten Liste
	};

	struct username *user_ptr = NULL;							//Pointer auf struct username um unbegrenzte Useranzahl zu realisieren


	datei_users_ptr = fopen("Usernames.txt", "r+");				//Versuch Usernames.txt lesend und schreibend zuöffnen
		if (datei_users_ptr == NULL)							//Wenn Versuch fehlschlägt
		{
			datei_users_ptr = fopen("Usernames.txt", "w+");		//Wenn Usernames.txt Datei also nicht existiert, erstelle sie
			printf("Usernames.txt wurde erstellt.\n");
			printf("Noch keine Nutzer bekannt! \nBitte einen neuen Nutzernamen eingeben: ");

			user_ptr = malloc(sizeof(struct username));			//Setze user_ptr auf neu erstelltes Element (ersten User)
			scanf("%s", user_ptr->name);						//Es können noch keine Leerzeichen eingescannt werden
			strcat(user_ptr->name, ";");						//Semikolon an neuen Nutzernamen in Datei anhängen
			fprintf(datei_users_ptr, user_ptr->name);
			printf("Nutzer eingelesen");
		}
		else													//Wenn Datei existiert (und entsprechend schon ein User bekannt ist); alle bekannten User auflisten
		{
			printf("Bitte einen der folgenden Nutzer auswaehlen, oder einen neuen Nutzernamen anlegen: \n");



				while(	(c = fgetc(datei_users_ptr) ) != EOF)		//Schleife für das auflisten aller Usernames

					{
						if( c == 59 )								//Wenn Strichpunkt kommt
						{
							printf("\n");							//Zeilenumbruch (für nächsten Nutzernamen)
						}
						else
							putchar(c);								//Normalfall: ein Buchstabe nach dem anderen
						}


		}




		printf("Ende\n");
		int a = 0;
		scanf("%d", &a);




	return 0;
}
