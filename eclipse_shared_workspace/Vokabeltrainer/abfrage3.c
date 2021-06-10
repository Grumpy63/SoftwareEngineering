/*
 * abfrage3.c
 *
 *  Created on: 08.06.2021
 *      Author: Luca
 */

#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"voc_functions.h"


int abfrage3(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{
	int anzahl_korrekter_voc = 0;
	struct vokabel* voc_ptr = NULL; 										//Hilfsptr auf aktuelle Vokabel
	int zufall_voc = 0;														//Randomzahl für Vokabelabfragenreihenfolge
	int zufall_sprache = 0;													//Zufalls Zahl für die zufällige Sprachreihenfolge
	char dummy_zeichen = ' ';												//Dummy zum Leerzeichen einlesen
	char eingabe[256];														//Platzhalter für User Vokabeleingabe


	scanf("%c", &dummy_zeichen);											//Leeren des Puffers
				if(dummy_zeichen == '\r')									//auch auf anderen OS (haben evtl mehr Zeichen)
						{
							scanf("%c", &dummy_zeichen);
						}


		for (int i=0; i < number_abzufragende_voc; i++)						//Schleife für die Abfragezyklen, i ist Laufvariable
		{

				reroll:
				srand(time(NULL));											//Generieren einer Zufallszahl von int in Bereich 0 bis Anzahl in Kategorie minus 1
				zufall_voc = irand(0, abzufragende_kategorie->anzahl_in_kategorie);

				voc_ptr = abzufragende_kategorie->erste_vokabel;			//Hilfszeiger auf Beginn der abzufragenden Vokabelliste

				for(int x = 0; x < (zufall_voc-1); x++) 							//Zeiger jeweils Vielfaches der Zufallszahl Weitersetzen auf die nächsten Listenelemente
				{
					voc_ptr = voc_ptr->next_vokabel;
				}

				if(voc_ptr->flag == 1)										//Wenn ausgewählte Vokabel bereits abgefragt ist
				{
					goto reroll;											//Suche eine neue Vokabel
				}
				else
				{
				voc_ptr->flag = 1;  										//Flag der Ausgewählten Vokabel setzen
				}


				//Nun die zufällige Sprachreihenfolge

				srand(time(NULL));											//Generieren einer von zwei Zufallszahl
				zufall_sprache = irand(0, 1);

				switch(zufall_sprache)
				{
				case 0:

					printf("\nBitte geben sie die Übersetzung von %s ein: ", voc_ptr->vokabel_sprache1);  	//Aufforderung zur Eingabe
					scanf("%[^\r\n]", eingabe);																//Es können auch Leerzeichen eingegeben werden
					scanf("%c", &dummy_zeichen);															//Leeren des Puffers
						if(dummy_zeichen == '\r')															//auch auf anderen OS (haben evtl mehr Zeichen)
								{
									scanf("%c", &dummy_zeichen);
								}
					strlwr(eingabe);
					if(strcmp(eingabe, voc_ptr->vokabel_sprache2) == 0)  								//Vergleich der beiden Strings.
						{
							printf("Ihre Eingabe war richtig!\n");											//Ausgabe eines Feedbacks
							anzahl_korrekter_voc++;															// Counter für richtige Vokabeln wird hochgesetzt
						}
					else
						{
							printf("Leider falsch! Korrekte wäre gewesen: %s\n", voc_ptr->vokabel_sprache2);   //Feedback mit richtiger Übersetzung
						}

					voc_ptr = NULL;	//Hilfszeiger wird wieder geerdet

				break;


				case 1:

					printf("\nBitte geben sie die Übersetzung von %s ein: ",voc_ptr->vokabel_sprache2);  // Aufforderung zur Eingabe
					scanf("%[^\r\n]", eingabe);							//Es können auch Leerzeichen eingegeben werden
					scanf("%c", &dummy_zeichen);										//Leeren des Puffers
						if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
								{
									scanf("%c", &dummy_zeichen);
								}
					strlwr(eingabe);																	//Eingabe ist nun all lower cases
					if(strcmp(eingabe, voc_ptr->vokabel_sprache1) == 0)  //Vergleich der beiden Strings.
						{
							printf("Ihre Eingabe war richtig!\n");			//Ausgabe eines Feedbacks
							anzahl_korrekter_voc++;							// Counter für richtige Vokabeln wird hochgesetzt
						}
					else
						{
						printf("Leider falsch! Korrekte wäre gewesen: %s\n", voc_ptr->vokabel_sprache1);   //Feedback mit richtiger Übersetzung
						}

					voc_ptr = NULL;	//Zeiger wird wieder geerdet

				break;


				default: printf("Interner Random Fehler!\n");
				}

		}




	return(anzahl_korrekter_voc);
}
