/* Definirati strukturu osoba(ime, prezime, godina rođenja) i napisati program koji :
A.dinamički dodaje novi element na početak liste,
B.ispisuje listu,
C.dinamički dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#define MAX 1024

typedef struct _osoba {
	char ime[MAX];
	char prezime[MAX];
	int godina;

	struct _osoba* next;
}osoba;

int unospocetak(osoba* head);
int ispis(osoba* head);
int ispis(osoba* head);
int unoskraj(osoba* head);
osoba* pronadizadnji(osoba* head);
osoba* pronadiprezime(osoba* head, char* prezime);
osoba* pronadipredhodni(osoba* head, osoba* x);
int obrisi(osoba* head, osoba* x);
int dodajiza(osoba* head, osoba* x);
int dodajispred(osoba* head, osoba* x);




int main() {
	osoba* head;
	head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;
		
	int izbor = 0;
	
	char prezime[MAX],prezime2[MAX];
	osoba* nadiprezime = NULL;
	osoba* obrisiel = NULL;
	nadiprezime = (osoba*)malloc(sizeof(osoba));
	obrisiel = (osoba*)malloc(sizeof(osoba));
	osoba* prez=NULL;

	printf("**********\n");
	printf("1-unos na pocetak\n");
	printf("2-unos na kraj\n");
	printf("3-ispis\n");
	printf("4-pronadi po prezimenu\n");
	printf("5-izbrisi prezime\n");
	printf("6-dodaj nakon\n");
	printf("7-dodaj ispred\n");
	printf("0-iskljuci program\n");
	printf("\n**********\n");

	while (1) {
		printf("\nizaberite zeljenu opciju unosom broja\n");
		scanf("%d", &izbor);
		switch (izbor) {
		case (1):unospocetak(head);
			break;
		case (2):unoskraj(head);
			break;
		case (3):ispis(head);
			break;
		case (4):
			printf("koje prezime zelite pronaci\n");
			scanf("%s", prezime);
			nadiprezime = pronadiprezime(head, prezime);
			printf("element koji trazite je %s\n %s\n %d\n", nadiprezime->ime, nadiprezime->prezime, nadiprezime->godina);
			break;
		case (5):
			printf("koje prezime zelite izbrisati\n");
			scanf(" %s", prezime2);
			obrisiel = pronadiprezime(head, prezime2);
			obrisi(head, obrisiel);
			break;
		case(6):
			printf("iza kojeg prezimena zelite dodati\n");
			scanf("%s", prezime);
			prez = pronadiprezime(head, prezime);
			dodajiza(head, prez);
			break;
		case(7):
			printf("ispred kojeg prezimena zelite dodati\n");
			scanf("%s", prezime);
			prez = pronadiprezime(head, prezime);
			dodajispred(head, prez);
			break;
		case(0):
			return 0;

		default:printf("krivi unos.pokusajte ponovno\n");
		}

	}
	return 0;
	}


	

int unospocetak(osoba* head) {
	osoba * o;
	o = (osoba*)malloc(sizeof(osoba));
	o->next = head->next;
	head->next = o;
	printf("unesi ime\n");
	scanf(" %s", o->ime);
	printf("unesi prezime\n");
	scanf(" %s", o->prezime);
	printf("unesi godinu rodenja\n");
	scanf(" %d", &o->godina);
	return 0;
}

int ispis(osoba* head) {
	osoba* o = head->next;
	while (o != NULL) {
		printf("Ime: %s\n,prezime: %s\n,godina rodenja: %d\n", o->ime, o->prezime, o->godina);
		o=o->next;
	}
	return 0;
}

int unoskraj(osoba* head) {
	osoba* o, * z;
	o= (osoba*)malloc(sizeof(osoba));
	z = (osoba*)malloc(sizeof(osoba));
	z = pronadizadnji(head);
	o->next = z -> next;
	z->next = o;
	printf("Unesite ime\n", o->ime);
	scanf(" %s", o->ime);
	printf("unesi prezime\n");
	scanf(" %s", o->prezime);
	printf("unesi godinu rodenja\n");
	scanf(" %d", &o->godina);
	
	return 0;
}
osoba* pronadizadnji(osoba* head) {
	osoba* o = head;
	while (o != NULL && o->next != NULL)
		o = o->next;
	return o;
}
osoba* pronadiprezime(osoba*head, char* prezime) {
	osoba* o = head->next;
	while (o != NULL && strcmp(o->prezime, prezime))
		o = o->next;
	return o;
}
osoba* pronadipredhodni(osoba *head,osoba *x) {
	osoba* o = head;
	while (o != NULL && o->next != x)
		o = o->next;
	return o;

}
int obrisi(osoba*head,osoba* x) {
	osoba * p = NULL, *q=NULL;
	p=(osoba*)malloc(sizeof(osoba));
	q = (osoba*)malloc(sizeof(osoba));
	q = x;
	p = pronadipredhodni(head, x);
	p -> next = x ->next;
	free(q);
	return 0;
}
int dodajiza(osoba*head, osoba*x) 
{
	osoba* p = head;
	osoba* q = NULL;
	q = (osoba*)malloc(sizeof(osoba));

	printf("upisi ime osobe koju dodajes\n");
	scanf("%s", q->ime);
	printf("upisi prezime osobe koju dodajes\n");
	scanf("%s", q->prezime);
	printf("upisi godinu rodenja osobe koju dodajes\n");
	scanf("%d", &q->godina);
	
	q->next = x->next;
	x->next = q;
	return 0;
}
int dodajispred(osoba* head, osoba* x) {
	osoba* p = pronadipredhodni(head,  x);
	osoba* novi = (osoba*)malloc(sizeof(osoba));
	printf("Unesite ime: \n");
	scanf("%s", novi->ime);
	printf("Unesite prezime: \n");
	scanf("%s", novi->prezime);
	printf("Unesite godinu rodenja: \n");
	scanf("%d", &novi->godina);
	printf("\n");

	novi->next = p->next;
	p->next = novi;
	return 0;
}