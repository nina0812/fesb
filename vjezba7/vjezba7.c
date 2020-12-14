/*Napisati program koji iz datoteke čita postfiks izraz i zatim korištenjem stoga računa
rezultat.Stog je potrebno realizirati preko vezane liste.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
typedef struct stog* Pozicija;
typedef struct stog
{
	int el;
	Pozicija next;
}Stog;
int Push(Pozicija, int);
int Pop(Pozicija);
int Citajizdatoteke(char*, Pozicija);
int izracun(int, int, int*, char);
int ispis(Pozicija P);
Pozicija stvorielement();
int main()
{
	Pozicija P = NULL;
	P = stvorielement();
	char imedatoteke[20];
	printf("Unesite ime datoteke iz koje zelite citati postfix izraz.\n");
	scanf("%s", imedatoteke);
	Citajizdatoteke(imedatoteke, P);
	printf("\nRezultat postfix izraza je: \n");
	ispis(P->next);

	return 0;
}

Pozicija stvorielement()
{
	Pozicija q = (Pozicija)malloc(sizeof(Stog));
	if (q == NULL)
	{
		printf("Greska u alokaciji memorije.\n");
		return NULL;
	}
	q->next = NULL;
	return q;
}

int Citajizdatoteke(char* ime, Pozicija P)
{
	char* buffer;
	int rezultat;
	int x, y;
	buffer = (char*)malloc(20 * sizeof(char));
	FILE* fp = NULL;
	fp = fopen(ime, "r");
	if (fp == NULL)
	{
		printf("Greska u otvaranju datoteke.\n");
		return -1;
	}
	while (!feof(fp))
	{
		fscanf(fp, "%s", buffer); //formatirano citanje podataka iz datoteke
		//provjera je li dani znak operand(broj)
		if (isdigit(buffer[0]))
		{
			sscanf(buffer, "%d", &x); //formatirano citanje podataka iz stringa
			Push(P, x);
			printf(" (%d)", x);
		}
		//nije operand(operator je)
		else
		{
			y = Pop(P);
			x = Pop(P);
			izracun(x, y, &rezultat, buffer[0]); //prvi element koji se skida(y) ide desno, drugi(x) lijevo
			printf("Medurezultat je %d\n", rezultat);
			Push(P, rezultat);
		}
	}
	fclose(fp);
	free(buffer);
	return 0;
}

int Push(Pozicija P, int a) //dodavanje na pocetak
{
	Pozicija q = NULL;
	q = stvorielement();
	q->el = a;
	q->next = P->next;
	P->next = q;
	return 0;
}

int Pop(Pozicija P) //skidanje s pocetka
{
	Pozicija temp = NULL;
	int x;
	temp = stvorielement();
	temp = P->next;
	x = temp->el;

	if (temp == NULL)
	{
		printf("Stog je prazan.\n");
		return -1;
	}
	else
	{
		P->next = temp->next;
		free(temp);
	}
	return x;
}

int izracun(int x, int y, int* rezultat, char operator)
{
	switch (operator)
	{
		case '+':
		{
			*rezultat = x + y;
			break;
		}
		case '-':
		{
			*rezultat = x - y;
			break;
		}
		case '*':
		{
			*rezultat = x * y;
			break;
		}
		case '/':
		{
			if (y == 0)
			{
				printf("Beskonacno.\n");
				return -1;
			}
				*rezultat = x / y;
			break;
		}
		default:
		{
			break;
		}
	}

	return 0;
}

int ispis(Pozicija P)
{
	while (P != NULL)
	{
		printf("%d", P->el);
		P = P->next;
	}
	return 0;
}
