/*
 * highscorce.c
 *
 *  Created on: 09.06.2021
 *      Author: Luca
 */


#include <stdio.h>
#include <stdlib.h>
#include "voc_functions.h"





int user_ergebnis(int korrekte_voc, int user_vokabelzahl)
{
	float prozentual = 0.0;

	printf("\n\nAnzahl Korrekter Eingaben: %d von %d", korrekte_voc, user_vokabelzahl);

	prozentual =  (float) korrekte_voc / user_vokabelzahl * 100;

	printf(" dies entspricht %.2f Prozent", prozentual);

	return 0;
}





int highscore_list(struct username *aktueller_nutzer)
{


	return 0;
}
