/*
 * kategorie_waehlen.c
 *
 *  Created on: 06.06.2021
 *      Author: David
 */

#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>
#include "voc_functions.h"

struct kategorie *kategorie_waehlen(struct kategorie *k_alle_erste_ptr)
{
	struct kategorie *rueckgabe_help_ptr = NULL;
	int i_max = 1;
	int i = 1;
	int a = 1;

	setbuf(stdout, NULL);
	if(k_alle_erste_ptr->next_kategorie == NULL)
	{
		printf("Kategorie %s wird abgefragt.\n\n", k_alle_erste_ptr->kategorie_name);
		return(k_alle_erste_ptr);
	}
	else if(k_alle_erste_ptr->next_kategorie->next_kategorie == NULL)
	{
		printf("Kategorie %s wird abgefragt.\n\n", k_alle_erste_ptr->next_kategorie->kategorie_name);
		return(k_alle_erste_ptr->next_kategorie);
	}

	printf("\nFolgende Kategorien koennen gewaehlt werden: \n");

	rueckgabe_help_ptr = k_alle_erste_ptr;

	while(rueckgabe_help_ptr != NULL)
	{
		printf("(%d) %s\n", i, rueckgabe_help_ptr->kategorie_name);
		i++;
		rueckgabe_help_ptr = rueckgabe_help_ptr->next_kategorie;
	}

	i_max = i-1;

	while(1){
		printf("\nZur Auswahl bitte die Nummer der Kategorie eingeben:\n");
		scanf("%d", &i);
		fflush(stdin);
		if(i<1 || i>i_max){
			printf("Ungueltige Eingabe. Waehlen Sie bitte eine Kategorie mit einer Eingabe zwischen 1 und %d.\n",i_max);
		}
		else{
			break;
		}
	}


	rueckgabe_help_ptr = k_alle_erste_ptr;


	while(a != i)
	{
		rueckgabe_help_ptr = rueckgabe_help_ptr->next_kategorie;
		a++;
	}

	//printf("\nSie haben sich erfolgreich für die Kategorie \"%s\" entschieden!\n\n",rueckgabe_help_ptr->kategorie_name);//brauchen wir nicht ? hmmmm

	return(rueckgabe_help_ptr);
}
