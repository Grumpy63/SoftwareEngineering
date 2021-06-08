/*
 * voc_functions.h
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */

#ifndef VOC_FUNCTIONS_H_
#define VOC_FUNCTIONS_H_


	//Deklarationen für usernames_list()

	struct username{													//Struct um Nutzernamen zu managen; zur Erstellung von verketteter Liste benötigt
		char name[256];													//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;										//Pointer zeigt auf nächsten Nutzer in der verketteten Liste
	};



	struct username *username_list();									//Deklaration der Funktion username_list()

	//Ende der Deklarationen für usernames_list()


	//Deklarationen für Vokabelabfrage

	struct vokabel
	{
		char vokabel_sprache1[256];
		char vokabel_sprache2[256];
		int flag;                                                                //wurde Vokabel bereits abgefragt? 0: nicht abgefragt, 1: abgefragt
		struct vokabel *next_vokabel;                                            //Pointer für Verkettung der Kategorien
	};

	struct kategorie
	{
		char kategorie_name[256];            									//Bezeichnung der Kategorie
		struct vokabel *erste_vokabel;   										//pointer auf das erste Vokabel-Paar in der Kategorie
		int anzahl_in_kategorie;                                                //wieviele Vokabeln befinden sich in der Kategorie
		struct kategorie *next_kategorie;                                       //Pointer für Verkettung der Kategorien
	};

	int irand( int a, int e);				//Deklaration für die Funktion irand()

	int abfrage(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc, int modus); //Deklaration der Funktion abfrage()
	int abfrage1(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); //Deklaration der Funktion abfrage1()
	int abfrage2(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); //Deklaration der Funktion abfrage2()

	//Ende der Deklarationen für Vokabelabfrage


#endif /* VOC_FUNCTIONS_H_ */
