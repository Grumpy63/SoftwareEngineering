/*
 * test_header.h
 *
 *  Created on: 31.05.2021
 *      Author: Luca
 */

#ifndef TEST_HEADER_H_
#define TEST_HEADER_H_


struct username{													//Struct um Nutzernamen zu managen; zur Erstellung von verketteter Liste benötigt
		char name[256];													//Nutzername mit Begrenzung auf 256 Zeichen
		struct username *next_user;										//Pointer zeigt auf nächsten Nutzer in der verketteten Liste
	};

struct username *usernames();

#endif /* TEST_HEADER_H_ */
