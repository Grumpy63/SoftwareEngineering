/*
 * Main.c
 *
 *  Created on: 06.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "voc_functions.h"

/*In dieser Funktion kann der Nutzer auswählen, ob er über alle Vokabeln abgefragt werden möchte
 * oder nur über eine bestimmte Anzahl an Vokabeln abgefragt werden möchte*/

int vokabelzahl_feststellen(struct kategorie *abzufragende_kategorie){
	int x = 0;																																					//Variable x auf 0 gesetzt
	int anzahl = 0;																																				//Variable anzahl auf 0 gesetzt
	char dummy_zeichen[256];																																	//Variable dummy_zeichen

	setbuf(stdout, NULL);																																		//Bufferausgang auf NULL setzen
	printf("\nDie abzufragende Kategorie \"%s\" enhält %d Vokabeln.\n\n",abzufragende_kategorie->kategorie_name,abzufragende_kategorie->anzahl_in_kategorie);	//Ausgabe einer Informationsnachricht für den Nutzer
	printf("Möchten Sie über:\n\n");																															//Ausgabe einer Informationsnachricht für den Nutzer
	printf("(1) alle Vokabeln abgefragt werden oder\n");																										//Ausgabe einer Informationsnachricht für den Nutzer
	printf("(2) nur über eine bestimmte Anzahl abgefragt werden?\n");																							//Ausgabe einer Informationsnachricht für den Nutzer
	printf("\nZur Auswahl bitte die entsprechende Nummer eingeben und mit der Enter-Taste bestätigen:");														//Ausgabe einer Informationsnachricht für den Nutzer
	mark2:																																						//Sprungmarke mark2
		scanf("%d", &x);																																		//Einlesen der Nutzereingabe
		if(x == 1)																																				//If-Verzweigung, wenn Variable x gleich 1 ist
		{
			printf("\nEs wurde die Auswahl getroffen, dass alle Vokabeln abgefragt werden.\n");																	//Ausgabe einer Informationsnachricht für den Nutzer
			return(abzufragende_kategorie->anzahl_in_kategorie);																								//Rückgabe des Wertes abzufragende_kategorie->anzahl_in_kategorie
		}
		else if(x == 2)																																			//Else if Verzweigung, wenn Variable x gleich 2 ist
		{
			printf("\nEs wurde die Auswahl getroffen, dass über eine bestimmte Anzahl abgefragt wird, die vom Nutzer bestimmt wird.\n");						//Ausgabe einer Informationsnachricht für den Nutzer
			mark1:
				printf("\nWie viele Vokabeln möchten Sie abgefragt werden?:");																					//Ausgabe einer Informationsnachricht für den Nutzer
				scanf("%d", &anzahl);																															//Einlesen der Nutzereingabe
				if(anzahl <= 0 || anzahl > abzufragende_kategorie->anzahl_in_kategorie || isalpha(anzahl) !=0)													//If-Verzweigung
				{
					printf("\nUngültige Eingabe. Wählen Sie bitte eine Anzahl mit der Eingabe einer Zahl zwischen 1 und %d.\n",abzufragende_kategorie->anzahl_in_kategorie);//Ausgabe einer Informationsnachricht für den Nutzer
					scanf("%[^\r\n]", dummy_zeichen);																											//Puffer leeren
					goto mark1;																																	//Zu Sprungmarke mark1 gehen
				}
				else																																			//Else Verzweigung
				{
					if(anzahl == 1)																																//If-Verzweigung, wenn Variable anzahl gleich 1 ist
					{
						printf("\nIm Folgenden wird eine Vokabel abgefragt.\n");																				//Ausgabe einer Informationsnachricht für den Nutzer
						return(anzahl);																															//Rückgabe der Variablen anzahl
					}
					else																																		//Else Verzweigung
					{
					printf("\nIm Folgenden werden %d Vokabeln abgefragt.\n", anzahl);																			//Ausgabe einer Informationsnachricht für den Nutzer
					return(anzahl);																																//Rückgabe der Variablen anzahl
					}
				}
			}
		else if(isalpha(x) !=1){																																//Else-If-Verzweigung, wenn Variable x ein char ist
			printf("\nUngültige Eingabe. Wählen Sie bitte Ihre Auswahl mit der Eingabe der Zahl 1 oder 2.\n");													//Ausgabe einer Informationsnachricht für den Nutzer
			scanf("%[^\r\n]", dummy_zeichen);																													//Puffer Leeren
			goto mark2;																																			//Zu Sprungmarke mark2 gehen
		}
		return(anzahl);																																			//Rückgabe der Variablen anzahl
}
