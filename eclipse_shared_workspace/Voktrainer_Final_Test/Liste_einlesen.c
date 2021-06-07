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

struct kategorie *liste_einlesen(){

	FILE *datei_liste_ptr;

	char dummy_zeichen = ' ';
	char listenname[256];
	char c;
	bool Flagge_Kategorie = false;
	bool Flagge_Kategorie_mind = false;
	bool Flagge_Semikolon0 = false;
	bool Flagge_Semikolon1 = false;
	bool Flagge_Semikolon2 = false;
	bool Flagge_Vokabelpaar = false;
	bool Flagge_Vokabel_allokiert = false;
	bool Flagge_erste_Vokabel_allokiert = false;
	bool Flagge_erste_Vokabel_alle_allokiert = false;
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




	setbuf(stdout, NULL);
	//printf("Bitte den Namen der Vokabelliste eingeben, die eingelesen werden soll. \n");
	//scanf("%c", &listenname);
	datei_liste_ptr = fopen("C:\\Users\\David\\Desktop\\SoftwareEngineering\\eclipse_shared_workspace\\Voktrainer_Final_Test\\Release\\Beispiel_Vokabelliste.txt", "r");
	if(datei_liste_ptr == NULL)
	{
		printf("Die Datei konnte leider nicht geöffnet werden.\n");
	}
	else{
		  k_alle_erste_ptr = malloc(sizeof(struct kategorie));													//Speicher für erste Kategorie wird allokiert und dem Pointer kategorie_erste_ptr zugewiesen
		  k_alle_erste_ptr->next_kategorie = NULL;
		  k_ptr = k_alle_erste_ptr;
		  v_alle_erste_ptr = k_alle_erste_ptr->erste_vokabel;
		  v_alle_ptr = k_alle_erste_ptr->erste_vokabel;

		  if(k_alle_erste_ptr == NULL)																			//Wenn Pointer kategorie_erste_ptr gleich NULL konnte kein Speicher allokiert werden
		  {
			  printf("Kein virtueller RAM zum Allokieren einer weiteren Kategorie mehr verfügbar.\n");
			  exit(1);
		  }
		  strcpy(k_alle_erste_ptr->kategorie_name ,"Alle Vokabeln");													//Der Name der ersten Liste (mit allen Voikabeln) wird auf Alle Vokablen festgelegt
		  while(c != EOF)																								//Zeichenweises Auslesen der Datei
		  {
			  c = fgetc(datei_liste_ptr);
			  if(c == '!')
			  {
				  Flagge_Kategorie_mind = true;
				  break;
			  }
		  }
		  while(c != EOF)																						//Zeichenweises Auslesen der Datei
	      {
	    	  c = fgetc(datei_liste_ptr);
	    	  if(c == '\r' || '\n')
	    	  {
	    		  continue;
	    	  }
	    	  //Einlesen für den Fall, dass es mindestens eine Kategorie im Dokument gibt
	    	  if(Flagge_Kategorie_mind == true)
	    	  {
	    		  //Beginn einer Kategorie
				  if(c == '!')																							//Wenn ausgelesenes Zeichen ein !, dann
				  {
					  Flagge_erste_Vokabel_allokiert = false;
					  Flagge_Kategorie = true;																			//Flagge_Kategorie speichert das Auftreten einer neuen Kategorie
					  Flagge_Vokabelpaar = false;
					  k_ptr->next_kategorie = malloc(sizeof(struct kategorie));											//Speicherplatz für eine neue Kategorie wird allokiert
					  k_ptr = k_ptr->next_kategorie;
					  continue;																							//Der nächste Durchlauf der while-Schleife beginnt
				  }
				  //Einlesen eines Kategorie-Namens
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
				  //Allokieren struct vokabel erstes Vokabelpaar einer Kategorie
				  if((Flagge_erste_Vokabel_allokiert == false && Flagge_Semikolon0 == true && c != ';') || (Flagge_Vokabelpaar == true && c != ';')) 															//Wenn das Ende einer Kategorie erreicht ist und das eingelesene Zeichen kein Semikolon ist, dann
				  {
					  k_ptr->erste_vokabel = malloc(sizeof(struct vokabel));
					  v_ptr = k_ptr->erste_vokabel;
					  if(Flagge_erste_Vokabel_alle_allokiert == false)
					  {
						  k_alle_ptr->erste_vokabel = malloc(sizeof(struct vokabel));
						  v_alle_ptr = k_alle_ptr->erste_vokabel;
						  Flagge_erste_Vokabel_alle_allokiert = true;
					  }
					  else
					  {
						  v_alle_ptr->next_vokabel = malloc(sizeof(struct vokabel));
						  v_alle_ptr = v_alle_ptr->next_vokabel;
					  }
					  k_ptr->anzahl_in_kategorie++;
					  k_alle_ptr->anzahl_in_kategorie++;
					  Flagge_Vokabel_allokiert = true;
					  Flagge_Semikolon0 = false;
					  Flagge_Vokabelpaar = false;
				  }
				  //Allokieren struct vokabel nachfolgenden Vokabelpaare einer Kategorie
				  if((Flagge_erste_Vokabel_allokiert == true && Flagge_Semikolon0 == true && c != ';') || (Flagge_Vokabelpaar == true && c != ';')) 															//Wenn das Ende einer Kategorie erreicht ist und das eingelesene Zeichen kein Semikolon ist, dann
				  {
					  v_ptr->next_vokabel = malloc(sizeof(struct vokabel));
					  v_ptr = v_ptr->next_vokabel;
					  v_alle_ptr->next_vokabel = malloc(sizeof(struct vokabel));
					  v_alle_ptr = v_alle_ptr->next_vokabel;
					  k_ptr->anzahl_in_kategorie++;
					  k_alle_ptr->anzahl_in_kategorie++;
					  Flagge_Vokabel_allokiert = true;
					  Flagge_Semikolon0 = false;
					  Flagge_Vokabelpaar = false;
					  Flagge_erste_Vokabel_allokiert = true;
				  }
				  //Ende der Sprache1
				  if(Flagge_Vokabel_allokiert == true && c == ';' && Flagge_Semikolon1 == false)
				  {
					  Flagge_Semikolon1 = true;
					  array_position_vokabel = 0;
					  continue;
				  }
				  //Einlesen von Sprache1
				  if(Flagge_Vokabel_allokiert == true && Flagge_Semikolon1 == false)
				  {
					  v_alle_ptr->vokabel_sprache1[array_position_vokabel] = c;
					  v_ptr->vokabel_sprache1[array_position_vokabel] =c;
					  array_position_vokabel++;
				  }
				  //Ende der Sprache2
				  if(Flagge_Semikolon1 == true && c == ';')
				  {
					  Flagge_Semikolon2 = true;
					  Flagge_Semikolon1 = false;
					  Flagge_Vokabel_allokiert = false;
					  Flagge_Vokabelpaar = true;
					  Flagge_erste_Vokabel_allokiert = true;
				  }
				  //Einlesen von Sprache2
				  if(Flagge_Vokabel_allokiert == true && Flagge_Semikolon1 == true)
				  {
					  v_alle_ptr->vokabel_sprache2[array_position_vokabel] = c;
					  v_ptr->vokabel_sprache2[array_position_vokabel] =c;
					  array_position_vokabel++;
				  }
	    	  	  }
	    	  //Einlesen für den Fall, dass es keine weitere Kategorie im Dokument gibt
	    	  else if(Flagge_Kategorie_mind == false)
	    	  {

	    		  //Allokieren struct vokabel
				  if((Flagge_Vokabelpaar == true && c != ';') || (Flagge_Vokabel_allokiert == false && c != ';')) 															//Wenn das Ende einer Kategorie erreicht ist und das eingelesene Zeichen kein Semikolon ist, dann
				  {
					  v_alle_help_ptr = malloc(sizeof(struct vokabel));
					  v_alle_ptr = v_alle_help_ptr;
					  free(v_alle_help_ptr);
					  k_alle_ptr->anzahl_in_kategorie++;
					  Flagge_Vokabel_allokiert = true;
					  Flagge_Vokabelpaar = false;
				  }
				  //Ende der Sprache1
				  if(Flagge_Vokabel_allokiert == true && c == ';')
				  {
					  Flagge_Semikolon1 = true;
					  array_position_vokabel = 0;
				  }
				  //Einlesen von Sprache1
				  if(Flagge_Vokabel_allokiert == true && Flagge_Semikolon1 == false)
				  {
					  v_alle_ptr->vokabel_sprache1[array_position_vokabel] = c;
					  v_ptr->vokabel_sprache1[array_position_vokabel] =c;
					  array_position_vokabel++;
				  }
				  //Ende der Sprache2
				  if(Flagge_Semikolon1 == true && c == ';')
				  {
					  Flagge_Semikolon2 = true;
					  Flagge_Semikolon1 = false;
					  Flagge_Vokabel_allokiert = false;
					  Flagge_Vokabelpaar = true;
					  v_alle_ptr = v_alle_ptr->next_vokabel;
					  v_ptr = v_ptr->next_vokabel;
				  }
				  //Einlesen von Sprache2
				  if(Flagge_Vokabel_allokiert == true && Flagge_Semikolon1 == true)
				  {
					  v_alle_ptr->vokabel_sprache2[array_position_vokabel] = c;
					  v_ptr->vokabel_sprache2[array_position_vokabel] =c;
					  array_position_vokabel++;
				  }
	    	  }
	      }
	}
	printf("%s \n", k_alle_erste_ptr->kategorie_name);
	printf("%s \n", k_alle_erste_ptr->next_kategorie->kategorie_name);
	printf("%s \n", k_alle_erste_ptr->next_kategorie->next_kategorie->kategorie_name);
	return(k_alle_erste_ptr);
}




