/*
 * abfrage1.c
 *
 *  Created on: 08.06.2021
 *      Author: Alexander Hein
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "voc_functions.h"								//Einbinden der Header-Dateien


int abfrage1(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc)
{


int anzahl_korrekter_voc = 0;
struct vokabel* help_ptr = NULL; 						//Hilfszeiger (Cursor)
int zufall = 0;
char dummy_zeichen = ' ';
char eingabe [256];


scanf("%c", &dummy_zeichen);										//Leeren des Puffers
			if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}


	for (int i=0; i<number_abzufragende_voc; i++)				//Schleife für die Abfragezyklen, i ist Laufvariable
	{
			reroll:
			srand(time(NULL));								//Generieren einer Zufallszahl von int in Bereich 0 bis x
			zufall = irand(0, abzufragende_kategorie->anzahl_in_kategorie);


			help_ptr = abzufragende_kategorie->erste_vokabel;			//Hilfszeiger auf Beginn der Vokabelliste


			for(int x=0; x < (zufall-1); x++) 				//Zeiger jeweils Vielfaches der Zufallszahl Weitersetzen auf die nächsten Listenelemente
			{
				help_ptr = help_ptr->next_vokabel;
			}

			if(help_ptr->flag == 1)										//Wenn ausgewählte Vokabel bereits abgefragt ist
			{
				goto reroll;											//Suche eine neue Vokabel
			}
			else
			{
				help_ptr->flag = 1;  										//Flag der Ausgewählten Vokabel setzen
			}


	//	help_ptr->flag = 1;									  //Flag der Ausgewählten Vokabel setzen

		printf("\nBitte geben sie die Übersetzung von %s ein: ", help_ptr->vokabel_sprache1);  // Aufforderung zur Eingabe
		scanf("%[^\r\n]", eingabe);							//Es können auch Leerzeichen eingegeben werden
		scanf("%c", &dummy_zeichen);										//Leeren des Puffers
			if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}
		strlwr(eingabe);										// Umwandlung lower String; Groß- Kleinschreibung egal!
		if(strcmp(eingabe, help_ptr->vokabel_sprache2) == 0)  //Vergleich der beiden Strings.
			{
				printf("Ihre Eingabe war richtig!\n");			//Ausgabe eines Feedbacks
				anzahl_korrekter_voc++;							// Counter für richtige Vokabeln wird hochgesetzt
			}
		else
			{
				printf("Leider falsch! Korrekte wäre gewesen: %s\n", help_ptr->vokabel_sprache2);   //Feedback mit richtiger Übersetzung
			}

		help_ptr = NULL;	//Zeiger wird wieder geerdet
	}

return(anzahl_korrekter_voc);				//Rückgabe der Richtigen
}
