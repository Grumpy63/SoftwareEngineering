#include <stdio.h>
#include <stdlib.h>


int main()
{
	FILE *datei_users_ptr;										//FILE pointer zum �ffnen der Usernames.txt Datei
	int c = 0;													//Char Platzhalter zum auslesen der Datei

	struct username{											//Struct um Nutzernamen zu managen; um zu �berpr�fen ob neuer Nutzername bereits besteht
		char name[255];											//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;								//Pointer zeigt auf n�chsten Nutzer in der verketteten Liste
	};

	struct username *user_ptr = NULL;							//Pointer auf struct username um unbegrenzte Useranzahl zu realisieren


	datei_users_ptr = fopen("Usernames.txt", "r+");				//Versuch Usernames.txt lesend und schreibend zu�ffnen
		if (datei_users_ptr == NULL)							//Wenn Versuch fehlschl�gt
		{
			datei_users_ptr = fopen("Usernames.txt", "w+");		//Wenn Usernames.txt Datei also nicht existiert, erstelle sie
			printf("Usernames.txt wurde erstellt.\n");
			printf("Noch keine Nutzer bekannt! \nBitte einen neuen Nutzernamen eingeben: ");

			user_ptr = malloc(sizeof(struct username));			//Setze user_ptr auf neu erstelltes Element (ersten User)
			scanf("%s", user_ptr->name);						//Es k�nnen noch keine Leerzeichen eingescannt werden
			strcat(user_ptr->name, ";");						//Semikolon an neuen Nutzernamen in Datei anh�ngen
			fprintf(datei_users_ptr, user_ptr->name);
			printf("Nutzer eingelesen\n");
		}
		else													//Wenn Datei existiert (und entsprechend schon ein User bekannt ist)
		{
			printf("Bitte einen der folgenden Nutzer auswaehlen, oder einen neuen Nutzernamen anlegen: \n");





			while(	(c = fgetc(datei_users_ptr) ) != EOF)		//Schleife f�r das auflisten aller Usernames

				{
					user_ptr = malloc(sizeof(struct username));	//erstelle neuen Nutzerplatz in der Liste

					while( c != 59 )								//Wenn KEIN Strichpunkt kommt
					{
						putchar(user_ptr->name);				//Normalfall: ein Buchstabe nach dem anderen
					}
						printf("%s", user_ptr->name);
						printf("\n");							//Zeilenumbruch (f�r n�chsten Nutzernamen)


				}

		}

		printf("Ende\n");
		int a = 0;
		scanf("%d", &a);




	return 0;
}

