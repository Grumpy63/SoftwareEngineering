/*
 * main.c
 *
 *  Created on: 13.05.2021
 *      Author: Luca
 */

#include <stdio.h>

int main(void)
{

	setbuf(stdout, NULL);


	int a = 0;

	printf("Hello World, bitte gib eine Zahl ein: ");

	scanf("%d", &a);

	printf("Die Zahl lautet %d.", a);

	return 0;
}
