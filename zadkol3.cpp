/*Napisati program koji čita iz datoteke dio teksta, te kreira binarno stablo pretraživanja. Binarno stablo se
kreira na način da se u njega upisuju sve različite riječi iz teksta koji je zapisan u datoteci s pripadajućim
duljinama unesene riječi.
struct _Cvor{char *rijec; int length; struct _Cvor *Left; struct _Cvor *Right;};
Potrebno je izračunati prosječnu duljinu svake riječi zapisane u binarnom stablu.
Napisati program koji iz tako kreiranog binarnog stabla u vezanu listu puni samo one riječi koje su dulje
od prosječne duljine svih riječi, te ispisati tu vezanu listu. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stablo* poz;
struct stablo {
	const char* rijec={};
	int length;
	poz l;
	poz d;
};

typedef struct lista *pozi;
struct lista {
	const char* rijec={};
	pozi next;
};
int ispisi_inorder(poz s);

poz dodaj(const char* rijec, poz s) {
	if (s == NULL) {
		s = (poz)malloc(sizeof(stablo));
		s->rijec=rijec;
		//strcpy(s->rijec, rijec);
		s->length = strlen(rijec);
		s->l = NULL;
		s->d = NULL;
	}
	if (strcmp(rijec, s->rijec) < 0)
		s->l = dodaj(rijec, s->l);
	if (strcmp(rijec, s->rijec) > 0)
		s->d = dodaj(rijec, s->d);
	return s;
}

int broji(poz s, int br) {
	if (s->l)
		br = broji(s->l, br);
	if (s->d)
		br = broji(s->d, br);
	br++;
	return br;
}
int brojislova(poz s, int len) {
	if (s->l)
		len = brojislova(s->l, len);
	if (s->d)
		len = brojislova(s->d, len);
	len = s ->length + len;
	return len;
}
pozi upisiulistu(pozi head, char* rijec);
int prodikrozstablo(poz s, float prosjek, pozi head);
int ispisilistu(pozi head);

int main() {
	FILE* f;	
	char rijec1[1024] ;
	int i = 0, br = 0, len=0;
	float prosjek;
	poz s = NULL;
	struct lista head;
	head.rijec = {};
	head.next = NULL;
	
	
	f = fopen("Datoteka1.txt", "r");
	if (!f) {
		printf("greska pri otvaranju dat");
		return -1;
	}
	while (feof(f) == 0) {

		fscanf(f, "%s", rijec1);     //ne zeli mi dodati rijeci u stablo
		printf("%s ", rijec1);
		s = dodaj(rijec1, s);	
	}	
	printf("\n");
	ispisi_inorder(s);    //ispise samo zadnji
	fclose(f);
	len = brojislova(s, len);
	br = broji(s, br);
	prosjek = (float)len / br;
	prodikrozstablo(s, prosjek, &head);
	ispisilistu(&head);
	return 0;
}

pozi upisiulistu(pozi head, const char *rijec) {
	pozi a = (pozi)malloc(sizeof(lista));
	a->rijec= rijec;
	a->next = head->next;
	head->next = a;
	return 0;
}

int prodikrozstablo(poz s, float prosjek, pozi head) {
	if (s->l)
		 prodikrozstablo(s->l, prosjek,head);
	if (s->d)
		prodikrozstablo(s->d,prosjek,head);
	if (s->length > prosjek)
		upisiulistu(head,s->rijec);
	return 0;
}

int ispisilistu(pozi head){
	while (head->next != NULL) {
		printf("%s", head->next->rijec);
		head = head ->next;
	}
	return 0;
}

int ispisi_inorder(poz s) {
	if (s != NULL) {
		ispisi_inorder(s->l);
		printf("%s ", s->rijec);
		ispisi_inorder(s->d);
	}
	return 0;
}
