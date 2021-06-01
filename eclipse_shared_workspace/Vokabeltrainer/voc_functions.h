/*
 * voc_functions.h
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */

#ifndef VOC_FUNCTIONS_H_
#define VOC_FUNCTIONS_H_


	//Definitionen für usernames

	struct username{													//Struct um Nutzernamen zu managen; zur Erstellung von verketteter Liste benötigt
		char name[256];													//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;										//Pointer zeigt auf nächsten Nutzer in der verketteten Liste
	};

	struct username *username_list();									//Deklaration der Funktion username_list()

	//Ende der Definitionen für usernames


#endif /* VOC_FUNCTIONS_H_ */
