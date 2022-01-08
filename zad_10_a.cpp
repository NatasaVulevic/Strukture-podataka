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



typedef struct stablo* poz;
struct stablo {
	char naziv_grada[256] = {};
	int broj_stanovnika;
	poz l;
	poz d;
};

typedef struct lista* pozicija ;
struct lista {	
	char drzava[250];
	poz stablo1 ;
	poz stablo2;
	pozicija next;
};

poz ucitaj_u_stablo1(char* naziv_grada, int broj_stanovnika, poz s);
poz ucitaj_u_stablo2(char* naziv_grada, int broj_stanovnika, poz s);
int dodaj_u_vezanu_listu(char* drzava, pozicija head,char* datoteka);
int print_inorder(poz s);
int ispisiveci(poz s, int el);


int main() {
	FILE* f;
	char drzava[250];
	char datoteka[256];
	int broj;
	char drzava1[250];	

	struct lista head1;	
	head1.drzava ;
	head1.stablo1 = NULL;
	head1.stablo2 = NULL;
	head1.next = NULL ;
	pozicija head = &head1;
			
	
	f = fopen("drzave.txt", "r");
	if (f == NULL) {
		printf("ne mogu otvoriti drzave.txt");
		return - 1;
	}		

	while (!feof(f)) {
		fscanf(f, "%s%s", drzava, datoteka);
		dodaj_u_vezanu_listu(drzava, head, datoteka);
	}
	fclose(f);	
	
	printf("\n");
	
	while (head->next != NULL) {
		printf("\n%s: ", head->next->drzava);
		print_inorder(head->next->stablo1);
		head = head->next;
	}do {
		printf("\nUpisi drzavu koju zelis pretraziti,\nako zelis izaci pritisni 1\n");
		scanf("%s", drzava1);
		if (strcmp(drzava1, "1") == 0)
			break;
		printf("\nUpisi broj stanovnika za koje zelis ispisati vece\n");
		scanf("%d", &broj);
		head = &head1;
		while (head->next != NULL && strcmp(head->next->drzava, drzava1) != 0)
			head = head->next;
		if (head->next == NULL) {
			printf("Nema trazene drzave\n");
			continue;
		}
		if (!strcmp(head->next->drzava, drzava1)) {

			ispisiveci(head->next->stablo2, broj);
		}
		
	} while (1);	

	return 0;
}

poz ucitaj_u_stablo1( char* naziv_grada,int broj_stanovnika, poz s) {
	
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
				s->l = ucitaj_u_stablo1(naziv_grada,broj_stanovnika, s->l);
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
		if (broj_stanovnika< s->broj_stanovnika)
			s->l = ucitaj_u_stablo2(naziv_grada, broj_stanovnika, s->l);
		if (broj_stanovnika>= s->broj_stanovnika)
			s->d = ucitaj_u_stablo1(naziv_grada, broj_stanovnika, s->d);
		return s;
	}
}
int dodaj_u_vezanu_listu(char* drzava , pozicija head,char*datoteka) {
	FILE* f;
	char grad[50] = {};
	int br_stan = 0;
	pozicija q = (pozicija)malloc(sizeof(lista));
	if (!q) {
		printf("nismo alocirali memoriju\n");
		return -2;
	}	

	strcpy(q->drzava, drzava);

	q->stablo1 = NULL;
	q->stablo2 = NULL;	

	f = fopen(datoteka, "r");
	if (f == NULL) {
		printf("ne mogu otvoriti dat\n");
		return -1;
	}
	while (!feof(f)) {
		fscanf(f, " %s %d", grad, &br_stan);
		q->stablo1 = ucitaj_u_stablo1(grad, br_stan, q->stablo1);
		q->stablo2 = ucitaj_u_stablo2(grad, br_stan, q->stablo2);
	}
	fclose(f);

	while (head->next != NULL&& strcmp(drzava,head->next->drzava)>0) 
		head = head->next;	
		q->next = head->next;
		head->next = q;
	
	return 0;	
}
int print_inorder(poz s) {
	if (s != NULL) {
		print_inorder(s->l);
		printf("%s %d, ", s->naziv_grada,s->broj_stanovnika);
		print_inorder(s->d);
	}
	return 0;
}

int ispisiveci(poz s, int el) {
	if (s == NULL)
		return 0;
	else {
		if (s->broj_stanovnika > el) {
			printf("%d ", s->broj_stanovnika);
			 ispisiveci(s->d, el);
			 ispisiveci(s->l, el);
		}
		else {
			ispisiveci(s->l,el);
		}
	}
	return 0 ;
}