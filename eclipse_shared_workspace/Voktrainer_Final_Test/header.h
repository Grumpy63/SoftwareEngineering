/*
 * header.h
 *
 *  Created on: 02.06.2021
 *      Author: David
 */

#ifndef HEADER_H_
#define HEADER_H_

void verzeichnis_auslesen();
struct kategorie *liste_einlesen();
struct kategorie *kategorie_waehlen(struct kategorie *k_alle_erste_ptr);
int vokabelzahl_feststellen(struct kategorie *k_alle_erste_ptr);

struct vokabel{
		char vokabel_sprache1[256];
		char vokabel_sprache2[256];
		int flag;																//wurde Vokabel bereits abgefragt?
		struct vokabel *next_vokabel;											//Pointer für Verkettung der Kategorien
			};

struct kategorie{
		char kategorie_name[256];												//Bezeichnung der Kategorie
		struct vokabel *erste_vokabel;											//pointer auf das erste Vokabel-Paar in der Kategorie
		int anzahl_in_kategorie;												//wieviele Vokabeln befinden sich in der Kategorie
		struct kategorie *next_kategorie;										//Pointer für Verkettung der Kategorien
			};

#endif /* HEADER_H_ */
