/* 7. Napisati program koji pomoću vezanih listi(stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.Točnije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dir* Pozicija;
struct dir {
	char ime[256];
	Pozicija child;
	Pozicija sib;
};
typedef struct stog* pozicija;
struct stog {
	Pozicija direktorij;
	pozicija next;
};

pozicija alocirajmem_stog();
Pozicija alocirajmem_dir(char*);
Pozicija  pop(pozicija head);
Pozicija  kreiraj_direktorij(Pozicija current, char* ime);
Pozicija cd_prev(pozicija head);
int ispis_dir(Pozicija current);
Pozicija cd(Pozicija current, pozicija head, char* ime);
int ispiscmd(pozicija head, Pozicija current);
int push(pozicija head, Pozicija b);

int main() {
struct stog head;
	head.direktorij = NULL;
	head.next = NULL;
	char unos[256]; char naredba[256];char ime[256];
	
	struct dir  C;
	C.child = NULL;
	C.sib = NULL;
	strcpy(C.ime, "C:");
	Pozicija current = &C;

	printf("C:\\>");
     push(&head,&C) ;
	
	while (1)
	{
		fgets(unos, 256, stdin);
		sscanf(unos, "%s %s", naredba, ime);

		if (!strcmp(naredba, "md")) {
			 current = kreiraj_direktorij(current, ime);
			ispiscmd(&head,current);      //sa ispiscmd nesto ne valja
			}

		else if (!strcmp(naredba, "cd")){			
				 current = cd(current, &head, ime);
				ispiscmd(&head, current);
			}

		else if (!strcmp(naredba, "cd..")) {
			 current = cd_prev(&head);
			ispiscmd (&head,current);
			}
		else if (!strcmp(naredba, "dir")) {
			ispiscmd(&head,current);
			ispis_dir(current);
		}
		else if (!strcmp(naredba, "exit"))
			break;
		else {
			printf("nedozvoljen unos");
		}

		
	}
	return 0;
}

pozicija alocirajmem_stog() {
	pozicija q = (pozicija)malloc(sizeof(stog));
	if (!q) {
		printf("greska\n");
		return NULL;
	}
	return q;
}
Pozicija alocirajmem_dir(char *ime) {
	Pozicija q = (Pozicija)malloc(sizeof(dir));
	if (!q) {
		printf("greska2\n");
		return NULL;
	}
	strcpy(q->ime,ime);
	q->child = NULL;
	q->sib = NULL;
	return q;
}

int push (pozicija head, Pozicija current) {
	pozicija a = alocirajmem_stog();
	pozicija temp = head;

	while (temp->next)
		temp = temp->next;
	a->next = temp->next;
	temp->next = a;
	a->direktorij=current;

	return 0;
}
Pozicija pop (pozicija head) {
	pozicija temp = head->next, prev = head->next;// vidi jel ih ima 2
	if (prev == NULL) {
		printf("prazan stog\n");
		 return NULL;
	}
	else if (prev->next == NULL) {
		Pozicija direktorij_ = prev->direktorij;
		head->next=NULL;
		free(prev);
		return direktorij_;
		
	}

	else {
		while (prev->next->next)
			prev = prev->next;
			temp = prev->next;
			Pozicija direktorij_ = temp->direktorij;

		prev->next = temp->next;
		free(temp);
	
		 return direktorij_;
	}
	
}
Pozicija  kreiraj_direktorij(Pozicija current, char* ime) {
	Pozicija direktorij_ = alocirajmem_dir(ime);
	
	if (current->child == NULL) {
		current->child = direktorij_;		
	}
	else {
		Pozicija b = current->child;
		while (b->sib)
			b = b->sib;
		b->sib=direktorij_;
	}current = direktorij_;
	return current;   
}
Pozicija cd(Pozicija current, pozicija head, char* ime) {       
	if (current->child == NULL)
		return current;
	else {
		Pozicija z = current;
		Pozicija a = current->child;
		while (a) {
			if (!strcmp(a->ime, ime)) {
				push(head, a);
				return a;
			}
			a = a->sib;
		}
		
		return z;
	}
}
Pozicija cd_prev(pozicija head) {
	Pozicija a = pop(head);
	return a;
	
}
int ispis_dir(Pozicija current) {
	if (current->child == NULL)
		printf("direktorij je prazan");
	else {
		current = current->child;
		while (current) {
			printf("%s\n", current->ime);
			current = current->sib;
		}
		return 0;
	}
	return 0;
}

int ispiscmd (pozicija head,Pozicija current) {
	char a[256] = "";
	while (head->next) {
		strcat(a, head->next->direktorij->ime);
		strcat(a, "\\");
		head = head->next;
	}
	strcat(a, ">");
	printf("%s", a);
	return 0;
}