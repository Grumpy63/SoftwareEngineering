/*
 * voc_functions.h
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */

#ifndef VOC_FUNCTIONS_H_
#define VOC_FUNCTIONS_H_





	//Definitionen f�r usernames_list() (Luca&Alex)


	//FILE *datei_users_ptr;

	struct username																								//Struct um Nutzernamen zu managen; zur Erstellung von verketteter Liste ben�tigt
	{
		char name[256];																							//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;																				//Pointer zeigt auf n�chsten Nutzer in der verketteten Liste
	};



	struct username *username_list();																			//Deklaration der Funktion username_list()

	//Ende der Deklarationen f�r usernames_list()



	//Definition f�r Liste einlesen, Kategoriewahl, Abfragerichtung, Abfragezahl (David&David)

	struct vokabel																								//Struct zur Erstellung einer verketteten Liste der Vokabeln
	{
		char vokabel_sprache1[256];																				//Variable zum Abspeichern der Vokabel in Sprache 1
		char vokabel_sprache2[256];																				//Variable zum Abspeichern der Vokabel in Sprache 2
		int flag;                                                                								//Variable zum Detektieren ob Vokabel bereits abgefragt; wurde Vokabel bereits abgefragt? 0: nicht abgefragt, 1: abgefragt
		struct vokabel *next_vokabel;                                            								//Pointer f�r Verkettung der Kategorien
	};

	struct kategorie																							//Struct zur Erstellung einer verketteten Liste der Kategorien
	{
		char kategorie_name[256];            																	//Bezeichnung der Kategorie
		struct vokabel *erste_vokabel;   																		//pointer auf das erste Vokabel-Paar in der Kategorie
		int anzahl_in_kategorie;                                                								//wieviele Vokabeln befinden sich in der Kategorie
		struct kategorie *next_kategorie;                                      									//Pointer f�r Verkettung der Kategorien
	};

	struct entitiy_name																							//Struct zur Erstellung einer verketteten Liste der Listennamen
	{
		char name[256];																							//Variable name zum Speichern der Listennamen
		struct entitiy_name *next;																				//Pointer zur Verkettung der entitiy_namen
	};

	struct kategorie *liste_einlesen();																			//Deklaration der Funktion liste_einlesen()
	struct kategorie *kategorie_waehlen(struct kategorie *k_alle_erste_ptr);									//Deklaration der Funktion *kategorie_waehlen()
	int richtung_waehlen();																						//Deklaration der Funktion richtung_waehlen()
	int vokabelzahl_feststellen(struct kategorie *abzufragende_kategorie);										//Deklaration der Funktion vokabelzahl_feststellen()
	struct kategorie *liste_einlesen();																			//Deklaration der Funktion *liste_einlesen()
	int vokabelzahl_feststellen(struct kategorie *k_alle_erste_ptr);											//Deklaration der Funktion vokabelzahl_feststellen()

	//Ende der Definition f�r Abfrage der Vokabeln



	//Deklarationen f�r Vokabelabfrage

	int irand( int a, int e);																					//Deklaration f�r die Funktion irand(); Erzeugt zuf�llige Zahl x mit a<=x<=e

	int abfrage(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc, int modus); 				//Deklaration der Funktion abfrage()
	int abfrage1(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); 						//Deklaration der Funktion abfrage1()
	int abfrage2(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); 						//Deklaration der Funktion abfrage2()
	int abfrage3(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); 						//Deklaration der Funktion abfrage3(); gemischte Abfrage

	//Ende der Deklarationen f�r Vokabelabfrage



	//Definitionen f�r Abfrage der Vokabeln (Luca&Alex&Julian)


	int vokabel_abfrage(int abfrage_modus, int anzahl_abzufragen, struct kategorie *aktuelle_kategorie);		//Funktion fragt so viele Vokabeln aus der �bergebenen Kategorie ab
																												//wie anzahl_abzufragen es befiehlt, und in der Reihenfolge wie der abfrage_modus sagt

	//Ende der Definitionen f�r Abfrage der Vokabeln



	//Definition f�r highscores

	int user_ergebnis(int korrekte_voc, int user_vokabelzahl);
	int highscore_list(struct username *aktueller_nutzer);

	//Ende der Definition f�r highscores



#endif /* VOC_FUNCTIONS_H_ */
