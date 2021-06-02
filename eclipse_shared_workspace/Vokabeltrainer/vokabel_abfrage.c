/*
 * vokabel_abfrage.c
 *
 *  Created on: 02.06.2021
 *      Author: Luca
 */


int vokabel_abfrage(int abfrage_modus, int anzahl_abzufragen, struct kategorie *aktuelle_kategorie){



	for(int anzahl_abgefragt = 0; anzahl_abgefragt<anzahl_abzufragen; anzahl_abgefragt++)
	{

		switch(abfrage_modus){
			case 0:
				printf("Abfrage von Sprache 1 zu Sprache 2");
				 vokabel_abfrage_s1zus2(*aktuelle_kategorie);
				break;

			case 1:
				printf("Abfrage von Sprache 2 zu Sprache 1");
				break;

			case 2:
				printf("Gemischte Abfrage von Sprache 1 zu Sprache 2 und umgekehrt");
				break;

			default:
				printf("Kein gültiger Abfrage Modus");
				return 0;
		}








	}




	return 0;
}
