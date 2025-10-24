/*3. Prethodnom zadatku dodati funkcije :
A.dinamički dodaje novi element iza određenog elementa,
B.dinamički dodaje novi element ispred određenog elementa,
C.sortira listu po prezimenima osoba,
D.upisuje listu u datoteku,
E.čita listu iz datoteke.*/


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
int unoskraj(osoba* head);
osoba* pronadizadnji(osoba* head);
osoba* pronadiprezime(osoba* head, char* prezime);
osoba* pronadipredhodni(osoba* head, char* prezime);
int obrisi(osoba* head, char* prezime);
int dodajiza(osoba* head, char* prezime);
int dodajispred(osoba* head, char* prezime);
int unos(osoba*);
int sortiraj(osoba* head);
int upisiudat(osoba* head);
int citajizdat(osoba* head);




int main() {
	osoba* head;
	head = (osoba*)malloc(sizeof(osoba));
	head->next = NULL;

	int izbor = 0;

	char prezime[MAX], prezime2[MAX];
	osoba* nadiprezime = NULL;
	osoba* obrisiel = NULL;
	nadiprezime = (osoba*)malloc(sizeof(osoba));
	obrisiel = (osoba*)malloc(sizeof(osoba));
	

	printf("**********\n");
	printf("1-unos na pocetak\n");
	printf("2-unos na kraj\n");
	printf("3-ispis\n");
	printf("4-pronadi po prezimenu\n");
	printf("5-izbrisi prezime\n");
	printf("6-dodaj nakon\n");
	printf("7-dodaj ispred\n");
	printf("8-sortiraj listu\n");
	printf("9-upisi u datoteku\n");
	printf("10-citaj iz datotke\n");


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
			if (nadiprezime == NULL)
				printf("ne postoji trazeno prezime");
			else			
				printf("element koji trazite je %s\n %s\n %d\n", nadiprezime->ime, nadiprezime->prezime, nadiprezime->godina);
				break;
			
		case (5):
			printf("koje prezime zelite izbrisati\n");
			scanf(" %s", prezime2);
			obrisi(head, prezime2);
			break;
		case(6):
			printf("iza kojeg prezimena zelite dodati\n");
			scanf("%s", prezime);			
			dodajiza(head, prezime);
			break;
		case(7):
			printf("ispred kojeg prezimena zelite dodati\n");
			scanf("%s", prezime);			
			dodajispred(head, prezime);
			break;
		case(8):
			sortiraj(head);
			break;
		case (9):
			upisiudat(head);
			break;
		case(10):
			citajizdat(head);
			break;
		case(0):
			return 0;

		default:printf("krivi unos.pokusajte ponovno\n");
		}
	}

	return 0;
}

int unos(osoba* x) {
	printf("unesi ime\n");
	scanf("%s", x->ime);

	printf("unesi prezime\n");
	scanf("%s", x->prezime);

	printf("unesi godinu rodenja\n");
	scanf("%d", &x->godina);
	return 0;
}

int unospocetak(osoba* head) {
	osoba* o;
	o = (osoba*)malloc(sizeof(osoba));
	o->next = head->next;
	head->next = o;
	unos(o);
	return 0;
}

int ispis(osoba* head) {
	osoba* o = head->next;
	while (o != NULL) {
		printf("\nIme: %s\n prezime: %s\n godina rodenja: %d\n", o->ime, o->prezime, o->godina);
		o = o->next;
	}
	return 0;
}

int unoskraj(osoba* head) {
	osoba* o, * z;
	o = (osoba*)malloc(sizeof(osoba));
	
	z = pronadizadnji(head);
	o->next = z->next;
	z->next = o;

	unos(o);
	return 0;
}
osoba* pronadizadnji(osoba* head) {
	osoba* o = head;
	while (o != NULL && o->next != NULL)
		o = o->next;
	return o;
}
osoba* pronadiprezime(osoba* head, char* prezime) {
	osoba* o = head->next;
	while (o != NULL && strcmp(o->prezime, prezime))
			o = o->next;
		
		return o;
		
		
}
osoba* pronadipredhodni(osoba* head, char* prezime) {
	osoba* x;
	x = pronadiprezime(head, prezime);
	if (x == NULL)
	{
		printf("ne postoji trazeno prezime\n");
		return NULL;
	}
	else {

		osoba* o = head;
		while (o != NULL && o->next != x)
			o = o->next;
		return o;
	}

}
int obrisi(osoba* head, char* prezime) {
	osoba* p = NULL, * x = NULL, * temp = NULL;
	x = pronadiprezime(head, prezime);
	if (x == NULL)
	{
		printf("ne postoji trazeno prezime\n");
		return 0;
	}
	else {
		p = (osoba*)malloc(sizeof(osoba));
		temp = x;
		p = pronadipredhodni(head, prezime);
		temp = p->next;
		p->next = x->next;
		free(temp);
		return 0;
	}
}
int dodajiza(osoba* head, char* prezime)
{	
	osoba* p = NULL;
	osoba* q = NULL;
	q = (osoba*)malloc(sizeof(osoba));
	p = pronadiprezime(head, prezime); 
	if (p == NULL) {
		printf("ne postoji trazeno prezime\n");
		return 0;
	}
	else {
		printf("unesi podatke osobe koju dodajes\n");
		unos(q);

		q->next = p->next;
		p->next = q;
		return 0;
	}
}
int dodajispred(osoba* head, char* prezime) {
	osoba* x = pronadiprezime(head, prezime); 
	if (x == NULL) {
		printf("ne postoji trazeno prezime\n");
		return 0;
	}
	else {
	osoba* p = pronadipredhodni(head, prezime);
	osoba* novi = (osoba*)malloc(sizeof(osoba));
	printf("unesi podatke osobe koju dodajes\n");
	unos(novi);

	novi->next = p->next;
	p->next = novi;
	return 0;}
}
int sortiraj(osoba* head) {
	osoba* p = head;
	osoba* predq = NULL, * q = NULL, * zadnji = NULL;
	while (p->next != zadnji) {
		predq = p;
		q = predq->next;
		while (q->next != zadnji) {
			if (strcmp(q->prezime, q->next->prezime) > 0) {
				predq->next = q->next;
				q->next = q->next->next;
				predq->next->next = q;
				q = predq->next;
			}
			predq = q;
			q = q->next;
		}
		zadnji = q;
	}
	return 0;
}
int upisiudat(osoba* head) {
	osoba* o = NULL;
	
	o = head->next;
	FILE* fp = NULL;
	fp = fopen("Natasa.txt", "w");

	if (fp == NULL) {
		printf("greska u otvaranju datoteke\n");
		return -1;
	}
	while (o != NULL)
	{
		fprintf(fp, "ime: %s prezime: %s godina rodenja %d\n", o->ime, o->prezime, o->godina);
		o = o->next;
	}
	fclose(fp);
	return 0;
}

int citajizdat(osoba* head)
{
	
	char buffer[1024] = { 0 };
	int i, broj = 0;

	FILE* fp = NULL;
	fp = fopen("Natasa.txt", "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}
		while (!feof(fp)) {
			fgets(buffer, 1024, fp);
			broj++;
		}
		rewind(fp);

		for (i = 0; i < broj - 1; i++) {
			fgets(buffer, 1024, fp);
			printf("%s", buffer);
		}
		fclose(fp);
	return 0;
}
