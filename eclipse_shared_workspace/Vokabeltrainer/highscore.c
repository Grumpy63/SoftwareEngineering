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
	struct user_and_score *ptr_aktuell_scorekette = NULL;							//Zeiger auf aktuellen user mit score
	struct user_and_score *ptr_help_scorekette = NULL;								//Hilfszeiger auf user mit score

	struct user_and_score *ptr_list1 = NULL;									//Zeiger auf user_and_score zum eintragen der Werte
	struct user_and_score *ptr_list2 = NULL;									//Zeiger auf user_and_score zum eintragen der Werte
	struct user_and_score *ptr_list3 = NULL;									//Zeiger auf user_and_score zum eintragen der Werte

	float prozentual = 0.0;														//Prozentual richtiges vom aktuellen Nutzer
	prozentual = (float) korrekte_voc / user_vokabelzahl * 100;					//Zum weiteren verwenden

	datei_highscore_ptr = fopen("Highscorelist.txt", "r");							//Versuch Usernames.txt lesend zuöffnen
	if (datei_highscore_ptr == NULL)												//Wenn Versuch fehlschlägt
	{
		printf("Highscorelist.txt existiert noch nicht!\n");
		datei_highscore_ptr = fopen("Highscorelist.txt", "w+");						//Wenn Highscorelist.txt Datei also nicht existiert, erstelle sie

		//Verkettete Liste aus tatsächlichem Nutzer und unused Platzhaltern

		ptr_scorekette = malloc(sizeof(struct user_and_score));						//Erstellung des ersten Listenelements
		if(ptr_scorekette==NULL)
		{
			printf("FATAL ERROR");
			return 0;
		}

		ptr_anfang_scorekette = ptr_scorekette;										//erstes Listenelement festhalten

		strcpy(ptr_scorekette->username, aktueller_nutzer->name);					//Aktueller Benutzer wird eingetragen
		ptr_scorekette->score = prozentual;											//sowie seine Punktzahl

		ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));				//Erstellung des zweiten Listenelements
		strcpy(ptr_cursor_scorekette->username, "-not yet used-");					//Aktueller Benutzer wird eingetragen
		ptr_cursor_scorekette->score = 0.0;

		ptr_scorekette->next = ptr_cursor_scorekette;								//Verknüpfung des ersten mit dem zweiten Element
		ptr_scorekette = ptr_cursor_scorekette;										//ptr_scorekette zeigt nun auf 2. Element

		ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));				//Erstellung des dritten Listenelements
		strcpy(ptr_cursor_scorekette->username, "-not yet used-");		     		//3. Benutzer wird eingetragen
		ptr_cursor_scorekette->score = 0.0;

		ptr_scorekette->next = ptr_cursor_scorekette;								//Verknüpfung des zweiten mit dem dritten Element

		ptr_scorekette = NULL;
		ptr_cursor_scorekette = NULL;


		ptr_cursor_scorekette = ptr_anfang_scorekette;								//ptr_anfang_scorekette wird durch Aufruf der Ausgabe verändert!

		ausgabe_scoreliste(ptr_anfang_scorekette);

		//Nun nur noch in die Datei übertragen

		for(int i = 1; i<=3; i++)														//Drei User werden in die Highscorelist.txt geschrieben
		{
		fprintf(datei_highscore_ptr, ptr_cursor_scorekette->username);					//User wird in Highscoreliste geschrieben
		fprintf(datei_highscore_ptr, ";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_cursor_scorekette->score);			//Score wird geschrieben
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


		/*
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
*/



		ptr_list1 = malloc(sizeof(struct user_and_score));
		ptr_list2 = malloc(sizeof(struct user_and_score));
		ptr_list3 = malloc(sizeof(struct user_and_score));
		char name1[256];
		char name2[256];
		char name3[256];

		//Hier weiterarbeiten
		fscanf(datei_highscore_ptr,"%s;%f;%s;%f;%s;%f;",
			   name1, ptr_list1->score, name2, ptr_list2->score, name3, ptr_list3->score);

		ptr_anfang_scorekette = ptr_list1;
		ptr_anfang_scorekette->next = ptr_list2;
		ptr_list2->next = ptr_list3;




		//Aktueller User wird mit bestehenden Verglichen

		ptr_aktuell_scorekette = malloc(sizeof(struct user_and_score));
		strcpy(ptr_aktuell_scorekette->username, aktueller_nutzer->name);					//Aktueller Benutzer wird eingetragen
		ptr_aktuell_scorekette->score = prozentual;											//sowie seine Punktzahl


		ptr_cursor_scorekette = ptr_anfang_scorekette->next;								//Pointer auf zweites Listenelement
		ptr_help_scorekette = ptr_cursor_scorekette->next;									//Pointer auf drittes und letztes Listenelement


		if((ptr_aktuell_scorekette->score)>=(ptr_anfang_scorekette->score))					//Einschub an erster Stelle
		{
			ptr_aktuell_scorekette->next = ptr_anfang_scorekette;							//Aktueller User Listenelement ist nun an erster Stelle
			ptr_anfang_scorekette = ptr_aktuell_scorekette;									//Liste beginnt bei dem neuen User Element
			free(ptr_help_scorekette);														//Löschen des letzten Platzes
			ptr_cursor_scorekette->next = NULL;												//Nun letztes Element hat keinen Nachfolger
		}
		else if((ptr_aktuell_scorekette->score)>=(ptr_cursor_scorekette->score))			//Einschub an zweiter Stelle
		{
			ptr_aktuell_scorekette->next = ptr_cursor_scorekette;							//Aktueller User Listenelement ist nun an zweiter Stelle
			ptr_anfang_scorekette->next = ptr_aktuell_scorekette;							//Liste beginnt bei dem neuen User Element
			free(ptr_help_scorekette);														//Löschen des letzten Platzes
			ptr_cursor_scorekette->next = NULL;												//Nun letztes Element hat keinen Nachfolger
		}
		else if((ptr_aktuell_scorekette->score)>=(ptr_help_scorekette->score))				//Einschub an dritter Stelle
		{
			ptr_cursor_scorekette->next = ptr_aktuell_scorekette;							//Anhängen an zweites Listenelement
			free(ptr_help_scorekette);														//Letztes Element wird gelöscht, da nur die besten 3 bestehen bleiben
		}
		else
		{
			free(ptr_aktuell_scorekette);													//Userergebnis wird gelöscht, da es nicht für die top 3 gereicht hat
		}


		/*
		for(int i=1; i<=3; i++)																//Vergleich mit allen 3 bestehenden Nutzern
		{
			ptr_scorekette = ptr_cursor_scorekette;

			if((ptr_aktuell_scorekette->score)>=(ptr_cursor_scorekette))							//Vergleich Score des aktuellen Nutzers
			{
				ptr_aktuell_scorekette->next = ptr_cursor_scorekette;							//Vorranhängen des aktuellen users an listenelement
				ptr_help_scorekette = ptr_aktuell_scorekette;								//help pointer auf aktuellen user

			}

			ptr_cursor_scorekette = ptr_cursor_scorekette->next;
		}

		*/


		ptr_cursor_scorekette = NULL;
		ptr_scorekette = NULL;



		ausgabe_scoreliste(ptr_anfang_scorekette);


	return 0;
	}
}





int ausgabe_scoreliste(struct user_and_score *ptr_scoreliste)
{

	printf("\nAusgabe der Highscorelist:\n");

	for(int i=1; i<=3; i++)
	{
	printf("(%d) %s mit %0.2f Prozent\n", i, ptr_scoreliste->username, ptr_scoreliste->score);
	ptr_scoreliste = ptr_scoreliste->next;
	}

	return 0;
}
