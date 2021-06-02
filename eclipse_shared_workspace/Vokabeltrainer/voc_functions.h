/*
 * voc_functions.h
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */

#ifndef VOC_FUNCTIONS_H_
#define VOC_FUNCTIONS_H_


	//Definitionen f�r usernames_list()

	struct username{													//Struct um Nutzernamen zu managen; zur Erstellung von verketteter Liste ben�tigt
		char name[256];													//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;										//Pointer zeigt auf n�chsten Nutzer in der verketteten Liste
	};

	struct username *username_list();									//Deklaration der Funktion username_list()

	//Ende der Definitionen f�r usernames_list()



	//Definitionen f�r Abfrage der Vokabeln

	struct vokabel{
		char vokabel_sprache1[256];
		char vokabel_sprache2[256];
		int flag;														//wurde Vokabel bereits abgefragt?
		struct vokabel *next_vokabel;									//Pointer f�r Verkettung der Kategorien
			};

	struct kategorie{
		char kategorie_name[256];										//Bezeichnung der Kategorie
		struct vokabel *erste_vokabel;									//pointer auf das erste Vokabel-Paar in der Kategorie
		int anzahl_in_kategorie;										//wieviele Vokabeln befinden sich in der Kategorie
		struct kategorie *next_kategorie;								//Pointer f�r Verkettung der Kategorien
			};

	void vokabel_abfrage(int anzahl_abzufragen, struct kategorie *aktuelle_kategorie);			//Funktion fragt so viele Vokabeln aus der �bergebenen Kategorie ab wie anzahl_abzufragen es befiehlt

	//Ende der Definitionen f�r Abfrage der Vokabeln


#endif /* VOC_FUNCTIONS_H_ */
