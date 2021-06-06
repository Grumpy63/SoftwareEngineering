/*
 * Main.c
 *
 *  Created on: 02.06.2021
 *      Author: David
 */
#include <stdio.h>
#include <stdlib.h>
#include "header.h"


int main(){

	verzeichnis_auslesen();

	kategorie_waehlen(liste_einlesen());

	return(0);
}
