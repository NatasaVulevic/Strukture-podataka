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

typedef struct listag* pozl;
struct listag {
	char naziv_grada[256];
	int broj_stanovnika;
	pozl next;
};

typedef struct stablodrzava* pozsd;
struct stablodrzava {
	char imedrzave[256];
	pozl headl;
	char imedatoteke[256];
	pozsd L;
	pozsd D;
};
int print_inorder2(pozsd s3);
pozsd dodaj_stablodrzava1(char* drzava, char* imedatoteke, pozsd s3);

int main() {
	FILE* f;
	int broj;
	char drzava[250];
	char datoteka[256];
	pozsd s3 = NULL;

	f = fopen("drzave.txt", "r");                                    //  f3
	if (f == NULL) {
		printf("ne mogu otvoriti drzave.txt");
		return -1;
	}
	while (!feof(f)) {
		fscanf(f, "%s%s", drzava, datoteka);
		s3 = dodaj_stablodrzava1(drzava, datoteka, s3);
	}
	fclose(f);
	print_inorder2(s3);
	printf("Unesi broj za kojeg zelis drzave s vecim brojem stanovnika\n");
	scanf("%d", &broj);

	return 0;
}

pozsd dodaj_stablodrzava1(char* drzava, char* imedatoteke, pozsd s3) {
	FILE* f;
	char* naziv_grada1 = {};
	int broj_stan;
	if (s3 == NULL) {
		pozsd s3 = (pozsd)malloc(sizeof(stablodrzava));
		strcpy(s3->imedrzave, drzava);
		pozl p = (pozl)malloc(sizeof(listag));
		s3->headl = p;
		s3->headl->next = NULL;
		f = fopen(imedatoteke, "r");
		if (f == NULL) {
			printf("ne mogu otvoriti dat");
			return NULL;                                            //break;
		}
		while (!feof(f)) {
			fscanf(f, " %s %d", naziv_grada1, &broj_stan);
			pozl a = (pozl)malloc(sizeof(listag));
			strcpy(a->naziv_grada, naziv_grada1);
			a->broj_stanovnika = broj_stan;
			while (s3->headl->next != NULL && s3->headl->next->broj_stanovnika < a->broj_stanovnika)
				s3->headl = s3->headl->next;
			
				a->next = s3->headl->next;
				s3->headl->next = a->next;
		}
	}

	else {
		if (strcmp(drzava, s3->imedrzave) < 0)
			s3->L = dodaj_stablodrzava1(drzava, imedatoteke, s3->L);
		if (strcmp(drzava, s3->imedrzave) > 0)
			s3->D = dodaj_stablodrzava1(drzava, imedatoteke, s3->D);
	}
	return s3;
}
int print_inorder2(pozsd s3) {
	if (s3 != NULL) {
		print_inorder2(s3->L);
		printf("%s ", s3->imedrzave);
		/*while (s3->headl->next != NULL) {
			printf("%s%d", s3->headl->next->naziv_grada, &s3->headl->next->broj_stanovnika);
			s3->headl = s3->headl->next;
		}*/
		print_inorder2(s3->D);
	}
	return 0;
}