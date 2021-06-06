/*
 * Main.c
 *
 *  Created on: 02.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include "header.h"



void verzeichnis_auslesen(){																			//Definition der Funktion verzeichnis_auslesen

	char needle[] = ".txt";																				//Variable zum Durchsuchen des Strings des Dateinamens auf ".txt"
	char needle2[] = "Usernames";																		//Variable zum Durchsuchen des Strings des Dateinamens auf "Usernames"
	char needle3[] = "Highscore";																		//Variable zum Durchsuchen des Strings des Dateinamens auf "Highscore"
    int Aufzaehlung = 1;																				//Variable zum Hochz�hlen bei Ausgabe der Dateinamen beginnend bei 1
    bool flag = false;																					//Variable zum Erkennen, ob mind. eine Vokabelliste vorhanden ist
    DIR *dir;																							//DIR pointer zum Auslesen des Verzeichnises
    struct dirent * entity;																				//Ein pointer entity vom Datentyp struct dirent

    dir = opendir("C:/Users/David/Desktop/SoftwareEngineering/eclipse_shared_workspace/Voktrainer_Final_Test/Release");																					//Mit der Funktion opendir wird ein Verzeichnis ge�ffnet, in diesem Fall das Verzeichnis, in dem die Anwendung liegt -> (".") und dir zugewiesen
    if (dir) {																							//Wenn dir ungleich 0 wird in die if-Abfrage verzweigt
        while (0 != (entity = readdir(dir))) {															//Schleife zum Auslesen aller Dateinamen, solange bis keine Eintr�ge mehr im Verzeichnis sind
                if(strcmp(entity->d_name, ".") == 0 ||												//Wird eventuell sp�ter ben�tigt, wenn Verzeichnis weiter verzeigt ist
                   strcmp(entity->d_name, "..") == 0){												//
                    continue;																			//
                    }																					//

                if((strstr(entity->d_name, needle) != 0) &&												//If-Verzweiung, wenn der Dateiname ein .txt enth�lt
                   (strstr(entity->d_name, needle2) == 0) &&											//und nicht den String Usernames enth�lt, da dies keine Vokabelliste
				   (strstr(entity->d_name, needle3) == 0)){												//und nicht den String Highscore enth�lt, da dies ebenfalls keine Vokabelliste
                    printf("%d) %s\n", Aufzaehlung, entity->d_name);									//Printf Anweisung zum Ausgeben des Aufz�hlungspunkts mit dem Dateinamen
                    Aufzaehlung ++;																		//Variable Aufzaehlung um eins inkrementieren
                    flag = true;																		//Wenn mind. eine Datei gefunden und ausgegeben wurde, wird die flag gesetzt

                }
        }
        if(flag == false){																				//Flag �berpr�fen, f�r den Fall, dass keine Datei gefunden wurde
        	printf("Es konnte keine Vokabelliste in dem Verzeichnis der Anwendung gefunden werden./n");	//Ausgabe einer Informationsnachricht f�r den Nutzer
        }
        closedir(dir);																					//Nach dem Ablauf der Funktion wird das zu Beginn ge�ffnete Verzeichnis wieder geschlossen
    }
	//return(0);
}

