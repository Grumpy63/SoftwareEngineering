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

	FILE *datei_vorlage_ptr;																				//

	char c = ' ';																							//
	int listenname = 0;																						//

	bool Flagge_Neue_Kategorie = false;																		//
	bool Flagge_Kategorie_mind = false;																		//

	bool Flagge_Vokabelpaar_beschreibbar = false;															//
	bool Flagge_Kategorie_befuellbar = false;																//

	bool Flagge_Vokabel1_vorhanden = false;																	//
	bool Flagge_Vokabel2_vorhanden = false;																	//


	bool Flagge_aktuelles_Vokablpaar = false;																//
	bool Flagge_alleVokabel1_fertig = false;																//


	bool Flagge_erster_Durchlauf = false;																	//
	bool Flagge_Semikolon = false;																			//

	bool Flagge_Entity = false;																				//

	int array_position_kategorie = 0;																		//
	int array_position_vokabel = 0;																			//


	struct kategorie * alle_kategorien_ptr = NULL;															//
	struct vokabel * alle_vokablen_ende_ptr = NULL;															//

	struct kategorie * erste_kategorie_ptr = NULL;															//
	struct kategorie * ende_kategorie_ptr = NULL;															//
	struct vokabel * ende_vokabel_ptr = NULL;																//

	struct vokabel * vokabel_cpy_laeufer_ptr = NULL;														//
	struct kategorie * kategorie_laeufer_ptr = NULL;														//
	struct vokabel * vokabel_org_laeufer_ptr = NULL;														//

	struct entitiy_name *erste_entity_name_ptr = NULL;														//
	struct entitiy_name *ende_entity_name_ptr = NULL;														//
	struct entitiy_name *entity_name_ptr = NULL;															//


	char needle[] = ".txt";																					//Variable zum Durchsuchen des Strings des Dateinamens auf ".txt"
	char needle2[] = "Usernames";																			//Variable zum Durchsuchen des Strings des Dateinamens auf "Usernames"
	char needle3[] = "Highscore";																			//Variable zum Durchsuchen des Strings des Dateinamens auf "Highscore"
	char needle4[] = ".csv";
	int Aufzaehlung = 1;																					//Variable zum Hochzählen bei Ausgabe der Dateinamen beginnend bei 1
	bool flag = false;																						//Variable zum Erkennen, ob mind. eine Vokabelliste vorhanden ist
	DIR *dir;																								//DIR pointer zum Auslesen des Verzeichnises
	struct dirent * entity;

	//Ausgeben der möglichen Vokabellisten
	do{
	setbuf(stdout, NULL);																					//Ein pointer entity vom Datentyp struct dirent
    dir = opendir(".");																						//Mit der Funktion opendir wird ein Verzeichnis geöffnet, in diesem Fall das Verzeichnis, in dem die Anwendung liegt -> (".") und dir zugewiesen
    if (dir) {																								//Wenn dir ungleich 0 wird in die if-Abfrage verzweigt
        while (0 != (entity = readdir(dir))) {																//Schleife zum Auslesen aller Dateinamen, solange bis keine Einträge mehr im Verzeichnis sind
                if(strcmp(entity->d_name, ".") == 0 ||														//Wird eventuell später benötigt, wenn Verzeichnis weiter verzeigt ist
                   strcmp(entity->d_name, "..") == 0){														//Wird eventuell später benötigt, wenn Verzeichnis weiter verzeigt ist
                    continue;																				//
                    }																						//

                if(((strstr(entity->d_name, needle) != 0) || strstr(entity->d_name, needle4) != 0)&&		//If-Verzweiung, wenn der Dateiname ein .txt ocer .csv enthält
                   (strstr(entity->d_name, needle2) == 0) &&												//und nicht den String Usernames enthält, da dies keine Vokabelliste ist
				   (strstr(entity->d_name, needle3) == 0)){													//und nicht den String Highscore enthält, da dies ebenfalls keine Vokabelliste ist
                    printf("(%d) %s\n", Aufzaehlung, entity->d_name);										//Printf Anweisung zum Ausgeben des Aufzählungspunkts mit dem Dateinamen

                    if(Flagge_Entity == false)																//If-Verzweigung zum Überprüfen ob eine struct entity_name besteht
                    {
                    	erste_entity_name_ptr = malloc(sizeof(struct entitiy_name));						//Allokieren einer ersten Struct enitiy_name auf den Pointer erste_entity_name_ptr
                    	ende_entity_name_ptr = erste_entity_name_ptr;										//ende_entity_name_ptr wird auf erste_entity_name_ptr gesetzt
                    	strcpy(erste_entity_name_ptr->name, entity->d_name);								//Der Name der ersten Datei wird in erste_entity_name_ptr->name geschrieben
                    	Flagge_Entity = true;																//Die Flagge_Entity wird gesetzt
                    }
                    else																					//Else-Verzweigung
                    {
                    	ende_entity_name_ptr->next = malloc(sizeof(struct entitiy_name));					//Allokieren einer neuen Struct entity_name auf den next Pointer der vorherigen Struct
                    	strcpy(ende_entity_name_ptr->next->name, entity->d_name);							//Der Name der nächsten Datei wird in die neu erstellte Struct geschrieben
                    	ende_entity_name_ptr = ende_entity_name_ptr->next;									//Der ende_entity_name_ptr wird auf den next Pointer der letzten Struct gesetzt
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

    printf("Bitte wählen Sie die Liste aus, welche abgefragt werden soll:\n");								//Ausgabe einer Informationsnachricht für den Nutzer
    do
    {
    	scanf("%d", &listenname);																			//Einlesen der Nutzereingabe zur Auswahl der Liste
    	if(listenname > Aufzaehlung || listenname <= 0)														//Eingabeüberprüfung der Nutzereingabe
    	    {
    	    	printf("Die Eingabe ist ungültig bitte geben Sie Ihre Auswahl erneut ein.\n");				//Ausgabe einer Informationsnachricht für den Nutzer
    	    	scanf("%d", &listenname);																	//Bei Falscheingabe erneutes Einlesen der Nutzereingabe
    	    	continue;
    	    }
    	else
    	{
    		break;
    	}
    }while(listenname > Aufzaehlung || listenname <= 0);													//Wenn Eingabe immer noch ungültig erneutes Durchlaufen der Schleife


	Aufzaehlung = 1;																						//Die Variable Aufzaehlung auf 1 setzen
	entity_name_ptr = erste_entity_name_ptr;																//Durchlaufpointer entity_name_ptr auf die erste Struct setzen mit erste_entity_name_ptr

	while(listenname != Aufzaehlung)																		//While-Schleife zum Durchlaufen der Struct entitiy_name bis der Pointer entity_name_ptr auf die Auswahl zeigt
	{
		entity_name_ptr = entity_name_ptr->next;															//Pointer entity_name_ptr auf das folgende Element setzen
		Aufzaehlung++;																						//Variable Aufzaehlung um eins inkrementieren
		continue;																							//Neuer Durchlauf der While-Schleife
	}
	datei_vorlage_ptr = fopen(entity_name_ptr->name, "r");													//Die ausgewählte Datei lesend öffnen und Anfangsadresse in File-Pointer datei_vorlage_ptr schreiben

	if(datei_vorlage_ptr == NULL)																			//If-Abfrage ob der Pointer datei_vorlage_ptr auf NULL zeigt, denn dann konnte das File nicht geöffnet werden
	{
		printf("Die Datei konnte leider nicht geöffnet werden.\n");											//Ausgabe einer Informationsnachricht für den Nutzer
		printf("Bitte geben Sie eine neue Auswahl ein:\n");													//Ausgabe einer Informationsnachricht für den Nutzer
	}
	}while(datei_vorlage_ptr == NULL);																		//Wenn der Pointer datei_vorlage_ptr auf NULL zeigt, beginnt ein neuer Durchlauf um die Auswahl zu wiederholen



	//Überprüfen des Files auf mindestens eine Kategorie

	while(c != EOF)																							//While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
	{
		c = fgetc(datei_vorlage_ptr);																		//Mit der Funktion fgetc() wird ein Zeichen aus dem File ausgelesen und in die Variable c geschrieben


		if(c == '!')																						//Die If-Abfrage überprüft das ausgelesene Zeichen auf ein "!", was gleichbedeutend mit dem Anfang einer Kategorie ist
		{
		  Flagge_Kategorie_mind = true;																		//Die Bool-Variable Flagge_Kategorie_mind wird auf true gesetzt
		  break;																							//Die While-Schleife wird verlassen
		}

	}

	fseek(datei_vorlage_ptr, 0, SEEK_SET);																	//Die Funktion fseek() setzt den Pointer datei_vorlage_ptr zurück auf den Anfang des Files

	if(Flagge_Kategorie_mind == true){																		//Die If-Abfrage überprüft ob die Variable Flagge_Kategorie_mind auf true steht

		  while(c != EOF)																					//While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
	      {
			  //Nächstes Zeichen auslesen
	    	  c = fgetc(datei_vorlage_ptr);																	//Mit der Funktion fgetc() wird ein Zeichen aus dem File ausgelesen und in die Variable c geschrieben

	    	  //Zeilenbrüche raustrennen
	    	  if((Flagge_Semikolon == true && c == ';') ||c == '\r' || c == EOF)							//If-Abfrage die als Filter für Zeilenumbrüche und doppelte Semikolons wirkt
	    	  {
	    		  continue;																					//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
	    	  }
	    	  if(c == ';')																					//If-Abfrage überprüft ob c ein ";" ist
	    	  {
	    		  Flagge_Semikolon = true;																	//Setzen der Variablen Flagge_Semikolon auf true
	    	  }
	    	  else																							//Else-Verzweigung
	    	  {
	    		  Flagge_Semikolon = false;																	//Setzen der Variablen Flagge_Semikolon auf false
	    	  }

			  //Beginn einer neuen Kategorie
			  if(c == '!')																					//If-Abfrage überprüft ob c ein "!" ist
			  {
				  Flagge_Neue_Kategorie = true;																//Setzen der Variablen Flagge_Neue_Kategorie auf true
				  Flagge_Kategorie_befuellbar = false;														//Setzen der Variablen Flagge_Kategorie_befuellbar auf false

				  if(erste_kategorie_ptr == NULL){															//If-Abfrage überprüft ob der Pointer erste_kategorie_ptr auf NULL zeigt
					  erste_kategorie_ptr = malloc(sizeof(struct kategorie));								//Es wird eine neue struct kategorie auf den Pointer erste_kategorie_ptr allokiert
					  ende_kategorie_ptr = erste_kategorie_ptr;												//Der Pointer ende_kategorie_ptr zeigt auf die erste struct kategorie
				  }
				  else{																						//Else-Verzweigung
					  ende_kategorie_ptr->next_kategorie = malloc(sizeof(struct kategorie));				//Auf den Pointer next der struct kategorie wird eine neue struct kategorie allokiert
					  ende_kategorie_ptr = ende_kategorie_ptr->next_kategorie;								//Der Pointer ende_kategorie_ptr wir um ein Element in der Liste weiter verschoben
				  }
				  ende_kategorie_ptr->erste_vokabel = NULL;													//Der Pointer erste_vokabel der struct kategorie wird auf NULL gesetzt
				  continue;																					//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
			  }

			  //Einlesen eines Kategorie-Namens
			  if(Flagge_Neue_Kategorie == true)																//If-Abfrage überprüft ob die Variable Flagge_Neue_Kategorie true ist
			  {

				  if(c == ';'|| c == '\n')																	//If-Abfrage ob c ein ";" oder ein "\n" ist
				  {
					  Flagge_Neue_Kategorie = false;														//Setzen der Variablen Flagge_Neue_Kategorie auf false
					  Flagge_Kategorie_befuellbar = true;													//Setzen der Variablen Flagge_Kategorie_befuellbar auf true
					  array_position_kategorie = 0;															//Setzen der Variabeln array_position_kategorie zum Durchlaufen des Arrays kategorie_name auf 0
					  continue;																				//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
				  }
				  ende_kategorie_ptr->kategorie_name[array_position_kategorie] = c;							//Dem Array kategorie_name wird das eingelesene Zeichen an der Position array_position_kategorie zugewiesen
				  array_position_kategorie++;																//Die Variable array_position_kategorie wird um eins inkrementiert
				  continue;																					//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
			  }

			  //Neues Vokabelpaar anzulegen
			  if(Flagge_Vokabelpaar_beschreibbar == false && Flagge_Kategorie_befuellbar == true && c!='\n' && c!=';'){		//
				  Flagge_Vokabel1_vorhanden = false;														//Setzen der Variablen Flagge_Vokabel1_vorhanden auf false
				  Flagge_Vokabel2_vorhanden = false;														//Setzen der Variablen Flagge_Vokabel2_vorhanden auf false

				  if(ende_kategorie_ptr->erste_vokabel == NULL){											//If-Abfrage ob der Pointer ende_kategorie_ptr->erste_vokabel auf NULL zeigt
					  ende_kategorie_ptr->erste_vokabel = malloc(sizeof(struct vokabel));					//Auf den Pointer ende_kategorie_ptr->erste_vokabel wird eine neue struct kategorie allokiert
					  ende_vokabel_ptr = ende_kategorie_ptr->erste_vokabel;									//Der Pointer ende_vokabel_ptr wird auf den Pointer ende_kategorie_ptr->erste_vokabel gesetzt
				  }
				  else{																						//Else-Verzweigung
					  ende_vokabel_ptr->next_vokabel = malloc(sizeof(struct vokabel));						//Auf den Pointer ende_vokabel_ptr->next_vokabel wird eine neue struct vokabel allokiert
					  ende_vokabel_ptr = ende_vokabel_ptr->next_vokabel;									//Der Pointer ende_vokabel_ptr wird auf den Pointer ende_vokabel_ptr->next_vokabel gesetzt (nächste struct vokabel)
				  }
				  ende_vokabel_ptr->flag = 0;																//Über den Pointer ende_vokabel_ptr wird die Variable flag auf 0 initialisiert

				  ende_kategorie_ptr->anzahl_in_kategorie++;												//Über den Pointer ende_kategorie_ptr wird die Variable anzahl_in_kategorie um eins inkrementiert
				  Flagge_Vokabelpaar_beschreibbar = true;													//Setzen der Variablen Flagge_Vokabelpaar_beschreibbar auf true
			  }

			  //Vokabel eins vorhanden
			  if(Flagge_Vokabel1_vorhanden == false && Flagge_Vokabelpaar_beschreibbar == true){			//If-Abfrage ob die Variable Flagge_Vokabel1_vorhanden und die Variable Flagge_Vokabelpaar_beschreibbar false sind

				  if(c == ';' || c == '\n')																	//If-Abfrage ob c ein ";" oder ein "\n" ist
				  {
					  Flagge_Vokabel1_vorhanden = true;														//Setzen der Variablen Flagge_Vokabel1_vorhanden auf true
					  array_position_vokabel = 0;															//Setzen der Variabeln array_position_vokabel zum Durchlaufen des Arrays vokabel_sprache1 auf 0
					  continue;																				//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
				  }
				  ende_vokabel_ptr->vokabel_sprache1[array_position_vokabel] = c;							//Dem Array vokabel_sprache1 wird das eingelesene Zeichen an der Position array_position_vokabel zugewiesen
				  array_position_vokabel++;																	//Die Variable array_position_vokabel wird um eins inkrementiert
				  continue;																					//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
			  }

			  //Vokabel zwei vorhanden
			  if(Flagge_Vokabel2_vorhanden == false && Flagge_Vokabelpaar_beschreibbar == true){			//If-Abfrage ob die Variable Flagge_Vokabel2_vorhanden und die Variable Flagge_Vokabelpaar_beschreibbar false sind

				  if(c == ';' || c == '\n')																	//If-Abfrage ob c ein ";" oder ein "\n" ist
				  {
					  Flagge_Vokabel2_vorhanden = true;														//Setzen der Variablen Flagge_Vokabel2_vorhanden auf true
					  Flagge_Vokabelpaar_beschreibbar = false;												//Setzen der Variablen Flagge_Vokabelpaar_beschreibbar auf false
					  array_position_vokabel = 0;															//Setzen der Variabeln array_position_vokabel zum Durchlaufen des Arrays vokabel_sprache2 auf 0
					  continue;																				//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
				  }
				  ende_vokabel_ptr->vokabel_sprache2[array_position_vokabel] = c;							//Dem Array vokabel_sprache2 wird das eingelesene Zeichen an der Position array_position_vokabel zugewiesen
				  array_position_vokabel++;																	//Die Variable array_position_vokabel wird um eins inkrementiert
				  continue;																					//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
			  }
	    	}																								//While: Dokument auslesen zuende
	}																										//If: Kategorien vorhanden zuende
	else{																									//Else-Verzweigung
		Flagge_erster_Durchlauf = true;																		//Setzen der Variablen Flagge_erster_Durchlauf auf true
		while(c != EOF || Flagge_erster_Durchlauf == true)													//While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet oder Flagge_erster_Durchlauf true ist
		{
			Flagge_erster_Durchlauf = false;																//Setzen der Variablen Flagge_erster_Durchlauf auf false

		  //Nächstes Zeichen auslesen
		  c = fgetc(datei_vorlage_ptr);																		//Mit der Funktion fgetc() wird ein Zeichen aus dem File ausgelesen und in die Variable c geschrieben

    	  if((Flagge_Semikolon == true && c == ';') ||c == '\r' || c == EOF)								//If-Abfrage ob die Variable Flagge_Semikolon true und c ein ";" ist oder c ein "\r" oder End-Of-File ist
    	  {
    		  continue;																						//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
    	  }
    	  if(c == ';')																						//If-Abfrage ob c ein ";" ist
    	  {
    		  Flagge_Semikolon = true;																		//Setzen der Variablen Flagge_Semikolon auf true
    	  }
    	  else																								//Else-Verzweigung
    	  {
    		  Flagge_Semikolon = false;																		//Setzen der Variablen Flagge_Semikolon auf false
    	  }

		  //Einzige Erste Kategorie/Vokabel anlegen
		  if(alle_kategorien_ptr == NULL){																	//If-Abfrage ob der Pointer alle_kategorien_ptr auf NULL zeigt
			  alle_kategorien_ptr = malloc(sizeof(struct kategorie));										//Auf den Pointer alle_kategorien_ptr wird die erste struct kategorie allokiert
			  strcpy(alle_kategorien_ptr->kategorie_name,"Alle Vokabeln");									//Mit der Funktion strcpy() wird der String "Alle Vokabeln" über den Pointer alle_kategorien_ptr in die Variable kategorie_name kopiert

			  alle_kategorien_ptr->erste_vokabel = malloc(sizeof(struct vokabel));							//Auf den Pointer alle_kategorien_ptr->erste_vokabel wird die erste struct vokabel allokiert
			  alle_vokablen_ende_ptr =  alle_kategorien_ptr->erste_vokabel;									//Der Pointer alle_vokablen_ende_ptr wird auf den Pointer alle_kategorien_ptr->erste_vokabel gesetzt
			  Flagge_aktuelles_Vokablpaar = true;															//Setzen der Variablen Flagge_aktuelles_Vokablpaar auf true
		  }

		  //Vokabel 1
		  if(Flagge_alleVokabel1_fertig == false){															//If-Abfrage ob die Variable Flagge_alleVokabel1_fertig false ist

			  if(Flagge_aktuelles_Vokablpaar == false){														//If-Abfrage ob die Variable Flagge_aktuelles_Vokablpaar false ist
				  alle_vokablen_ende_ptr->next_vokabel = malloc(sizeof(struct vokabel));					//Auf den Pointer alle_vokablen_ende_ptr->next_vokabel wird eine neue struct vokabel allokiert
				  alle_vokablen_ende_ptr = alle_vokablen_ende_ptr->next_vokabel;							//Der Pointer alle_vokablen_ende_ptr wird auf den Pointer alle_vokablen_ende_ptr->next_vokabel gesetzt (auf die nächste Vokabel)
				  Flagge_aktuelles_Vokablpaar = true;														//Setzen der Variablen Flagge_aktuelles_Vokablpaar auf true
			  }

			  if(c == ';'){																					//If-Abfrage ob c ein ";" ist
				  Flagge_alleVokabel1_fertig = true;														//Setzen der Variablen Flagge_alleVokabel1_fertig auf true
				  continue;																					//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
			  }
			  alle_vokablen_ende_ptr->vokabel_sprache1[array_position_vokabel] = c;							//Dem Array vokabel_sprache1 wird das eingelesene Zeichen an der Position array_position_vokabel zugewiesen
			  array_position_vokabel++;																		//Die Variable array_position_vokabel wird um eins inkrementiert
		  }

		  //Vokabel 2
		  if(Flagge_alleVokabel1_fertig == true){															//If-Abfrage ob die Variable Flagge_alleVokabel1_fertig true ist

			  if(c == ';'){																					//If-Abfrage ob c ein ";" ist
				  Flagge_alleVokabel1_fertig = false;														//Setzen der Variablen auf false
				  Flagge_aktuelles_Vokablpaar = false;														//Setzen der Variablen auf false
				  alle_kategorien_ptr->anzahl_in_kategorie++;												//Über den Pointer alle_kategorien_ptr wird die Variable anzahl_in_kategorie um eins inkrementiert
				  continue;																					//Erneuter Beginn der While-Schleife zum zeichenweisen Auslesen des Files solange c nicht End-Of-File beinhaltet
			  }

			  alle_vokablen_ende_ptr->vokabel_sprache2[array_position_vokabel] = c;							//Dem Array vokabel_sprache2 wird das eingelesene Zeichen an der Position array_position_vokabel zugewiesen
			  array_position_vokabel++;																		//Die Variable array_position_vokabel wird um eins inkrementiert
		  }

		}//Ende While EOF fürt alle vok
		return(alle_kategorien_ptr);																		//Der Pointer alle_kategorien_ptr wird von der Funktion zurück gegeben
	}//Ende else für abfrage ob !kategorie



	//Eine Gesamt-Kategorie erschaffen.
		if(true){																							//If-Abfrage
			alle_kategorien_ptr = malloc(sizeof(struct kategorie));											//Auf den Pointer alle_kategorien_ptr wird die erste struct kategorie allokiert
			strcpy(alle_kategorien_ptr->kategorie_name,"Alle Vokabeln");									//Mit der Funktion strcpy() wird der String "Alle Vokabeln" über den Pointer alle_kategorien_ptr in die Variable kategorie_name kopiert

			alle_kategorien_ptr->next_kategorie = erste_kategorie_ptr;										//
			alle_kategorien_ptr->anzahl_in_kategorie = erste_kategorie_ptr->anzahl_in_kategorie;			//

			kategorie_laeufer_ptr = erste_kategorie_ptr;													//

			vokabel_org_laeufer_ptr = erste_kategorie_ptr->erste_vokabel;									//
			vokabel_cpy_laeufer_ptr = malloc(sizeof(struct vokabel));										//

			cpy_vokabel(vokabel_cpy_laeufer_ptr,vokabel_org_laeufer_ptr);									//

			alle_kategorien_ptr->erste_vokabel = vokabel_cpy_laeufer_ptr;									//

			while(1){																						//

				while(vokabel_org_laeufer_ptr->next_vokabel != NULL){										//
					vokabel_cpy_laeufer_ptr->next_vokabel = malloc(sizeof(struct vokabel));					//
					vokabel_cpy_laeufer_ptr = vokabel_cpy_laeufer_ptr->next_vokabel;						//
					vokabel_org_laeufer_ptr = vokabel_org_laeufer_ptr->next_vokabel;						//


					cpy_vokabel(vokabel_cpy_laeufer_ptr,vokabel_org_laeufer_ptr);							//
				}

				kategorie_laeufer_ptr = kategorie_laeufer_ptr->next_kategorie;								//
				if(kategorie_laeufer_ptr == NULL)															//
				{
					break;																					//
				}
				vokabel_org_laeufer_ptr = kategorie_laeufer_ptr->erste_vokabel;								//
				vokabel_cpy_laeufer_ptr->next_vokabel = malloc(sizeof(struct vokabel));						//
				vokabel_cpy_laeufer_ptr = vokabel_cpy_laeufer_ptr->next_vokabel;							//
				cpy_vokabel(vokabel_cpy_laeufer_ptr,vokabel_org_laeufer_ptr);								//
				alle_kategorien_ptr->anzahl_in_kategorie += kategorie_laeufer_ptr->anzahl_in_kategorie;		//
			}

		}//Ende Gesamtzkategorie erschaffen

	fclose(datei_vorlage_ptr);																				//
	//closedir(dir);
	return(alle_kategorien_ptr);																			//
}//Ende Funktion liste einlesen


void cpy_vokabel(struct vokabel * copy,struct vokabel * original){											//

	strcpy(copy->vokabel_sprache1,original->vokabel_sprache1);												//
	strcpy(copy->vokabel_sprache2,original->vokabel_sprache2);												//
	copy->flag = original->flag;																			//

}

