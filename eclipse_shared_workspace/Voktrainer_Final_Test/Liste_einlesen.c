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

	FILE *datei_vorlage_ptr;

	char c;

	bool Flagge_Neue_Kategorie = false;
	bool Flagge_Kategorie_mind = false;

	bool Flagge_Vokabelpaar_beschreibbar = false;
	bool Flagge_Kategorie_befuellbar = false;

	bool Flagge_Vokabel1_vorhanden = false;
	bool Flagge_Vokabel2_vorhanden = false;


	bool Flagge_aktuelles_Vokablpaar = false;

	bool Flagge_alleVokabel1_fertig = false;

	int array_position_kategorie = 0;
	int array_position_vokabel = 0;


	struct kategorie * alle_kategorien_ptr = NULL;
	struct vokabel * alle_vokablen_ende_ptr = NULL;

	struct kategorie * erste_kategorie_ptr = NULL;
	struct kategorie * ende_kategorie_ptr = NULL;
	struct vokabel * ende_vokabel_ptr = NULL;

	struct vokabel * vokabel_laeufer_ptr = NULL;
	struct kategorie * kategorie_laeufer_ptr = NULL;


	do{
	setbuf(stdout, NULL);
	//printf("Bitte den Namen der Vokabelliste eingeben, die eingelesen werden soll. \n");
	//scanf("%c", &listenname);
	datei_vorlage_ptr = fopen("C:/Users/David/Desktop/SoftwareEngineering/eclipse_shared_workspace/Voktrainer_Final_Test/Release/Beispiel_Vokabelliste.txt", "r");
	//datei_counter_ptr = datei_vorlage_ptr;
	if(datei_vorlage_ptr == NULL)
	{
		printf("Die Datei konnte leider nicht geöffnet werden.\n");
	}
	}while(datei_vorlage_ptr == NULL);
	
	
	
	while(c != EOF)															
	{
		c = fgetc(datei_vorlage_ptr);
		
		
		if(c == '!')
		{
		  Flagge_Kategorie_mind = true;
		  break;
		}
		
	}

	fseek(datei_vorlage_ptr, 0, SEEK_SET);

	if(Flagge_Kategorie_mind == true){
		
		  while(c != EOF)																
	      {
			  //Nächstes Zeichen auslesen
	    	  c = fgetc(datei_vorlage_ptr);
	    	  
	    	  //Zeilenbrüche raustrennen
	    	  if(c == '\r' || c =='\n' || c == EOF)
	    	  {
	    		  continue;
	    	  }
	    	  
			  //Beginn einer neuen Kategorie
			  if(c == '!')
			  {
				  Flagge_Neue_Kategorie = true;
				  Flagge_Kategorie_befuellbar = false;

				  if(erste_kategorie_ptr == NULL){
					  erste_kategorie_ptr = malloc(sizeof(struct kategorie));
					  ende_kategorie_ptr = erste_kategorie_ptr;
				  }
				  else{
					  ende_kategorie_ptr->next_kategorie = malloc(sizeof(struct kategorie));
					  ende_kategorie_ptr = ende_kategorie_ptr->next_kategorie;
				  }

				  continue;
			  }
				  
			  //Einlesen eines Kategorie-Namens
			  if(Flagge_Neue_Kategorie == true)
			  {

				  if(c == ';')
				  {
					  Flagge_Neue_Kategorie = false;
					  Flagge_Kategorie_befuellbar = true;
					  array_position_kategorie = 0;
					  continue;
				  }
				  ende_kategorie_ptr->kategorie_name[array_position_kategorie] = c;
				  array_position_kategorie++;
				  continue;
			  }

			  //Neues Vokabelpaar anzulegen
			  if(Flagge_Vokabelpaar_beschreibbar == false && Flagge_Kategorie_befuellbar == true){
				  Flagge_Vokabel1_vorhanden = false;
				  Flagge_Vokabel2_vorhanden = false;

				  if(ende_kategorie_ptr->erste_vokabel == NULL){
					  ende_kategorie_ptr->erste_vokabel = malloc(sizeof(struct vokabel));
					  ende_vokabel_ptr = ende_kategorie_ptr->erste_vokabel;
				  }
				  else{
					  ende_vokabel_ptr->next_vokabel = malloc(sizeof(struct vokabel));
					  ende_vokabel_ptr = ende_vokabel_ptr->next_vokabel;
				  }
				  ende_kategorie_ptr->anzahl_in_kategorie++;
				  Flagge_Vokabelpaar_beschreibbar = true;
			  }

			  //Vokabel eins vorhanden
			  if(Flagge_Vokabel1_vorhanden == false && Flagge_Vokabelpaar_beschreibbar == true){

				  if(c == ';')
				  {
					  Flagge_Vokabel1_vorhanden = true;
					  array_position_vokabel = 0;
					  continue;
				  }
				  ende_vokabel_ptr->vokabel_sprache1[array_position_vokabel] = c;
				  array_position_vokabel++;
				  continue;
			  }

			  //Vokabel zwei vorhanden
			  if(Flagge_Vokabel2_vorhanden == false && Flagge_Vokabelpaar_beschreibbar == true){

				  if(c == ';')
				  {
					  Flagge_Vokabel2_vorhanden = true;
					  Flagge_Vokabelpaar_beschreibbar = false;
					  array_position_vokabel = 0;
					  continue;
				  }
				  ende_vokabel_ptr->vokabel_sprache2[array_position_vokabel] = c;
				  array_position_vokabel++;
				  continue;
			  }

	    	}//While: dokument auslesen zuende

	    	 
	}//if: kategorien vorhanden zuende

	else{
		  while(c != EOF)
	      {
			  //Nächstes Zeichen auslesen
	    	  c = fgetc(datei_vorlage_ptr);

	    	  //Zeilenbrüche raustrennen
	    	  if(c == '\r' || c =='\n' || c == EOF)
	    	  {
	    		  continue;
	    	  }

	    	  //Einzige Erste Kategorie/Vokabel anlegen
	    	  if(alle_kategorien_ptr == NULL){
	    		  alle_kategorien_ptr = malloc(sizeof(struct kategorie));
	    		  strcpy(alle_kategorien_ptr->kategorie_name,"Alle Vokabeln");

	    		  alle_kategorien_ptr->erste_vokabel = malloc(sizeof(struct vokabel));
	    		  alle_vokablen_ende_ptr =  alle_kategorien_ptr->erste_vokabel;
	    		  Flagge_aktuelles_Vokablpaar = true;
	    	  }

	    	  //Vokabel 1
	    	  if(Flagge_alleVokabel1_fertig == false){

	    		  if(Flagge_aktuelles_Vokablpaar == false){
	    			  alle_vokablen_ende_ptr->next_vokabel = malloc(sizeof(struct vokabel));
	    			  alle_vokablen_ende_ptr = alle_vokablen_ende_ptr->next_vokabel;
	    			  Flagge_aktuelles_Vokablpaar = true;
	    		  }

	    		  if(c == ';'){
	    			  Flagge_alleVokabel1_fertig = true;
	    			  continue;
	    		  }
	    		  alle_vokablen_ende_ptr->vokabel_sprache1[array_position_vokabel] = c;
	    		  array_position_vokabel++;
	    	  }

	    	  //Vokabel 2
	    	  if(Flagge_alleVokabel1_fertig == true){

	    		  if(c == ';'){
	    			  Flagge_alleVokabel1_fertig = false;
	    			  Flagge_aktuelles_Vokablpaar = false;
	    			  alle_kategorien_ptr->anzahl_in_kategorie++;
	    			  continue;
	    		  }

	    		  alle_vokablen_ende_ptr->vokabel_sprache2[array_position_vokabel] = c;
	    		  array_position_vokabel++;
	    	  }

	      }//Ende While EOF fürt alle vok
		  return(alle_kategorien_ptr);
	}//Ende else für abfrage ob !kategorie
	      


	//Eine Gesamt-Kategorie erschaffen.
	if(true){
		alle_kategorien_ptr = malloc(sizeof(struct kategorie));
		strcpy(alle_kategorien_ptr->kategorie_name,"Alle Vokabeln");

		alle_kategorien_ptr->next_kategorie = erste_kategorie_ptr;
		alle_kategorien_ptr->erste_vokabel = erste_kategorie_ptr->erste_vokabel;
		alle_kategorien_ptr->anzahl_in_kategorie = erste_kategorie_ptr->anzahl_in_kategorie;

		kategorie_laeufer_ptr = erste_kategorie_ptr;
		vokabel_laeufer_ptr = alle_kategorien_ptr->erste_vokabel;

		while(kategorie_laeufer_ptr->next_kategorie != NULL){

			kategorie_laeufer_ptr = kategorie_laeufer_ptr->next_kategorie;

			while(vokabel_laeufer_ptr->next_vokabel != NULL){
				vokabel_laeufer_ptr = vokabel_laeufer_ptr->next_vokabel;
			}

			vokabel_laeufer_ptr->next_vokabel = kategorie_laeufer_ptr->erste_vokabel;
			alle_kategorien_ptr->anzahl_in_kategorie += kategorie_laeufer_ptr->anzahl_in_kategorie;
		}

	}//Ende gesamtzkategorie erschaffen

	return(alle_kategorien_ptr);
}//Ende Funktion liste einlesen




