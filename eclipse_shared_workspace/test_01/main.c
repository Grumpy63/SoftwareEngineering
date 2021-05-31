/*
 * usernames.c
 *
 *  Created on: 22.05.2021
 *      Author: Luca Elsesser
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_header.h"

#define SEMIKOLON 59													//Makro zur Übersichtlichkeit; 59 entspricht  Semikolon in ASCII



int main()
{

	struct username *aktueller_nutzer = NULL;

	aktueller_nutzer = usernames();

	printf("Willkommen in der Main %s", aktueller_nutzer->name);
	int a = 0;
	scanf("%s", &a);

	return 0;
}
