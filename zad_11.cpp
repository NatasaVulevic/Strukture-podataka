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
struct stablo {
	char naziv_grada[256] = {};
	int broj_stanovnika;
	poz l;
	poz d;
};
typedef struct hashtab* pozhashtab;
struct hashtab{
	pozicija tablica[11];
};

int racunaj_index(char* drzava);
int  dodaj(int index, pozhashtab hash, char* drzava, char* datoteka);
poz ucitaj_u_stablo1(char* naziv_grada, int broj_stanovnika, poz s);
poz ucitaj_u_stablo2(char* naziv_grada, int broj_stanovnika, poz s);
int ispisi_drzave(pozhashtab hash, int index);


int main() {
	char drzava[250];
	char datoteka[256];
	FILE* f;
	int i,b;
	

	pozhashtab hash=(pozhashtab)malloc(sizeof(struct hashtab));

	if (!hash) {
		printf("neuspjela alokacija");
		return -1;
	}
	
	for (i = 0; i < 11; i++) {
		//hash->tablica[i]->drzava = {};
		hash->tablica[i]->stablo1 = NULL;
		hash->tablica[i]->stablo2 = NULL;
		hash->tablica[i]->next = NULL;
	}


	printf("1");
	f = fopen("drzave.txt", "r");
	if (f == NULL) {
		printf("ne mogu otvoriti drzave.txt");
		return -1;
	}

	while (!feof(f)) {
		fscanf(f, "%s%s", drzava, datoteka);
		b = racunaj_index(drzava);
		printf("%d", b);
		dodaj(b, hash, drzava, datoteka);
	}
	for (i = 0; i < 11; i++) {
		ispisi_drzave(hash, i);
	}

	

	return 0;
}


int racunaj_index(char* drzava) {
	int a = 0, i, b;
	for (i = 0; i < 5; i++) {
		a += (int)drzava[i];
	}
	b = a % 11;
	return b;
}

int  dodaj(int index, pozhashtab hash, char* drzava, char* datoteka){
	FILE* f;
	char* naziv_grada = {};
	int broj_stan;
	pozicija a = (pozicija)malloc(sizeof lista);
	strcpy(a->drzava, drzava);
	a->stablo1 = NULL;
	a->stablo2 = NULL;
	f = fopen(datoteka, "r"); 
	if (f == NULL) {
		printf("ne mogu otvoriti dat\n");
		return -1;
	}
	while (!feof(f)) {
		fscanf(f,"%s %d", naziv_grada, &broj_stan);
		a->stablo1 = ucitaj_u_stablo1(naziv_grada, broj_stan, a->stablo1);
		a->stablo2 = ucitaj_u_stablo1(naziv_grada, broj_stan, a->stablo2);

	}
	
	a->next = hash->tablica[index]->next;
	hash->tablica[index]->next = a;

	return 0;
}

poz ucitaj_u_stablo1(char* naziv_grada, int broj_stanovnika, poz s) {

	if (s == NULL) {
		s = (poz)malloc(sizeof(stablo));
		strcpy(s->naziv_grada, naziv_grada);
		s->broj_stanovnika = broj_stanovnika;
		s->l = NULL;
		s->d = NULL;
		return s;
	}
	else {
		if (strcmp(naziv_grada, s->naziv_grada) < 0)
			s->l = ucitaj_u_stablo1(naziv_grada, broj_stanovnika, s->l);
		if (strcmp(naziv_grada, s->naziv_grada) > 0)
			s->d = ucitaj_u_stablo1(naziv_grada, broj_stanovnika, s->d);
		return s;
	}
}

poz ucitaj_u_stablo2(char* naziv_grada, int broj_stanovnika, poz s) {

	if (s == NULL) {
		s = (poz)malloc(sizeof(stablo));
		strcpy(s->naziv_grada, naziv_grada);
		s->broj_stanovnika = broj_stanovnika;
		s->l = NULL;
		s->d = NULL;
		return s;
	}
	else {
		if (broj_stanovnika < s->broj_stanovnika)
			s->l = ucitaj_u_stablo2(naziv_grada, broj_stanovnika, s->l);
		if (broj_stanovnika >= s->broj_stanovnika)
			s->d = ucitaj_u_stablo1(naziv_grada, broj_stanovnika, s->d);
		return s;
	}
}
int ispisi_drzave(pozhashtab hash, int index) {
	if (hash->tablica[index]->next == NULL)
		printf("Nema drzave na trazenom mjestu\n");
	while (hash->tablica[index]->next != NULL) {
		printf(" %s ", hash->tablica[index]->next->drzava);
		hash->tablica[index] = hash->tablica[index]->next;
	}
	return 0;

}
