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


	for (int i=0; i<number_abzufragende_voc; i++)				//Schleife für die Abfragezyklen, i ist Laufvariable
	{
		{
			srand(time(NULL));								//Generieren einer Zufallszahl von int in Bereich 0 bis x
			zufall = irand(0,abzufragende_kategorie->anzahl_in_kategorie);


			help_ptr = abzufragende_kategorie->erste_vokabel;			//Hilfszeiger auf Beginn der Vokabelliste


			for(int x=0; x<zufall;x++) 				//Zeiger jeweils Vielfaches der Zufallszahl Weitersetzen auf die nächsten Listenelemente
			{
				help_ptr = help_ptr->next_vokabel;
			}

		} while(help_ptr->flag == 1)  //Prüfen ob Vokabel schon abgefragt wurde, wenn ja beginnt schleife von vorne mit neuer Zufallszahl

		help_ptr->flag =1;  //Flag der Ausgewählten Vokabel setzen

		printf("Bitte geben sie die Übersetzung von %s ein:",help_ptr->vokabel_sprache1);  // Aufforderung zur Eingabe
		scanf("%[^\r\n]", eingabe);							//Es können auch Leerzeichen eingegeben werden
		scanf("%c", &dummy_zeichen);										//Leeren des Puffers
			if(dummy_zeichen == '\r')											//auch auf anderen OS (haben evtl mehr Zeichen)
					{
						scanf("%c", &dummy_zeichen);
					}
		if(strcmp(eingabe, help_ptr->vokabel_sprache2) == 0)  //Vergleich der beiden Strings. Groß/Kleinschreibung spielt noch eine Rolle!!!!
			{
				printf("Ihre Eingabe war richtig!");			//Ausgabe eines Feedbacks
				anzahl_korrekter_voc++;							// Counter für richtige Vokabeln wird hochgesetzt
			}
		else
			{
				printf("Leider falsch! Korrekte wäre gewesen: %s", help_ptr->vokabel_sprache2);   //Feedback mit richtiger Übersetzung
			}

		help_ptr = NULL;	//Zeiger wird wieder geerdet
	}
return(anzahl_korrekter_voc);				//Rückgabe der Richtigen
}
