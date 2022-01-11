/*10. Napisati program koji čita datoteku drzave.txt u kojoj su zapisani nazivi pojedinih država. Uz
ime države u datoteci se nalazi i ime dodatne datoteke u kojoj se nalaze gradovi pojedine
države. Svaka datoteka koja predstavlja državu sadrži popis gradova u formatu naziv_grada,
broj_stanovnika.
					a) Potrebno je formirati sortiranu vezanu listu država po nazivu. Svaki čvor vezane liste
					sadrži stablo gradova sortirano po broju stanovnika, zatim po nazivu grada.

b) Potrebno je formirati stablo država sortirano po nazivu. Svaki čvor stabla sadrži vezanu
listu gradova sortiranu po broju stanovnika, zatim po nazivu grada.
Nakon formiranja podataka potrebno je ispisati države i gradove te omogućiti korisniku putem
tastature pretragu gradova određene države koji imaju broj stanovnika veći od unosa na
tastaturi.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lista* pozl;
struct lista {
	char naziv_grada[256];
	int broj_stanovnika;
	pozl next;
};

typedef struct stablo* poz;
struct stablo {
	char imedrzave[256];
	pozl head;
	pozl head1;
	poz L;
	poz D;
};
poz dodaj_stablo(char* drzava, char* imedatoteke, poz s);
int ispisi_inorder(poz s);


int main() {
	FILE* f;
	char drzava[250];
	char datoteka[256];
	poz s = NULL ;

	f = fopen("drzave.txt", "r");                                  
	if (f == NULL) {
		printf("ne mogu otvoriti drzave.txt");
		return -1;
	}
	while (!feof(f)) {
		fscanf(f, "%s%s", drzava, datoteka);		
		s = dodaj_stablo(drzava, datoteka, s);
	}
	fclose(f);	
	ispisi_inorder(s);

	return 0;
}

poz dodaj_stablo(char* drzava, char* imedatoteke, poz s) {
	FILE* f;
	char naziv_grada1[50] = {};
	int broj_stan;
	
	if (s == NULL) {
		poz s = (poz)malloc(sizeof(struct stablo));
		if (!s) {
			printf("nismo alocirali s");
			return NULL;
		}
		strcpy(s->imedrzave, drzava);
		s->head = (pozl)malloc(sizeof( lista));
		if (!s->head) {
			printf("nismo alocirali s->head");
			return NULL;
		}
		s->head->next = NULL;
		s->head1 = (pozl)malloc(sizeof(lista));
		if (!s->head1) {
			printf("nismo alocirali s->head1");
			return NULL;
		}
		s->head1->next = NULL;
		s->L = NULL;
		s->D = NULL;
		f = fopen(imedatoteke, "r");
		if (f == NULL) {
			printf("ne mogu otvoriti dat");
			return NULL;
		}
		while (!feof(f)) {
			fscanf(f, " %s%d", naziv_grada1, &broj_stan);
		
			pozl a = (pozl)malloc(sizeof(struct lista));
			if (!a) {
				printf("Nismo uspjeli alocirati a");
				return NULL;
			}
			pozl b=	(pozl)malloc(sizeof(struct lista));
			if (!b) {
				printf("Nismo uspjeli alocirati b");
				return NULL;
			}
			strcpy(b->naziv_grada, naziv_grada1);
			b->broj_stanovnika = broj_stan;
			while (s->head1->next != NULL && b->broj_stanovnika > s->head1->next->broj_stanovnika)
				s->head1 = s->head1->next;
			b->next = s->head1->next;
			s->head1->next = b;
			strcpy(a->naziv_grada, naziv_grada1);
			a->broj_stanovnika = broj_stan;
			while (s->head->next != NULL && strcmp(a->naziv_grada, s->head->next->naziv_grada) > 0)
				s->head =s->head->next;
			a->next = s->head->next;
			s->head->next = a;
		}
		fclose(f);
		
	}
	else {
		if (strcmp(drzava, s->imedrzave) < 0)
			s->L = dodaj_stablo(drzava, imedatoteke, s->L);
		if (strcmp(drzava, s->imedrzave) > 0)
			s->D = dodaj_stablo(drzava, imedatoteke, s->D);
		
	}
	return s;

}
		
int ispisi_inorder(poz s) {
	if (s != NULL) {
		if (s->L)
			ispisi_inorder(s->L);
		printf("%s: \n", s->imedrzave);
		while (s->head->next != NULL) {
			printf("%s, %d ", s->head->next->naziv_grada, s->head->next->broj_stanovnika);
			s->head = s->head->next;
		}
		if (s->D)
			ispisi_inorder(s->D);
	}
	return 0;
}
		
		
		
