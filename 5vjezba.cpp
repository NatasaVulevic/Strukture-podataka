/*5. Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat. Stog je potrebno realizirati preko vezane liste*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct _stog * position;
typedef struct _stog {
	double number;
	position next;
} stog;

position kreirajelement(double number);
int umetniposlije(position a, position element);
int push(position head, double number);
int izbrisiposlije(position a);
int pop(double* destinacija, position head);
int izvrsioperaciju(position head, char operacija);
int izracunaj_postfix_iz_datoteke(double* destinacija, const char* imedatoteke);
int izbrisisve(position head);



int main() {
	double rezultat;
	izracunaj_postfix_iz_datoteke(&rezultat, "postfix.txt");
	printf("%lf\n", rezultat);

		return 0;
}


position kreirajelement(double number) {
	position element=NULL;
	element = (position)malloc(sizeof(stog));
	if (!element) {
		perror("ne mozemo alocirati\n");
		return NULL;
	}
	element->number = number;
	element->next = NULL;
	return element;
}
int umetniposlije(position a ,position element) {

	element->next = a->next;
	a->next = element;
	return 0;
}
int push(position head, double number) {
	position element = kreirajelement(number);
	
	umetniposlije(head, element);
	return 0;
}
int izbrisiposlije(position a) {

	position b = a->next;
	a->next = b -> next;
	free(b);
	if (!b) {
		printf("greska\n");
		return -1;
	}
	return 0;
}
int pop(double* destinacija, position head) {
	position first = head->next;
	*destinacija = first->number;
	izbrisiposlije(head);
	return 0;
}

int izvrsioperaciju(position head, char operacija) {
	double operand1=0, operand2=0, rezultat=0;
	int status1 = 0, status2=0;
	status2 = pop(&operand2, head);
	if (status2 != 0)
		return -1;
	status1 = pop(&operand1, head);
	if (status1 != 0)
		return -2;

	switch (operacija) {
	case '+':
		rezultat = operand1 + operand2;
		break;
	case '-':
		rezultat = operand1 - operand2;
		break;
	case '*':rezultat = operand1 * operand2;
		break;
	case '/':rezultat = operand1 / operand2;
		if (operand2 == 0) {
			printf("ne mozemo dijeliti s nulom\n");
			return -3;
		}
		break;
	default:
		printf("operacija nije definirana\n");
		return -4;
	}

	return push(head,rezultat);
}

int izracunaj_postfix_iz_datoteke(double* destinacija,const char * imedatoteke) {
	int duljinadatoteke=0;
	char* buffer = NULL;
	char* privremenibuffer = 0;
	int numbytes = 0;
	int status = 0;
	double number = 0;
	char operacija = 0;
	FILE * f = NULL;
	stog head = {head.number = 0,head.next = NULL };
	f = fopen(imedatoteke, "rb");
	if (!f) {
		printf("ne mogu otvoriti datoteku\n");
		return -1;
	}
	fseek(f, 0, SEEK_END);
	duljinadatoteke = ftell(f);
	buffer = (char*)calloc(duljinadatoteke + 1, sizeof(char));
	if (!buffer)
	{
		perror("ne mogu alocirati memoriju\n");
		return -2;
	}
	rewind(f);
	fread(buffer, sizeof(char), duljinadatoteke, f);
	printf("| % s|\n",buffer);
	fclose(f);
	privremenibuffer = buffer;
	while (strlen(privremenibuffer)>0)
	{
		status = sscanf(privremenibuffer, "%lf %n", &number,&numbytes);
		if (status == 1) {
			status = push(&head, number);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				izbrisisve(&head);
				return -1;
			}
			privremenibuffer += numbytes;

		}
		else {
			sscanf(privremenibuffer, " %c %n", &operacija, &numbytes);
			status = izvrsioperaciju(&head, operacija);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				izbrisisve(&head);
				return -1;
			}
			privremenibuffer += numbytes;
		}
	}
	free(buffer);

	status = pop(destinacija, &head);
	if (status != EXIT_SUCCESS)
	{
		izbrisisve(&head);
		return -5;
	}

	if (head.next)
	{
		printf("Postfix ne valja\n");
		izbrisisve(&head);
		return -6;
	}

	return EXIT_SUCCESS;

}



int izbrisisve(position head) {
	position p = head->next;
	while (p) {
		izbrisiposlije(head);
	}
	return 0;
}