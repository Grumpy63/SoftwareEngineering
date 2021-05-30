#include <stdio.h>
#include <stdlib.h>


int main()
{

	FILE *datei_users_ptr;												//FILE pointer zum öffnen der Usernames.txt Datei
	int c = 0;															//Char Platzhalter zum auslesen der Datei
	int u = 0;															//Variable benutzt in Erstellung User verkettete Liste

	struct username{													//Struct um Nutzernamen zu managen; um zu überprüfen ob neuer Nutzername bereits besteht
		char name[256];													//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;										//Pointer zeigt auf nächsten Nutzer in der verketteten Liste
	};

	struct username *user_ptr = NULL;									//Pointer auf struct username um unbegrenzte Useranzahl zu realisieren
	struct username *user_help_ptr = NULL;								//Pointer zum anlegen der Liste (festhalten des letzen users)
	struct username *user_first_ptr = NULL;								//Pointer auf ersten User in der Liste

	struct username *entered_user_ptr = NULL;							//Pointer auf aktuell gewählten User


	datei_users_ptr = fopen("Usernames.txt", "r+");						//Versuch Usernames.txt lesend und schreibend zuöffnen
		if (datei_users_ptr == NULL)									//Wenn Versuch fehlschlägt
		{
			datei_users_ptr = fopen("Usernames.txt", "w+");				//Wenn Usernames.txt Datei also nicht existiert, erstelle sie
			printf("Usernames.txt wurde erstellt.\n");
			printf("Noch keine Nutzer bekannt! \nBitte einen neuen Nutzernamen eingeben: ");

			user_ptr = malloc(sizeof(struct username));					//Setze user_ptr auf neu erstelltes Element (ersten User)
			scanf("%s", user_ptr->name);								//Es können noch keine Leerzeichen eingescannt werden
			strcat(user_ptr->name, ";");								//Semikolon an neuen Nutzernamen in Datei anhängen
			fprintf(datei_users_ptr, user_ptr->name);
			printf("Nutzer erfolgreich angelegt!\n");
			printf("Ende\n");
			int a = 0;
			scanf("%d", &a);
			return (1);
		}
		else															//Wenn Datei existiert (und entsprechend schon ein User bekannt ist); alle bekannten User auflisten
		{
			printf("Bitte einen der folgenden Nutzer auswaehlen, oder einen neuen Nutzernamen anlegen:\n\n");

			//TEST: Nutzer als verkettete Liste anlegen



			user_ptr = malloc(sizeof(struct username));						//erstmaliges anlegen eines user-platzes auf der liste (mindestens ein user steht drauf)
			user_first_ptr = user_ptr;

			while(	(c = fgetc(datei_users_ptr) ) != EOF)					//Schleife für das auflisten aller Usernames, solange nicht end of file erreicht
					{


						if( c != 59 )										//Wenn KEIN Strichpunkt kommt
						{
							user_ptr->name[u] = c;							//Buchstabe einlesen
							u++;
						}
						else												//Wenn strichpunkt: nächsten Nutzer anlegen
						{
							user_help_ptr = user_ptr;						//Hilfspointer zeigt auf letzten User
							user_ptr = malloc(sizeof(struct username));		//Neuer User wird angelegt
							user_help_ptr->next_user = user_ptr;			//Neuer User wird an letzten User angehängt
							u = 0;											//Rücksetzen der Variable zum wieder-verwenden in der oberen if-Bedingung
						}
					}

				//Alle User als Kette angelegt abgeschlossen
				//Es folgt Ausgabe aller User


			user_ptr = user_first_ptr;

			while (user_ptr != NULL)
			{
			printf("%s\n", user_ptr->name);
			user_ptr = user_ptr->next_user;
			}



		}


		printf("Bitte einen Nutzernamen auswaehlen, oder einen neuen Namen eingeben: ");			//Aufforderung einen Namen festzulegen

		entered_user_ptr = malloc(sizeof(struct username));											//Festlegen des Pointers für den aktuell gewählten User

		scanf("%s", entered_user_ptr->name);														//Einlesen des gewählten Users


		//Es erfolgt die Überprüfung auf die Existenz (Doppelnennung) des Namens

		//1. Schreiben der existierenden Namen als verkettete Liste






		printf("Ende\n");
		int a = 0;
		scanf("%d", &a);




	return 0;
}
