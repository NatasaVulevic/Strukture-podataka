
/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<ctype.h>
#include<malloc.h>



#define MAX_SIZE (128)
#define MAX_LINE (1024)




typedef struct _student {
	  char ime[MAX_SIZE];
	    char prezime[MAX_SIZE];
	double bodovi;
} ;
int ProcitajBrojRedakaIzDatoteke(  char* nazivDatoteke);
* AlocirajMemorijuProcitajStudente(int brojstudenata,   char* nazivDatoteke);


int main() {
	int i;
	char nazivdatoteke[MAX_SIZE] = { 0 };
	strcpy(nazivdatoteke, "ocjene2.txt");
	int brojstudenata = ProcitajBrojRedakaIzDatoteke(nazivdatoteke);
    printf("broj studenata je: %d\n", brojstudenata);
	* studenti;
	studenti = AlocirajMemorijuProcitajStudente(brojstudenata, nazivdatoteke);
	double max = studenti[0].bodovi;
	for (i = 1; i < brojstudenata; i++)
	{
		if (studenti[i].bodovi > max)
			max = studenti[i].bodovi;
	}
	for (i = 0; i < brojstudenata; i++) {
		printf("%s %s %lf %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, studenti[i].bodovi/max*100);
			}
				
	return 0;
}
int ProcitajBrojRedakaIzDatoteke(  char* nazivDatoteke) {
	int brojac = 0;
	FILE* datoteka=NULL ;
	
	char buffer[MAX_LINE] = { 0 };
	datoteka = fopen(nazivDatoteke, "r");
	if(!datoteka){
		printf("greska u otvaranju datoteke\n");
		return -1;
	}
	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}
	fclose(datoteka);
	return brojac;
}
 * AlocirajMemorijuProcitajStudente(int brojstudenata,  char* nazivDatoteke) {
	int brojac = 0;
	FILE* datoteka=NULL ;
	* studenti=NULL ;
	studenti =( *) malloc(brojstudenata * sizeof());
		
	datoteka= fopen(nazivDatoteke, "r");
	if (!datoteka) {
		printf("greska alociranja\n");
		free(studenti);
		return NULL;
	}
	while (!feof(datoteka)) {
		fscanf(datoteka, "%s%s%lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	fclose(datoteka);
	return studenti;
}
 
