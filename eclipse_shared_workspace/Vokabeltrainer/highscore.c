/*
 * Created on: 09.06.2021
 * Author: Luca Elsesser
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"

#define SEMIKOLON 59													//Makro zur �bersichtlichkeit; 59 entspricht  Semikolon in ASCII




int user_ergebnis(int korrekte_voc, int user_vokabelzahl)								//Funktion zur Ausgabe des Nutzerergebnisses der aktuellen Sitzung
{
	float prozentual = 0.0;																//Hier wird der Prozentuale Wert der richtig beantworteten Vocs gespeichert

	printf("Anzahl korrekter Eingaben: %d von %d", korrekte_voc, user_vokabelzahl);	//Ausgabe der Richtigen Antworten verglichen mit abgefragten Vocs

	prozentual =  (float) korrekte_voc / user_vokabelzahl * 100;						//Hier wird der Prozentuale Wert der richtig beantworteten Vocs berechnet

	printf(" dies entspricht %.2f Prozent\n", prozentual);								//Ausgabe des Prozentualen Werts der richtig genannten Vocs

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
		if(ptr_scorekette==NULL)													//�berpr�fung ab Erstellung erfolgreich
		{
			printf("FATAL ERROR");
			return 0;
		}

		ptr_anfang_scorekette = ptr_scorekette;										//erstes Listenelement festhalten

		strcpy(ptr_scorekette->username, aktueller_nutzer->name);					//Aktueller Benutzer wird eingetragen
		ptr_scorekette->score = prozentual;											//sowie seine Punktzahl

		ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));				//Erstellung des zweiten Listenelements
		strcpy(ptr_cursor_scorekette->username, "-unbelegt-");						//Filler Benutzer wird eingetragen
		ptr_cursor_scorekette->score = 0.0;											//mit niedrigstem m�glichen Wert (wird durch n�chsten Nutzer �berschrieben)

		ptr_scorekette->next = ptr_cursor_scorekette;								//Verkn�pfung des ersten mit dem zweiten Element
		ptr_scorekette = ptr_cursor_scorekette;										//ptr_scorekette zeigt nun auf 2. Element

		ptr_cursor_scorekette = malloc(sizeof(struct user_and_score));				//Erstellung des dritten Listenelements
		strcpy(ptr_cursor_scorekette->username, "-unbelegt-");		     			//3. Filler Benutzer wird eingetragen
		ptr_cursor_scorekette->score = 0.0;											//mit niedrigstem m�glichen Wert (wird durch n�chsten Nutzer �berschrieben)

		ptr_scorekette->next = ptr_cursor_scorekette;								//Verkn�pfung des zweiten mit dem dritten Element

		ptr_scorekette = NULL;														//Erdung der Pointer
		ptr_cursor_scorekette = NULL;												//Erdung der Pointer


		ptr_cursor_scorekette = ptr_anfang_scorekette;

		ausgabe_scoreliste(ptr_anfang_scorekette);									//Ausgabe der neuen Liste

		//Nun noch in die Datei �bertragen

		for(int i = 1; i<=3; i++)														//Drei User werden in die Highscorelist.txt geschrieben
		{
		fprintf(datei_highscore_ptr, ptr_cursor_scorekette->username);					//User wird in Highscoreliste geschrieben
		fprintf(datei_highscore_ptr, ";");												//Semikolon f�r Konformit�t
		fprintf(datei_highscore_ptr, "%0.5f", ptr_cursor_scorekette->score);			//Score wird geschrieben
		fprintf(datei_highscore_ptr, ";");												//Semikolon f�r Konformit�t
		ptr_cursor_scorekette = ptr_cursor_scorekette->next;							//Cursor wird auf n�chsten struct User&Score geschoben
		}

		ptr_cursor_scorekette = NULL;													//Erdung der Pointer

		fclose(datei_highscore_ptr);													//Schlie�en des Streams um �nderungen in Highscorelist.txt zu speichern
		return 0;
	}
	else																			//Wenn Highscorelist.txt schon existiert
	{

		//Gesamte Liste als Verkettung abschreiben

		ptr_list1 = malloc(sizeof(struct user_and_score));							//Hilfspointer: f�r jeden Platz auf der Highscorelist eigenen Pointer
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

		ptr_aktuell_scorekette = malloc(sizeof(struct user_and_score));						//Speicher f�r aktuellen User wird allokiert
		strcpy(ptr_aktuell_scorekette->username, aktueller_nutzer->name);					//Aktueller Benutzer wird eingetragen
		ptr_aktuell_scorekette->score = prozentual;											//sowie seine Punktzahl


		ptr_cursor_scorekette = ptr_anfang_scorekette->next;								//Pointer auf zweites Listenelement
		ptr_help_scorekette = ptr_cursor_scorekette->next;									//Pointer auf drittes und letztes Listenelement


		if((ptr_aktuell_scorekette->score)>=(ptr_anfang_scorekette->score))					//Einschub an erster Stelle n�tig?
		{
			ptr_aktuell_scorekette->next = ptr_anfang_scorekette;							//Aktueller User Listenelement ist nun an erster Stelle
			ptr_anfang_scorekette = ptr_aktuell_scorekette;									//Liste beginnt bei dem neuen User Element
			free(ptr_help_scorekette);														//L�schen des letzten Platzes
			ptr_cursor_scorekette->next = NULL;												//Nun letztes Element hat keinen Nachfolger
		}
		else if((ptr_aktuell_scorekette->score)>=(ptr_cursor_scorekette->score))			//Einschub an zweiter Stelle n�tig?
		{
			ptr_aktuell_scorekette->next = ptr_cursor_scorekette;							//Aktueller User Listenelement ist nun an zweiter Stelle
			ptr_anfang_scorekette->next = ptr_aktuell_scorekette;							//Liste beginnt bei dem neuen User Element
			free(ptr_help_scorekette);														//L�schen des letzten Platzes
			ptr_cursor_scorekette->next = NULL;												//Nun letztes Element hat keinen Nachfolger
		}
		else if((ptr_aktuell_scorekette->score)>=(ptr_help_scorekette->score))				//Einschub an dritter Stelle n�tig?
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

		ptr_cursor_scorekette = NULL;														//Pointer werden geerdet
		ptr_scorekette = NULL;																//Pointer werden geerdet

		ausgabe_scoreliste(ptr_anfang_scorekette);											//Ausgabe der neuen Liste


		//NEUE Verkettete Liste in Highscorefile �berschreiben

		fclose(datei_highscore_ptr);													//ausschlie�lich lesender Zugriff wird beendet


		datei_highscore_ptr = fopen("Highscorelist.txt", "w+");							//Highscorelist wird �berschreibend ge�ffnet

		fprintf(datei_highscore_ptr, ptr_list1->username);
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_list1->score);						//Score vom 1. Platz wird geschrieben
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, ptr_list2->username);
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_list2->score);						//Score vom 2. Platzwird geschrieben
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, ptr_list3->username);
		fprintf(datei_highscore_ptr,";");
		fprintf(datei_highscore_ptr, "%0.5f", ptr_list3->score);						//Score vom 3. Platz wird geschrieben
		fprintf(datei_highscore_ptr,";");

		fclose(datei_highscore_ptr);													//Schlie�en des Streams um �nderungen in Highscorelist.txt zu speichern
		return 0;
	}
}





int ausgabe_scoreliste(struct user_and_score *ptr_scoreliste)						//Gibt verkettete Liste von user&score auf dem Bildschirm aus
{

	struct user_and_score *ptr_help = NULL;											//Help Pointer innerhalb der Funktion,
	ptr_help = ptr_scoreliste;														//damit �bergebener Zeiger nicht ver�ndert wird

	printf("\nDie aktuelle TOP 3 der Highscoreliste:\n");

	for(int i=1; i<=3; i++)															//Schleife �ber die drei Listenelemente
	{
	printf("(%d) %s mit %0.2f Prozent\n", i, ptr_help->username, ptr_help->score);	//Ausgabe der Platzierungen nacheinander
	ptr_help = ptr_help->next;														//weitersetzen des Pointers als Cursor
	}

	return 0;
}
