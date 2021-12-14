//8. Napisati program koji omogućava rad s binarnim stablom pretraživanja.Treba
//omogućiti unošenje novog elementa u stablo, ispis elemenata(inorder, preorder, postorder i
//level order), brisanje i pronalaženje nekog elementa.


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct stablo* pozicija;
struct stablo {
	int el;
	pozicija l;
	pozicija d;

};
typedef struct red* Pozicija;
struct red {
	pozicija stablo;
	Pozicija next;
};



	pozicija dodaj(int x, pozicija s) {
	if (s == NULL) {
		s = (pozicija)malloc(sizeof(stablo));
		s->el = x;
		s->l = NULL;
		s->d = NULL;
	}
	 if (x < s->el)
		s->l=dodaj(x, s->l);
	 if (x > s->el)
		 s->d = dodaj(x, s->d);
   return s;
	
}

int ispisi_inorder(pozicija s) {
	if (s != NULL) {
		ispisi_inorder(s->l);
		printf("%d ", s->el);
		ispisi_inorder(s->d);
	}
	return 0;
}

int ispisi_postorder(pozicija s) {
	if (s != NULL) {
		ispisi_postorder(s->l);		
		ispisi_postorder(s->d);
		printf("%d ", s->el);

	}
		return 0;	
}
int ispisi_preorder(pozicija s) {
	if (s != NULL) {
		printf("%d ", s->el);
		ispisi_preorder(s->l);
		ispisi_preorder(s->d);
	}
	return 0;
}
pozicija trazi_min(pozicija s) {
	if (s == NULL) {
		printf("Nema stabla");
		return s;
		}
	else {
		while (s ->l) {			
				s = s->l;
				return s;
		}

		return s;
	}
}
pozicija izbrisi(int x, pozicija s) {
	pozicija temp;
	
	if (x != NULL) {

		if (x < s->el)
			s->l = izbrisi(x, s->l);
		if (x > s->el)
			s->d = izbrisi(x, s->d);
		if (x == s->el) {
			if (s->l != NULL && s->d != NULL) {
				temp = trazi_min(s->d);
				s->el = temp->el;
				s->d = izbrisi(s->el, s->d);
			}
			else {
				temp = s;
				if (s->l == NULL)
					s = s->d;
				else
					s = s->l;
				free(temp);
			}
		}
		return s;
	}
	else	{
		printf("nema trazenog elementa\n");
			return s;
				}	
}



pozicija trazi(int x, pozicija s) {
	if (s != NULL) {
		if (x < s->el)
			return trazi(x, s->l);
		else if (x > s->el)
			return trazi(x, s->d);
		else 
			return s;		
	}
	else 		
		return s;
	
	}
	
	

	int main() {
		Pozicija head=(Pozicija)malloc(sizeof(red));
		head->stablo = NULL;
		head->next = NULL;
		pozicija s = NULL;
		s = dodaj(5, s);
		s = dodaj(4, s);
		s = dodaj(11, s);
		s = dodaj(10, s);
		s = dodaj(2, s);
		s = dodaj(3, s);
		s = dodaj(1, s);

		int unos,x,a,b;
		while (1) {
		  printf("\n**************\n"
				"Ako zelis upisati element u stablo stisni 1\n"
				"ako zelis ispisati inorder stisni 2 \n"
				"ako zelis ispisati postorder stisni 3\n"
				"ako zelis ispisati preorder stisni 4\n"
				"ako zelis izbrisati element stisni 5\n"
				"ako zelis pronaci element stisni 6\n"
				"ako zelis izici stisni 0\n"
			    "**********\n");
			scanf("%d", &unos);

			switch (unos) {
			case(1):
				printf("upisi broj kojeg zelis upisati u stablo\n");
				scanf("%d", &x);
				s = dodaj(x, s);
				break;
			case(2):
				ispisi_inorder(s);
				break;
			case(3):
				ispisi_postorder(s);
				break;
			case(4):
				ispisi_preorder(s);
				break;
			case(5):
				printf("Upisi element koji zelis izbrisati\n");
				scanf("%d", &a);
				s = izbrisi(a, s);
				break;
			case(6):
				printf("upisi element kojeg zelis naci\n");
				scanf("%d", &b);
				s = trazi(b, s);
				if (s != NULL)
					printf("adresa trazenog elementa je %d\n", s);
				else
					printf("nema trazenog elementa\n");
				break;
			case(0):
				return 0;
			default:
				printf("krivi unos, pokusajte ponovno\n");
			}

		}
		return 0;
	}
	
	

	