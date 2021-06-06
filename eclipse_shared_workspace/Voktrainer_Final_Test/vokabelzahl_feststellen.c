/*
 * Main.c
 *
 *  Created on: 06.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int vokabelzahl_feststellen(struct kategorie *abzufragende_kategorie){

	printf("\nDie abzufragende Kategorie \"%c\" enthält %d Vokabeln.\n Wie viele möchten sie maximal abgefragt werden ?\n Maximale Anzahl Vokabeln:\n",abzufragende_kategorie->kategorie_name,abzufragende_kategorie->anzahl_in_kategorie);

	int anzahl = 0;

	setbuf(stdout, NULL);
	scanf("%d",anzahl);

	return anzahl;
}

