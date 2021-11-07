/* 4. Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
čitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<ctype.h>
#define MAXLINE 1024

typedef struct _element* pozicija;
typedef struct _element {
	int koef;
	int pot;
	pozicija next;

}element;

pozicija stvorielement(int koef, int pot);
int citajizdatoteke(pozicija head1, pozicija head2);
int citajpo2(char* buffer, pozicija head);
int umetnisortirano(pozicija head, pozicija a);
int umetni(pozicija temp, pozicija a);
int umetniiza(pozicija p, pozicija a);
int izbrisiposlije(pozicija p);
int ispisilistu(pozicija head);
int zbroji(pozicija headzbroj, pozicija head1, pozicija head2);
int mnozi(pozicija headprodukt, pozicija head1, pozicija head2);
int isprintaj(pozicija prvi);


int main() {
	
	element head1 = {head1.koef = 0,head1.pot = 0, head1.next = NULL};
	element head2 = { head2.koef = 0,head2.pot = 0, head2.next = NULL };
	element headzbroj = { headzbroj.koef = 0, headzbroj.pot = 0,  headzbroj.next = NULL };
	element headprodukt = { headprodukt.koef = 0,headprodukt.pot = 0,headprodukt.next = NULL };
	
	citajizdatoteke(&head1, &head2);
	ispisilistu(&head1);
	ispisilistu(&head2);
	zbroji(&headzbroj, &head1,& head2);
	ispisilistu(&headzbroj);	
	printf("zbroj polinoma je: \n");
	isprintaj(&headzbroj);
	printf("\n");
	printf("umnozak polinoma je:\n");
    mnozi(&headprodukt, &head1,&head2);
	isprintaj(&headprodukt);

	return 0;
}


pozicija stvorielement(int koef, int pot) {                               
	pozicija p = (pozicija)malloc(sizeof(element));
	if (p == NULL) {
		printf("greska u alociranju\n");
		return NULL;
	}

	p->koef = koef;
	p->pot = pot;
	p->next = NULL;
	return p;
}

int citajizdatoteke(pozicija head1, pozicija head2) {	
	FILE * fp=NULL;
	char buffer1[MAXLINE] = { 0 };	
	char buffer2[MAXLINE] = { 0 };

	fp = fopen("polinomi.txt", "r");
	if (fp == 0) {
		perror("greska u utvaranju dat\n");
		return -1;
	}
	fgets(buffer1, MAXLINE, fp);
	citajpo2(buffer1, head1);

	fgets(buffer2, MAXLINE, fp);
	citajpo2(buffer2, head2);	
	
	return 0;

}
	int citajpo2(char*buffer, pozicija head) {
		int brojbajtova=0;
		int koef=0, pot=0,x=0;
		char* privremenibuffer= buffer;
		pozicija a = NULL;
		while (strlen(privremenibuffer) > 0) {
			x = sscanf(privremenibuffer, "%d %d %n", &koef, &pot,&brojbajtova);
			if (x!= 2)
			{
				printf("Imate neparan broj elemenata\n");
				return -1;
			}
			a = stvorielement(koef, pot);
			if (!a) {
				printf("greska pri stvaranju elementa\n");
				return -1;
			}
			umetnisortirano(head, a);
			privremenibuffer += brojbajtova;
		}
		return 0;
	}
	int umetnisortirano(pozicija head,pozicija a) {
		pozicija temp = head;
		while (temp->next != NULL && a->pot > temp->next->pot)
			temp = temp->next;
		umetni(temp,a);

		return 0;
	}
	int umetni(pozicija temp,pozicija a) {
		int novikoef = 0;
		if (temp->next == NULL || temp->next->pot != a->pot)
			umetniiza(temp, a);
		else
		{
			novikoef = temp->next->koef + a->koef;

			if (novikoef == 0)
				izbrisiposlije(temp);
			else
				temp->next->koef = novikoef;
		}
		
		return 0;
	}
	int umetniiza(pozicija p, pozicija a) {
		a->next = p->next;
		p -> next = a;
		return 0;
	}
	int izbrisiposlije(pozicija p) {
		pozicija temp = p->next;
		p->next = temp->next;
		free(temp);

		return 0;
	}
	int ispisilistu(pozicija head) {
		pozicija p;
		 p = head->next;
		 while (p) {
			 printf("%d %d\n", p->koef, p->pot);
			 p = p->next;
		 }
			printf("\n");
		return 0;
	}

	int zbroji(pozicija headzbroj, pozicija head1, pozicija head2){
		pozicija i = NULL;
		pozicija j = NULL;
		pozicija a = NULL;
		for (i = head1->next; i != NULL; i = i->next) {
		   a = stvorielement(i->koef, i->pot);
		   umetnisortirano(headzbroj, a);
	      }
		for (j = head2->next; j != NULL; j = j->next) {
			a = stvorielement(j->koef, j->pot);
			if (!a) {
				printf("greska pri stvaranju elementa\n");
				return NULL;
			}

			umetnisortirano(headzbroj, a);
		}
		return 0;
	}
	int mnozi (pozicija headprodukt, pozicija head1, pozicija head2) {
		pozicija i = NULL;
		pozicija j = NULL;
		pozicija a = NULL;
		for (i = head1->next; i != NULL; i = i->next) {
			for (j = head1->next; j != NULL; j = j->next) {
				a = stvorielement(i->koef * j->koef, i->pot + j->pot);
				umetnisortirano(headprodukt, a);

			}
		}
		return 0;
	}

	int isprintaj(pozicija head) {
		pozicija prvi = head->next;
		
			if (prvi->pot < 0) {
				if (prvi->koef == 1)
					printf("x^(%d)", prvi->pot);
				else
					printf("%dx^(%d)", prvi->koef,prvi->pot);
			}
			else {
				if (prvi->koef == 1)
					printf("x^%d", prvi->pot);
				else
					printf("%dx^%d",prvi->koef, prvi->pot);
			}

			prvi = prvi -> next;
			for (; prvi != NULL; prvi = prvi->next) {

				if (prvi->pot < 0) {
					if (prvi->koef == 1)
						printf("+x^(%d)", prvi->pot);
					else if (prvi->koef < 0)
						printf("%dx^(%d)", prvi->koef, prvi->pot);
					else
						printf("+%dx^(%d)", prvi->koef, prvi->pot);
				}
				else {
					if (prvi->koef == 1)
						printf("+x^%d", prvi->pot);
					else if (prvi->koef < 0)
						printf("%dx^%d", prvi->koef, prvi->pot);
					else
						printf("+%dx^%d", prvi->koef, prvi->pot);
				}
			}
			printf("\n");
		return 0;
	}
