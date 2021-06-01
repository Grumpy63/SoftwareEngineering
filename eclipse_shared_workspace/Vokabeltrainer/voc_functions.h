/*
 * voc_functions.h
 *
 *  Created on: 22.05.2021
 *      Author: Luca
 */

#ifndef VOC_FUNCTIONS_H_
#define VOC_FUNCTIONS_H_


	//Definitionen f�r usernames

	struct username{													//Struct um Nutzernamen zu managen; zur Erstellung von verketteter Liste ben�tigt
		char name[256];													//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;										//Pointer zeigt auf n�chsten Nutzer in der verketteten Liste
	};

	struct username *username_list();									//Deklaration der Funktion username_list()

	//Ende der Definitionen f�r usernames


#endif /* VOC_FUNCTIONS_H_ */
