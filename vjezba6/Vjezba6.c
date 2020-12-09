#define _CRT_SECURE_NO_WARNINGS
/*Napisati program koji pomoću vezanih listi simulira rad :
a) stoga,
b) reda.
Napomena: Funkcija "push" sprema cijeli broj, slučajno generirani u opsegu od 10 - 100.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct cvor* Pozicija;
typedef struct cvor
{
	int el;
	Pozicija next;
}Cvor;
int pushStog(Pozicija);
int pushRed(Pozicija);
int pop(Pozicija);
int ispis(Pozicija);
Pozicija dodajelementiinicijaliziraj();
int getrandomnumber(int, int);
int main()
{
	int izbor = 0;
	Cvor stog, red;
	stog.next = NULL;
	red.next = NULL;
	while (izbor != 5)
	{
		printf("\n1-Push stog.\n");
		printf("\n2-Pop stog.\n");
		printf("\n3- Push red.\n");
		printf("\n4-Pop red.\n");
		printf("\n5-kraj.\n");
		printf("\nVas izbor je: \n");
		scanf("%d", &izbor);
	switch (izbor)
		{
			case 1:
			{
				pushStog(&stog);
				ispis(stog.next);
				break;
			}
			case 2:
			{
				pop(&stog);
				ispis(stog.next);
				break;
			}
			case 3:
			{
				pushRed(&red);
				ispis(red.next);
				break;
			}
			case 4:
			{
				pop(&red);
				ispis(red.next);
				break;
			}
			case 5:
			{
				printf("Kraj programa.\n");
				break;
			}
			default:
			{
				printf("Nepostojec odabir.\n");
				break;
			}
		}	
	}
 return 0;
}

int getrandomnumber(int min, int max)
{
	srand((unsigned)time(NULL));
	return rand() % (max + 1 - min) + min;
}

Pozicija dodajelementiinicijaliziraj()
{
	Pozicija noviel;
	noviel = (Pozicija)malloc(sizeof(Cvor));
	if (noviel == NULL)
		{
			printf("Greska u alokaciji memorije.\n");
			return NULL;
		}
	else
		{
			noviel->el = getrandomnumber(10, 100);
			noviel->next = NULL;
			return noviel;
		}

}

int pushStog(Pozicija P) //dodajemo na pocetak
{
	Pozicija q = dodajelementiinicijaliziraj();
	q->next = P->next;
	P->next = q;
  return 0;
}

int pushRed(Pozicija P) //dodajemo na kraj
{
	Pozicija q = dodajelementiinicijaliziraj();
	while (P->next != NULL)
		{
		   P = P->next;
		}
	q ->next = P->next;
	P->next = q;
	return 0;
}

int pop(Pozicija P) //brisanje s pocetka
{
	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(Cvor));
	temp = P->next;
	if (temp == NULL)
	{
		printf("Red je prazan.\n");
		return -1;
	}
		P->next = temp->next;
		free(temp);

	return 0;
}

int ispis(Pozicija P)
{
	if (P == NULL)
	{
		printf("Lista je prazna.\n");
		return -1;
	}
	else
	{
		while (P != NULL)
			{
				printf("%d\t", P->el);
				P = P->next;
			}
	}
	return 0;

}
