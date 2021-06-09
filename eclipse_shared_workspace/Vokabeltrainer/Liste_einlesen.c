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
#include <windows.h>
#include <stdbool.h>
#include "voc_functions.h"

void cpy_vokabel(struct vokabel * copy,struct vokabel * original);

struct kategorie *liste_einlesen(){

	FILE *datei_vorlage_ptr;

	char c = ' ';
	int listenname = 0;

	bool Flagge_Neue_Kategorie = false;
	bool Flagge_Kategorie_mind = false;

	bool Flagge_Vokabelpaar_beschreibbar = false;
	bool Flagge_Kategorie_befuellbar = false;

	bool Flagge_Vokabel1_vorhanden = false;
	bool Flagge_Vokabel2_vorhanden = false;


	bool Flagge_aktuelles_Vokablpaar = false;
	bool Flagge_alleVokabel1_fertig = false;


	bool Flagge_erster_Durchlauf = false;
	bool Flagge_Semikolon = false;

	bool Flagge_Entity = false;

	int array_position_kategorie = 0;
	int array_position_vokabel = 0;


	struct kategorie * alle_kategorien_ptr = NULL;
	struct vokabel * alle_vokablen_ende_ptr = NULL;

	struct kategorie * erste_kategorie_ptr = NULL;
	struct kategorie * ende_kategorie_ptr = NULL;
	struct vokabel * ende_vokabel_ptr = NULL;

	struct vokabel * vokabel_cpy_laeufer_ptr = NULL;
	struct kategorie * kategorie_laeufer_ptr = NULL;
	struct vokabel * vokabel_org_laeufer_ptr = NULL;

	struct entitiy_name{
		char name[256];
		struct entitiy_name *next;
	};
	struct entitiy_name *erste_entity_name_ptr = NULL;
	struct entitiy_name *ende_entity_name_ptr = NULL;
	struct entitiy_name *entity_name_ptr = NULL;


	char needle[] = ".txt";																					//Variable zum Durchsuchen des Strings des Dateinamens auf ".txt"
		char needle2[] = "Usernames";																		//Variable zum Durchsuchen des Strings des Dateinamens auf "Usernames"
		char needle3[] = "Highscore";																		//Variable zum Durchsuchen des Strings des Dateinamens auf "Highscore"
	    char needle4[] = ".csv";
		int Aufzaehlung = 1;																				//Variable zum Hochzählen bei Ausgabe der Dateinamen beginnend bei 1
	    bool flag = false;																					//Variable zum Erkennen, ob mind. eine Vokabelliste vorhanden ist
	    DIR *dir;																							//DIR pointer zum Auslesen des Verzeichnises
	    struct dirent * entity;

	//Ausgeben der möglichen Vokabellisten
	do{
	setbuf(stdout, NULL);																					//Ein pointer entity vom Datentyp struct dirent
    dir = opendir(".");																						//Mit der Funktion opendir wird ein Verzeichnis geöffnet, in diesem Fall das Verzeichnis, in dem die Anwendung liegt -> (".") und dir zugewiesen
    if (dir) {																								//Wenn dir ungleich 0 wird in die if-Abfrage verzweigt
        while (0 != (entity = readdir(dir))) {																//Schleife zum Auslesen aller Dateinamen, solange bis keine Einträge mehr im Verzeichnis sind
                if(strcmp(entity->d_name, ".") == 0 ||														//Wird eventuell später benötigt, wenn Verzeichnis weiter verzeigt ist
                   strcmp(entity->d_name, "..") == 0){														//
                    continue;																				//
                    }																						//

                if(((strstr(entity->d_name, needle) != 0) || strstr(entity->d_name, needle4) != 0)&&												//If-Verzweiung, wenn der Dateiname ein .txt enthält
                   (strstr(entity->d_name, needle2) == 0) &&												//und nicht den String Usernames enthält, da dies keine Vokabelliste
				   (strstr(entity->d_name, needle3) == 0)){													//und nicht den String Highscore enthält, da dies ebenfalls keine Vokabelliste
                    printf("(%d) %s\n", Aufzaehlung, entity->d_name);										//Printf Anweisung zum Ausgeben des Aufzählungspunkts mit dem Dateinamen

                    if(Flagge_Entity == false)
                    {
                    	erste_entity_name_ptr = malloc(sizeof(struct entitiy_name));
                    	ende_entity_name_ptr = erste_entity_name_ptr;
                    	strcpy(erste_entity_name_ptr->name, entity->d_name);
                    	Flagge_Entity = true;
                    }
                    else
                    {
                    	ende_entity_name_ptr->next = malloc(sizeof(struct entitiy_name));
                    	strcpy(ende_entity_name_ptr->next->name, entity->d_name);
                    	ende_entity_name_ptr = ende_entity_name_ptr->next;
                    }
                    Aufzaehlung ++;																			//Variable Aufzaehlung um eins inkrementieren
                    flag = true;																			//Wenn mind. eine Datei gefunden und ausgegeben wurde, wird die flag gesetzt

                }
        }
        if(flag == false){																					//Flag überprüfen, für den Fall, dass keine Datei gefunden wurde
        	printf("Es konnte keine Vokabelliste in dem Verzeichnis der Anwendung gefunden werden./n");		//Ausgabe einer Informationsnachricht für den Nutzer
        }																									//Nach dem Ablauf der Funktion wird das zu Beginn geöffnete Verzeichnis wieder geschlossen
    }
    //Abfrage nach der zu öffnenden Datei

    printf("Bitte wählen Sie die Liste aus, welche abgefragt werden soll:\n");
    do
    {
    	scanf("%d", &listenname);
    	if(listenname > Aufzaehlung || listenname <= 0)
    	    {
    	    	printf("Die Eingabe ist ungültig bitte geben Sie Ihre Auswahl erneut ein.\n");
    	    	scanf("%d", &listenname);
    	    	continue;
    	    }
    	else
    	{
    		break;
    	}
    }while(listenname > Aufzaehlung || listenname <= 0);


	Aufzaehlung = 1;
	entity_name_ptr = erste_entity_name_ptr;

	while(listenname != Aufzaehlung)
	{
		entity_name_ptr = entity_name_ptr->next;
		Aufzaehlung++;
		continue;
	}
	datei_vorlage_ptr = fopen(entity_name_ptr->name, "r");

	if(datei_vorlage_ptr == NULL)
	{
		printf("Die Datei konnte leider nicht geöffnet werden.\n");
		printf("Bitte geben Sie eine neue Auswahl ein:\n");
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
	    	  if((Flagge_Semikolon == true && c == ';') ||c == '\r' || c == EOF)
	    	  {
	    		  continue;
	    	  }
	    	  if(c == ';')
	    	  {
	    		  Flagge_Semikolon = true;
	    	  }
	    	  else
	    	  {
	    		  Flagge_Semikolon = false;
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
				  ende_kategorie_ptr->erste_vokabel = NULL;
				  continue;
			  }

			  //Einlesen eines Kategorie-Namens
			  if(Flagge_Neue_Kategorie == true)
			  {

				  if(c == ';'|| c == '\n')
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
			  if(Flagge_Vokabelpaar_beschreibbar == false && Flagge_Kategorie_befuellbar == true && c!='\n' && c!=';'){
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
				  ende_vokabel_ptr->flag = 0;

				  ende_kategorie_ptr->anzahl_in_kategorie++;
				  Flagge_Vokabelpaar_beschreibbar = true;
			  }

			  //Vokabel eins vorhanden
			  if(Flagge_Vokabel1_vorhanden == false && Flagge_Vokabelpaar_beschreibbar == true){

				  if(c == ';' || c == '\n')
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

				  if(c == ';' || c == '\n')
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
		Flagge_erster_Durchlauf = true;
		while(c != EOF || Flagge_erster_Durchlauf == true)
		{
			Flagge_erster_Durchlauf = false;

		  //Nächstes Zeichen auslesen
		  c = fgetc(datei_vorlage_ptr);

    	  if((Flagge_Semikolon == true && c == ';') ||c == '\r' || c == EOF)
    	  {
    		  continue;
    	  }
    	  if(c == ';')
    	  {
    		  Flagge_Semikolon = true;
    	  }
    	  else
    	  {
    		  Flagge_Semikolon = false;
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
			alle_kategorien_ptr->anzahl_in_kategorie = erste_kategorie_ptr->anzahl_in_kategorie;

			kategorie_laeufer_ptr = erste_kategorie_ptr;

			vokabel_org_laeufer_ptr = erste_kategorie_ptr->erste_vokabel;
			vokabel_cpy_laeufer_ptr = malloc(sizeof(struct vokabel));

			cpy_vokabel(vokabel_cpy_laeufer_ptr,vokabel_org_laeufer_ptr);

			alle_kategorien_ptr->erste_vokabel = vokabel_cpy_laeufer_ptr;

			while(1){

				while(vokabel_org_laeufer_ptr->next_vokabel != NULL){
					vokabel_cpy_laeufer_ptr->next_vokabel = malloc(sizeof(struct vokabel));
					vokabel_cpy_laeufer_ptr = vokabel_cpy_laeufer_ptr->next_vokabel;
					vokabel_org_laeufer_ptr = vokabel_org_laeufer_ptr->next_vokabel;


					cpy_vokabel(vokabel_cpy_laeufer_ptr,vokabel_org_laeufer_ptr);
				}

				kategorie_laeufer_ptr = kategorie_laeufer_ptr->next_kategorie;
				if(kategorie_laeufer_ptr == NULL)
				{
					break;
				}
				vokabel_org_laeufer_ptr = kategorie_laeufer_ptr->erste_vokabel;
				vokabel_cpy_laeufer_ptr->next_vokabel = malloc(sizeof(struct vokabel));
				vokabel_cpy_laeufer_ptr = vokabel_cpy_laeufer_ptr->next_vokabel;
				cpy_vokabel(vokabel_cpy_laeufer_ptr,vokabel_org_laeufer_ptr);
				alle_kategorien_ptr->anzahl_in_kategorie += kategorie_laeufer_ptr->anzahl_in_kategorie;
			}

		}//Ende gesamtzkategorie erschaffen

	fclose(datei_vorlage_ptr);
	//closedir(dir);
	return(alle_kategorien_ptr);
}//Ende Funktion liste einlesen


void cpy_vokabel(struct vokabel * copy,struct vokabel * original){

	strcpy(copy->vokabel_sprache1,original->vokabel_sprache1);
	strcpy(copy->vokabel_sprache2,original->vokabel_sprache2);
	copy->flag = original->flag;

}

