/*
 ============================================================================
 Name        : DB_Test01.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {



	FILE * fPointer = NULL;
	//fPointer = fopen("C:/Users/DDevi/Desktop/Desk.txt","r"); // Test case if only files in appdata do not work
	fPointer = fopen("C:\\Users\\DDevi\\AppData\\Local\\GitHubDesktop\\app-2.8.1\\SoftwareEngineering\\Datenablage\\Beispiel_Vokabelliste.txt","r");

	/*Files in APP Data work too, yey
	 *fopen returns 0 if file is not found
	 * BE CAREFUL!!! replace "\" with "\\" or "/"
	 * */

	//stackflow code
	/*char * buffer = 0;
	long length;

	if (fPointer)
	{
	  fseek (fPointer, 0, SEEK_END);
	  length = ftell (fPointer);
	  fseek (fPointer, 0, SEEK_SET);
	  buffer = malloc (length);
	  if (buffer)
	  {
	    fread (buffer, 1, length, fPointer);
	  }
	  fclose (fPointer);
	}

	if (buffer)
	{
		printf(*buffer);
	  // start to process your data / extract strings here...
	}*/

	char singleLine[150];

	while(!feof(fPointer)){
		fgets(singleLine, 150, fPointer);
		//puts(singleLine);
		printf(singleLine);
	}

	fclose(fPointer);

	printf("Test success");


	return 0;
}
