/*9. Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u čvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraća
pokazivač na korijen stabla.
b) Napisati funkciju replace koja će svaki element stabla zamijeniti sumom elemenata u
njegovom lijevom i desnom podstablu (tj. sumom svih potomaka prije zamjene
vrijednosti u tim potomcima). Npr. stablo sa slike Slika 1 transformirat će se u stablo na
slici Slika 2.
c) Prepraviti program na način da umjesto predefiniranog cjelobrojnog polja korištenjem
funkcije rand() generira slučajne brojeve u rasponu <10, 90>. Također, potrebno je
upisati u datoteku sve brojeve u inorder prolasku nakon korištenja funkcije iz a), zatim b)
dijela zadatka.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct stablo* pozicija;
struct stablo {
	int el;
	pozicija l;
	pozicija d;

};
int zamijeni(pozicija s);
pozicija insert(pozicija s, int x){
	if (s == NULL) {
		s = (pozicija)malloc(sizeof(stablo));
		if (s == NULL){
			printf("Greska\n");
			return NULL; }
		s->el = x;
		s->l = NULL;
		s->d = NULL;
	}
	else {
		if (x >= s->el)
			s->l = insert(s->l, x);
		if(x< s->el)
			s->d = insert(s->d, x);
		
	}
	return s;

}
int print_inorder(pozicija s ) {
	
	if (s != NULL) {
		print_inorder(s->l);
		printf("%d ", s->el);
		
		print_inorder(s->d);
	}	
	return 0;
}

int print_inorder_u_dat(pozicija s, FILE* f) {

	if (s != NULL) {
		print_inorder_u_dat(s->l,f );
		fputc(s->el, f);
		print_inorder_u_dat(s->d,f);
	}

	return 0;
}
pozicija brisi_sve(pozicija s) {
	if (s != NULL) {
		brisi_sve(s->l);
		brisi_sve(s->d);
		free(s);
	}
	else
		return NULL;	
}

int main() {
	srand((unsigned)time(NULL));
	pozicija s = NULL;
	int i;
	int c=0,c1=0;
	FILE* f;
	FILE* f1;
	f = fopen("natasa.txt", "w");
	if (!f) {
		printf("ne mogu otvoriti datoteku");
		return 0;
	}
	f1 = fopen("natasa1.txt", "w");
	if (!f1) {
		printf("ne mogu otvoriti datoteku");
		return 0;
	}
	s=insert(s, 2);
	s = insert(s, 5);
	s = insert(s, 7);
	s = insert(s, 8);
	s = insert(s, 11);
	s = insert(s, 1);
	s = insert(s, 4);
    s = insert(s, 2);
	s = insert(s, 3);
	s = insert(s, 7);
	print_inorder(s);
	printf("\n");	
	print_inorder_u_dat(s, f);
	fclose(f);
	zamijeni(s);	
	print_inorder(s);	
	printf("\n");

	print_inorder_u_dat(s, f1);
    fclose(f1);
	s=brisi_sve(s);	
	
	for(i=0;i<10;i++)
	s = insert(s, rand()%81+10);
	printf("Ispis stabla sa random brojevima\n");
	print_inorder(s);
	printf("\n");  	
	
	printf("\nCitanje sadrzaja prve dat\n");
	f = fopen("natasa.txt", "r");
	if (!f) {
		printf("ne mogu otvoriti datoteku\n");
		return 0;
	}
	while (c != EOF) {
		c = getc(f);
		printf("%d ", c);
	}
	printf("\n");
	fclose(f);

	printf("\nCitanje sadrzaja druge datoteke\n");
	f1 = fopen("natasa1.txt", "r");
	if (!f) {
		printf("ne mogu otvoriti datoteku\n");
		return 0;
	}
	while (c1 != EOF) {
		c1 = getc(f);
		printf("%d ", c1);
	}
	printf("\n");
	fclose(f1);

	return 0;
}


int zamijeni(pozicija s) {
	int temp1 = 0, temp2 = 0, temp11 = 0, temp22 = 0;
	if (s != NULL) {
		if (s->l)
			temp1 = s->l->el;
		else
			temp1 = 0;
		if (s->d)
			temp2 = s->d->el;
		else
			temp2 = 0;
		zamijeni(s->l);
		zamijeni(s->d);
		if (s->l)
			temp11 = s->l->el;
		if (s->d)
			temp11 = s->d->el;

		s->el = temp1 + temp2 + temp11 + temp22;
		return s->el;
	}
	else
		return 0;
}




		






