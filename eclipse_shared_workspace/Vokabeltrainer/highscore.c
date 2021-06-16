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

#define SEMIKOLON 59													//Makro zur �bersichtlichkeit; 59 entspricht  Semikolon in ASCII






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

	FILE* datei_highscore_ptr = NULL;												//FILE* pointer zum �ffnen der Highscorelist.txt Datei
	struct user_and_score *ptr_anfang_scorekette = NULL;							//Zeigt immer auf anfang der Scorekette (zur �bergabe an ausgabe_scoreliste funktion)
	struct user_and_score *ptr_cursor_scorekette = NULL;							//Hilfszeiger f�r Liste anlegen
	struct user_and_score *ptr_scorekette = NULL;									//Zeiger auf user_and_score zum eintragen der Werte
	struct user_and_score *ptr_aktuell_scorekette = NULL;							//Zeiger auf aktuellen user mit score
	struct user_and_score *ptr_help_scorekette = NULL;								//Hilfszeiger auf user mit score

	struct user_and_score *ptr_list1 = NULL;									//Zeiger auf user_and_score zum eintragen der Werte
	struct user_and_score *ptr_list2 = NULL;									//Zeiger auf user_and_score zum eintragen der Werte
	struct user_and_score *ptr_list3 = NULL;									//Zeiger auf user_and_score zum eintragen der Werte

	float prozentual = 0.0;														//Prozentual richtiges vom aktuellen Nutzer
	prozentual = (float) korrekte_voc / user_vokabelzahl * 100;					//Zum weiteren verwenden

	datei_highscore_ptr = fopen("Highscorelist.txt", "r");							//Versuch Usernames.txt lesend zu�ffnen
	if (datei_highscore_ptr == NULL)												//Wenn Versuch fehlschl�gt
	{
		printf("Highscorelist.txt existiert noch nicht!\n");
		datei_highscore_ptr = fopen("Highscorelist.txt", "w+");						//Wenn Highscorelist.txt Datei also nicht existiert, erstelle sie

		//Verkettete Liste aus tats�chlichem Nutzer und unused Platzhaltern

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

		ptr_scorekette->next = ptr_cursor_scorekette;								//Verkn�pfung des ersten mit dem zweiten Element
		ptr_scorekette = ptr_cursor_scorekette;										//ptr_scorekette zeigt nun auf 2. Element

		ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));				//Erstellung des dritten Listenelements
		strcpy(ptr_cursor_scorekette->username, "-not yet used-");		     		//3. Benutzer wird eingetragen
		ptr_cursor_scorekette->score = 0.0;

		ptr_scorekette->next = ptr_cursor_scorekette;								//Verkn�pfung des zweiten mit dem dritten Element

		ptr_scorekette = NULL;
		ptr_cursor_scorekette = NULL;


		ptr_cursor_scorekette = ptr_anfang_scorekette;								//ptr_anfang_scorekette wird durch Aufruf der Ausgabe ver�ndert!

		ausgabe_scoreliste(ptr_anfang_scorekette);

		//Nun nur noch in die Datei �bertragen

		for(int i = 1; i<=3; i++)														//Drei User werden in die Highscorelist.txt geschrieben
		{
		fprintf(datei_highscore_ptr, ptr_cursor_scorekette->username);					//User wird in Highscoreliste geschrieben
		fprintf(datei_highscore_ptr, ";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_cursor_scorekette->score);			//Score wird geschrieben
		fprintf(datei_highscore_ptr, ";");
		ptr_cursor_scorekette = ptr_cursor_scorekette->next;							//Cursor wird auf n�chsten User&Score geschoben
		}

		ptr_cursor_scorekette = NULL;

		fclose(datei_highscore_ptr);
		return 0;
	}
	else
	{
		printf("Highscorelist.txt wird ausgelesen\n");

		//Gesamte Liste als Verkettung abschreiben

		ptr_list1 = malloc(sizeof(struct user_and_score));							//Hilfspointer f�r jeden Platz auf der Highscorelist eigenen Pointer
		ptr_list2 = malloc(sizeof(struct user_and_score));
		ptr_list3 = malloc(sizeof(struct user_and_score));

		float fscore1 = 0;															//hilfsvariablen zum auslesen der Scores aus der Datei
		float fscore2 = 0;
		float fscore3 = 0;

		fscanf(datei_highscore_ptr,"%[^';'];%f;%[^';'];%f;%[^';'];%f;", ptr_list1->username, &fscore1, ptr_list2->username, &fscore2, ptr_list3->username, &fscore3);		//Standardisiertes Auslesen, strings werden gelesen bis Semikolon;

		ptr_list1->score = fscore1;													//�bertragen der Hilfsvars in korrekte structs
		ptr_list2->score = fscore2;
		ptr_list3->score = fscore3;

		ptr_anfang_scorekette = ptr_list1;											//Aneinander reihen der Pointer
		ptr_list1->next = ptr_list2;
		ptr_list2->next = ptr_list3;
		ptr_list3->next = NULL;



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
			free(ptr_help_scorekette);														//L�schen des letzten Platzes
			ptr_cursor_scorekette->next = NULL;												//Nun letztes Element hat keinen Nachfolger
		}
		else if((ptr_aktuell_scorekette->score)>=(ptr_cursor_scorekette->score))			//Einschub an zweiter Stelle
		{
			ptr_aktuell_scorekette->next = ptr_cursor_scorekette;							//Aktueller User Listenelement ist nun an zweiter Stelle
			ptr_anfang_scorekette->next = ptr_aktuell_scorekette;							//Liste beginnt bei dem neuen User Element
			free(ptr_help_scorekette);														//L�schen des letzten Platzes
			ptr_cursor_scorekette->next = NULL;												//Nun letztes Element hat keinen Nachfolger
		}
		else if((ptr_aktuell_scorekette->score)>=(ptr_help_scorekette->score))				//Einschub an dritter Stelle
		{
			ptr_cursor_scorekette->next = ptr_aktuell_scorekette;							//Anh�ngen an zweites Listenelement
			free(ptr_help_scorekette);														//Letztes Element wird gel�scht, da nur die besten 3 bestehen bleiben
		}
		else
		{
			free(ptr_aktuell_scorekette);													//Userergebnis wird gel�scht, da es nicht f�r die top 3 gereicht hat
		}




		ptr_list1 = ptr_anfang_scorekette;													//�bertragen der Adressen der jeweiligen Listenelemente
		ptr_list2 = ptr_list1->next;														//Zur einfachen weitergabe an File
		ptr_list3 = ptr_list2->next;														//bspw. ptr_list3 zeigt auf letzten Platz der highscoreliste

		ptr_cursor_scorekette = NULL;
		ptr_scorekette = NULL;

		ausgabe_scoreliste(ptr_anfang_scorekette);											//Ausgabe der neuen Liste, VORSICHT ptr_anfang_scorekette wird hierbei ver�ndert!


		//NEUE Verkettete Liste in Highscorefile �berschreiben

		fclose(datei_highscore_ptr);													//ausschlie�lich lesender Zugriff wird beendet


		datei_highscore_ptr = fopen("Highscorelist.txt", "w+");							//Highscorelist wird �berschreibend ge�ffnet

		fprintf(datei_highscore_ptr, ptr_list1->username);
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_list1->score);			//Score wird geschrieben
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, ptr_list2->username);
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_list2->score);			//Score wird geschrieben
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, ptr_list3->username);
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_list3->score);			//Score wird geschrieben
		fprintf(datei_highscore_ptr,";");

		fclose(datei_highscore_ptr);


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
