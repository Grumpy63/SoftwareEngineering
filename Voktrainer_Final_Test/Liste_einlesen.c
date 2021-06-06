/*
 * Liste_einlesen.c
 *
 *  Created on: 03.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


FILE *datei_liste_ptr;

char dummy_zeichen = ' ';
char listenname[256];
char c;
bool Flagge_Kategorie = false;
bool Flagge_Kategorie_mind = false;
bool Flagge_Semikolon0 = false;
bool Flagge_Semikolon1 = false;
bool Flagge_Semikolon2 = false;
bool Flagge_Sprache1 = false;
bool Flagge_Sprache2 = false;
bool Flagge_erste_Vokabelpaar = false;
bool Flagge_erste_Vokabel_allokiert = false;
bool Flagge_Vokabel_allokiert = false;
int array_position_kategorie = 0;
int array_position_vokabel = 0;

struct kategorie *k_ptr = NULL;
struct kategorie *k_help_ptr = NULL;

//Pointer für die Alle Vokabeln Liste
struct kategorie *k_alle_erste_ptr = NULL;
struct kategorie *k_alle_ptr = NULL;
struct kategorie *k_alle_help_ptr = NULL;

struct vokabel *v_ptr = NULL;
struct vokabel *v_help_ptr = NULL;
struct vokabel *v_erste_ptr = NULL;

//Pointer für die Alle Vokabeln Liste
struct vokabel *v_alle_ptr = NULL;
struct vokabel *v_alle_help_ptr = NULL;
struct vokabel *v_alle_erste_ptr = NULL;



void liste_einlesen(){
	setbuf(stdout, NULL);
	printf("Bitte den Namen der Vokabelliste eingeben, die eingelesen werden soll. \n");
	scanf("%c", listenname);

	datei_liste_ptr = fopen(listenname, "r");
	if(datei_liste_ptr == NULL)
	{
		printf("Die Datei konnte leider nicht geöffnet werden.\n");
	}
	else{
		  k_alle_erste_ptr = malloc(sizeof(struct kategorie));													//Speicher für erste Kategorie wird allokiert und dem Pointer kategorie_erste_ptr zugewiesen
		  k_alle_ptr = k_alle_erste_ptr;
		  k_ptr = k_alle_erste_ptr;
		  v_alle_erste_ptr = k_alle_erste_ptr->erste_vokabel;
		  v_alle_ptr = k_alle_erste_ptr->erste_vokabel;

		  if(k_alle_erste_ptr == NULL)																			//Wenn Pointer kategorie_erste_ptr gleich NULL konnte kein Speicher allokiert werden
		  {
			  printf("Kein virtueller RAM zum Allokieren einer weiteren Kategorie mehr verfügbar.\n");
			  exit(1);
		  }
		  strcpy(k_alle_erste_ptr->kategorie_name ,"Alle Vokabeln");													//Der Name der ersten Liste (mit allen Voikabeln) wird auf Alle Vokablen festgelegt
		  while((c = fgetc(datei_liste_ptr)) != EOF)																//Zeichenweises Auslesen der Datei
		  {
			  if(c == '!')
			  {
				  Flagge_Kategorie_mind = true;
			  }
		  }
		  while((c = fgetc(datei_liste_ptr)) != EOF)																//Zeichenweises Auslesen der Datei
	      {
	    	  //Es ist mindestens eine Kategorie vorhanden
	    	  if(Flagge_Kategorie_mind == true)
	    	  {
	    		  //Beginn einer Kategorie
				  if(c == '!')																							//Wenn ausgelesenes Zeichen ein !, dann
				  {
					  Flagge_Kategorie = true;																			//Flagge_Kategorie speichert das Auftreten einer neuen Kategorie
					  k_help_ptr = malloc(sizeof(struct kategorie));											//Speicherplatz für eine neue Kategorie wird allokiert
					  k_ptr->next_kategorie = k_help_ptr;																		//Der Next pointer der vorherigen Kategorie wird auf den Speicher der neu allkoierten Kategorie gesetzt
					  k_ptr = k_ptr->next_kategorie;
					  free(k_help_ptr);
					  continue;																							//Der nächste Durchlauf der while-Schleife beginnt
				  }
				  //Einlesen einer Kategorie
				  if(Flagge_Kategorie == true && c != ';')
				  {
					  k_ptr->kategorie_name[array_position_kategorie] = c;
					  array_position_kategorie++;
					  continue;
				  }
				  //Ende einer Kategorie
				  if(Flagge_Kategorie == true && c == ';')																//Wenn eine Kategorie detektiert wurde und das eingelesene Zeichen ein Semikolon ist, dann
				  {
					  Flagge_Kategorie = false;																			//Wird die Flagge_Kategorie zurükgesetzt
					  Flagge_Semikolon0 = true;																			//Das Ende der Kategorie wurde detektiert und dieser Zustand wird in der Flagge_Semikolon0 gespeichert
					  array_position_kategorie = 0;																				//Die array_position zurückgesetzt für eine mögliche nächste Kategorie
					  continue;																							//Der nächste Durchlauf der while-schleife getriggert
				  }
				  //Allokieren erster struct vokabel
				  if(Flagge_Semikolon0 == true && c != ';') 															//Wenn das Ende einer Kategorie erreicht ist und das eingelesene Zeichen kein Semikolon ist, dann
				  {

				  }
				  //Speichern erste Vokabel Sprache1

	    	  }
	    	  else{

	    	  }
	    		  //Auslesen bis ";" und Abspeichern in einem Char Kategorie_Name
	    		  //new struct Kategorie mit dem gespeicherten Char Kategorie_Name
	    		  //Auslesen bis ";" und speichern in Vokabel_temp
	    		  //new struct Vokabel und speichern in Sprache1
	    		  //Auslesen bis ";" und speichern in Vokabel_temp
	    		  //Speichern in Sprache2
	      }
	}
}




