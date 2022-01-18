/*11. Prepraviti zadatak 10 na način da se formira hash tablica država. Tablica ima 11 mjesta, a
funkcija za preslikavanje ključ računa da se zbraja ASCII vrijednost prvih pet slova države zatim
računa ostatak cjelobrojnog dijeljenja te vrijednosti s veličinom tablice. Države s istim ključem se
pohranjuju u vezanu listu sortiranu po nazivu države. Svaki čvor vezane liste sadrži stablo
gradova sortirano po broju stanovnika, zatim po nazivu grada.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct stablo* poz;
typedef struct lista* pozicija;
struct lista {
	char drzava[250];
	poz stablo1;
	poz stablo2;
	pozicija next;
};
typedef struct hash* hashtab;
struct hash {
	int veltab;
	pozicija* hashliste;
};



struct stablo {
	char naziv_grada[256] = {};
	int broj_stanovnika;
	poz l;
	poz d;
};


void  dodaj(int index, hashtab H, char* drzava);
int racunaj_index(char* drzava);
int ispisi_drzavu(int index, hashtab H);

int main() {
	char drzava[250];
	char datoteka[256];
	int i,b;
	FILE* f;

	hashtab H;
	H = (hashtab)malloc(sizeof(struct hash));
	if (!H) {
		printf("Greska kod init tablice");
		return - 1;
	}
	H->veltab = 11;
	H->hashliste=(pozicija*) malloc(sizeof(struct lista)*11);
	if (!H->hashliste) {
		printf("Greska kod init hashliste");
		return -1;
	}
	for (i = 0; i < 11; i++)
		H->hashliste[i]->next = NULL;




	f = fopen("drzave.txt", "r");
	if (f == NULL) {
		printf("ne mogu otvoriti drzave.txt");
		return -1;
	}

	while (!feof(f)) {
		fscanf(f, "%s%s", drzava, datoteka);
		b = racunaj_index(drzava);
		dodaj(b, H, drzava);
	}
	fclose(f);
	ispisi_drzavu(1, H);

	return 0;
}

void  dodaj(int index, hashtab H,char *drzava) {
	pozicija lista1;
	lista1 = (pozicija)malloc(sizeof(struct lista));
	strcpy(lista1->drzava, drzava);
	lista1->stablo1 =(poz) malloc(sizeof(struct stablo));
	lista1->stablo2 = (poz)malloc(sizeof(struct stablo));
	lista1->next = H->hashliste[index]->next;
	H->hashliste[index]->next = lista1;


}
int racunaj_index(char* drzava) {
	int a=0,i,b;
	for (i = 0; i < 5; i++) {
		a += (int)drzava[i];
	}
	b = a % 11;
	return b;
}
int ispisi_drzavu( int index,hashtab H) {
	while (H->hashliste[index]->next != NULL) {
		printf("%s", H->hashliste[index]->next->drzava);
		H->hashliste[index] = H->hashliste[index]->next;
	}


	return 0;
}
