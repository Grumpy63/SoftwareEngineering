/*
 * highscorce.c
 *
 *  Created on: 09.06.2021
 *      Author: Luca
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"

#define SEMIKOLON 59													//Makro zur Übersichtlichkeit; 59 entspricht  Semikolon in ASCII






int user_ergebnis(int korrekte_voc, int user_vokabelzahl)
{
	float prozentual = 0.0;

	printf("\n\nAnzahl Korrekter Eingaben: %d von %d", korrekte_voc, user_vokabelzahl);

	prozentual =  (float) korrekte_voc / user_vokabelzahl * 100;

	printf(" dies entspricht %.2f Prozent\n", prozentual);

	return 0;
}





int highscore_list(struct username *aktueller_nutzer, int korrekte_voc, int user_vokabelzahl)
{

	FILE* datei_highscore_ptr = NULL;												//FILE* pointer zum öffnen der Highscorelist.txt Datei
	struct user_and_score *ptr_anfang_scorekette = NULL;							//Zeigt immer auf anfang der Scorekette (zur Übergabe an ausgabe_scoreliste funktion)
	struct user_and_score *ptr_cursor_scorekette = NULL;							//Hilfszeiger für Liste anlegen
	struct user_and_score *ptr_scorekette = NULL;									//Zeiger auf user_and_score zum eintragen der Werte

	datei_highscore_ptr = fopen("Highscorelist.txt", "r");							//Versuch Usernames.txt lesend zuöffnen
	if (datei_highscore_ptr == NULL)												//Wenn Versuch fehlschlägt
	{
		printf("Highscorelist.txt existiert noch nicht!\n");
		datei_highscore_ptr = fopen("Highscorelist.txt", "w+");						//Wenn Highscorelist.txt Datei also nicht existiert, erstelle sie

		//Verkettete Liste aus tatsächlichem Nutzer und unused Platzhaltern

		ptr_scorekette = malloc(sizeof(struct user_and_score));						//Erstellung des ersten Listenelements
		ptr_anfang_scorekette = ptr_scorekette;										//erstes Listenelement festhalten

		strcpy(ptr_scorekette->username, aktueller_nutzer->name);					//Aktueller Benutzer wird eingetragen
		ptr_scorekette->score = (korrekte_voc/user_vokabelzahl) * 100;				//sowie seine Punktzahl

		ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));				//Erstellung des zweiten Listenelements
		strcpy(ptr_cursor_scorekette->username, "-not yet used-");					//Aktueller Benutzer wird eingetragen
		ptr_cursor_scorekette->score = 0.0;

		ptr_scorekette->next = ptr_cursor_scorekette;
		ptr_scorekette = ptr_cursor_scorekette;

		ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));				//Erstellung des dritten Listenelements
		strcpy(ptr_cursor_scorekette->username, "-not yet used-");		     		//Aktueller Benutzer wird eingetragen
		ptr_cursor_scorekette->score = 0.0;

		ptr_scorekette->next = ptr_cursor_scorekette;
		ptr_scorekette = NULL;
		ptr_cursor_scorekette = NULL;


		ptr_cursor_scorekette = ptr_anfang_scorekette;								//ptr_anfang_scorekette wird durch aufruf der Ausgabe verändert!

		ausgabe_scoreliste(ptr_anfang_scorekette);

		//Nun nur noch in die Datei übertragen

		for(int i = 1; i<=3; i++)													//Drei User werden in die Highscorelist.txt geschrieben
		{
		fprintf(datei_highscore_ptr, ptr_cursor_scorekette->username);				//User wird in Highscoreliste geschrieben
		fprintf(datei_highscore_ptr, ";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_cursor_scorekette->score);					//Score wird geschrieben
		fprintf(datei_highscore_ptr, ";");
		ptr_cursor_scorekette = ptr_cursor_scorekette->next;							//Cursor wird auf nächsten User&Score geschoben
		}

		ptr_cursor_scorekette = NULL;

		fclose(datei_highscore_ptr);
		return 0;
	}
	else
	{
		printf("Highscorelist.txt wird ausgelesen\n");
		//Gesamte Liste als Verkettung abschreiben

		ptr_anfang_scorekette = malloc(sizeof(struct user_and_score));
		ptr_cursor_scorekette = ptr_anfang_scorekette;

		int c = 0;
		int u = 0;
		float f = 0.0;

		while(	(c = fgetc(datei_highscore_ptr) ) != EOF)										//Schleife für das auflisten aller Usernames, solange nicht end of file erreicht
		{
			if( c != SEMIKOLON )																//Wenn KEIN Semikolon kommt
			{
				ptr_cursor_scorekette->username[u] = c;											//Buchstabe einlesen
				u++;																			//Nächste Stelle im Namensarray belegen
			}
			else																				//Wenn Strichpunkt: Score einlesen
			{
				while((c = fscanf(datei_highscore_ptr,"%f", &f) ) != SEMIKOLON)
				{
					ptr_cursor_scorekette->score = f;
				}

			u = 0;
			ptr_scorekette = ptr_cursor_scorekette;
			ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));
			ptr_scorekette->next = ptr_cursor_scorekette;

			}
		}


		ausgabe_scoreliste(ptr_anfang_scorekette);


	return 0;
	}
}





int ausgabe_scoreliste(struct user_and_score *ptr_scoreliste)
{

	for(int i=1; i<=3; i++)
	{
	printf("\nAusgabe der Highscorelist:\n");
	printf("(%d) %s mit %0.2f Prozent\n", i, ptr_scoreliste->username, ptr_scoreliste->score);
	ptr_scoreliste = ptr_scoreliste->next;
	}

	return 0;
}
