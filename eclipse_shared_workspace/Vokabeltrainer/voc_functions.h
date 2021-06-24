/*
 * voc_functions.h
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */

#ifndef VOC_FUNCTIONS_H_
#define VOC_FUNCTIONS_H_





	//Definitionen für usernames_list() (Luca&Alex)


	//FILE *datei_users_ptr;

	struct username																								//Struct um Nutzernamen zu managen; zur Erstellung von verketteter Liste benötigt
	{
		char name[256];																							//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;																				//Pointer zeigt auf nächsten Nutzer in der verketteten Liste
	};



	struct username *username_list();																			//Deklaration der Funktion username_list()

	//Ende der Deklarationen für usernames_list()



	//Definition für Liste einlesen, Kategoriewahl, Abfragerichtung, Abfragezahl (David&David)

	struct vokabel																								//Struct zur Erstellung einer verketteten Liste der Vokabeln
	{
		char vokabel_sprache1[256];																				//Variable zum Abspeichern der Vokabel in Sprache 1
		char vokabel_sprache2[256];																				//Variable zum Abspeichern der Vokabel in Sprache 2
		int flag;                                                                								//Variable zum Detektieren ob Vokabel bereits abgefragt; wurde Vokabel bereits abgefragt? 0: nicht abgefragt, 1: abgefragt
		struct vokabel *next_vokabel;                                            								//Pointer für Verkettung der Kategorien
	};

	struct kategorie																							//Struct zur Erstellung einer verketteten Liste der Kategorien
	{
		char kategorie_name[256];            																	//Bezeichnung der Kategorie
		struct vokabel *erste_vokabel;   																		//pointer auf das erste Vokabel-Paar in der Kategorie
		int anzahl_in_kategorie;                                                								//wieviele Vokabeln befinden sich in der Kategorie
		struct kategorie *next_kategorie;                                      									//Pointer für Verkettung der Kategorien
	};

	struct entitiy_name																							//Struct zur Erstellung einer verketteten Liste der Listennamen
	{
		char name[256];																							//Variable name zum Speichern der Listennamen
		struct entitiy_name *next;																				//Pointer zur Verkettung der entitiy_namen
	};

	struct kategorie *liste_einlesen(struct vokabel * sprache);													//Deklaration der Funktion liste_einlesen()
	struct kategorie *kategorie_waehlen(struct kategorie *k_alle_erste_ptr);				//Deklaration der Funktion *kategorie_waehlen()
	int richtung_waehlen(struct vokabel * sprache);																//Deklaration der Funktion richtung_waehlen()
	int vokabelzahl_feststellen(struct kategorie *abzufragende_kategorie);										//Deklaration der Funktion vokabelzahl_feststellen()
	struct kategorie *liste_einlesen();																			//Deklaration der Funktion *liste_einlesen()
	int vokabelzahl_feststellen(struct kategorie *k_alle_erste_ptr);											//Deklaration der Funktion vokabelzahl_feststellen()

	//Ende der Definition für Abfrage der Vokabeln



	//Deklarationen für Vokabelabfrage

	int irand( int a, int e);																					//Deklaration für die Funktion irand(); Erzeugt zufällige Zahl x mit a<=x<=e

	int abfrage(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc, int modus); 				//Deklaration der Funktion abfrage()
	int abfrage1(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); 						//Deklaration der Funktion abfrage1()
	int abfrage2(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); 						//Deklaration der Funktion abfrage2()
	int abfrage3(struct kategorie* abzufragende_kategorie, int number_abzufragende_voc); 						//Deklaration der Funktion abfrage3(); gemischte Abfrage

	//Ende der Deklarationen für Vokabelabfrage



	//Definitionen für Abfrage der Vokabeln (Luca&Alex&Julian)


	int vokabel_abfrage(int abfrage_modus, int anzahl_abzufragen, struct kategorie *aktuelle_kategorie);		//Funktion fragt so viele Vokabeln aus der Übergebenen Kategorie ab
																												//wie anzahl_abzufragen es befiehlt, und in der Reihenfolge wie der abfrage_modus sagt

	//Ende der Definitionen für Abfrage der Vokabeln



	//Definition für highscores


	struct user_and_score																						//struct für das handling der highscores
	{
		char username[256];
		float score;
		struct user_and_score *next;
	};

	int user_ergebnis(int korrekte_voc, int user_vokabelzahl);													//Gibt das aktuelle Ergebnis des Nutzers aus
	int highscore_list(struct username *aktueller_nutzer, int korrekte_voc, int user_vokabelzahl);				//Sortiert das aktuelle Ergebnis des Nutzers in die bestehenden scores ein und schreibt sie in die Highscorelist.txt
	int ausgabe_scoreliste(struct user_and_score *ptr_scoreliste);												//Gibt verkettete Liste von user&score auf dem Bildschirm aus (wird in fkt highscore_list aufgerufen)


	//Ende der Definition für highscores



#endif /* VOC_FUNCTIONS_H_ */
