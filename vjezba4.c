#define _CRT_SECURE_NO_WARNINGS

/*4. Napisati program za zbrajanje i množenje polinoma. Koeficijenti i eksponenti se èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nužno sortirani.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<ctype.h>
#include<limits.h>

struct _Polinom;
typedef struct Polinom* Poli;

typedef struct Polinom
{
	int koeficijent;
	int eksponent;
	Poli next;
}Polinom;

int Unos(Poli, int, int);
int Ispis(Poli);
int Suma(Poli, Poli, Poli);
int Produkt(Poli, Poli, Poli);
int CitanjeIzDatoteke(Poli);
Poli TraziPret(int, Poli);
int Alociranje(Poli, int, int);
int UnosVrijednosti(int*, int*);
int IspisUputa();

int main()
{
	Polinom poli1Head = { 0 };
	Polinom poli2Head = { 0 };
	Polinom sumaHead = { 0 };
	Polinom produktHead = { 0 };

	int unos = 1, eksponent = 0, koeficijent = 0;

	poli1Head.eksponent = NULL;
	poli2Head.eksponent = NULL;
	sumaHead.eksponent = NULL;
	produktHead.eksponent = NULL;

	IspisUputa();

	while (unos != 0) {
		printf("\n\n\tUnesite broj:\t");
		scanf("%d", &unos);

		switch (unos)
		{
		case 0:
			printf("\n\nKraj Programa!\n");
			break;
		case 1:
			printf("\nUnesite ime polinoma za unos(npr 1, 2, 3, ...):\t");
			scanf("%d", &unos);
			switch (unos)
			{
			case 1:
				UnosVrijednosti(&koeficijent, &eksponent);
				Unos(&poli1Head, koeficijent, eksponent);
				break;
			case 2:
				UnosVrijednosti(&koeficijent, &eksponent);
				Unos(&poli2Head, koeficijent, eksponent);
				break;
			default:
				printf("\n\nNiste naveli niti jedan polinom!\n");
				break;
			}
			break;
		case 2:
			printf("\n\nUnesite ime polinoma za ispis(npr. 1, 2,3, ...):\t");
			scanf("%d", &unos);
			switch (unos)
			{
			case 1:
				Ispis(&poli1Head);
				break;
			case 2:
				Ispis(&poli2Head);
				break;
			default:
				printf("Niste naveli niti jedan polinom!\n");
				break;
			}
			break;
		case 3:
			Suma(&poli1Head, &poli2Head, &sumaHead);
			printf("Suma:\n");
			Ispis(&sumaHead);
			break;
		case 4:
			Produkt(poli1Head.next, poli2Head.next, &produktHead);
			printf("Produkt:\n");
			Ispis(&produktHead);
			break;
		case 5:
			CitanjeIzDatoteke(&poli1Head);
			break;
		case 6:
			CitanjeIzDatoteke(&poli2Head);
			break;
		default:
			printf("Krivi unos!\n");
			IspisUputa();
			break;
		}
	}

	return 0;
}

int IspisUputa()
{
	printf("\tUpute:\n");
	printf("\t-----------------------------------------\n");
	printf("\tUnos - 1\n");
	printf("\tIspis - 2\n");
	printf("\tRacunanje sume - 3\n");
	printf("\tRacunanje produkta - 4\n");
	printf("\tCitanje prvog polinoma iz datoteke - 5\n");
	printf("\tCitanje drugog polinoma iz datoteke - 6\n");
	printf("\tIzlaz iz programa - 0\n");
}

int UnosVrijednosti(int* koeficijent, int* eksponent)
{
	printf("Unesite koeficijent:\t");
	scanf("%d", koeficijent);
	printf("Unesite eksponent:\t");
	scanf("%d", eksponent);
	return 0;
}

int CitanjeIzDatoteke(Poli P)
{
	FILE* fp = NULL;
	char imePolinoma[20] = { 0 };
	int koeficijent = 0;
	char c = 'x';
	int eksponent = 0;

	printf("Unesite ime polinoma kojeg zelite procitati:\t");
	scanf(" %s", imePolinoma);

	fp = fopen(imePolinoma, "r");

	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d%c%d ", &koeficijent, &c, &eksponent);

			while (P->next != NULL && P->next->eksponent > eksponent)
			{
				P = P->next;
			}

			if (P->next != NULL && P->next->eksponent == eksponent)
			{
				P->next->koeficijent += koeficijent;
			}
			else {
				Alociranje(P, koeficijent, eksponent);
			}
		}
		Ispis(P);
	}
	return 0;
}

int Unos(Poli poli, int koeficijent, int eksponent)
{
	Poli temp = NULL;
	Poli head = NULL;

	if (koeficijent == 0)
	{
		printf("Koeficijent je 0 pa ce se ovaj unos ponistiti!\n");
	}
	else
	{
		while (poli->next != NULL && poli->next->eksponent > eksponent)
		{
			poli = poli->next;
		}

		if (poli->next != NULL && poli->next->eksponent == eksponent)
		{
			poli->next->koeficijent += koeficijent;
		}
		else
		{
			Alociranje(poli, koeficijent, eksponent);
		}
	}
	return 0;
}

int Alociranje(Poli P, int koeficijent, int eksponent)
{
	Poli temp = NULL;

	temp = (Poli)malloc(sizeof(Poli));
	if (temp == NULL)
	{
		printf("Greska!\n");
		return -1;
	}

	temp->eksponent = eksponent;
	temp->koeficijent = koeficijent;

	temp->next = P->next;
	P->next = temp;
	return 0;
}

int Ispis(Poli P)
{
	while (P != NULL)
	{
		if (P->koeficijent == 0 && P->eksponent == NULL)
		{
			if (P->next != NULL)
			{
				P = P->next;

				printf("\t%dx%d ", P->koeficijent, P->eksponent);

				P = P->next;
			}
			else
				P = P->next;
		}
		else if (P->next == NULL)
		{
			if (P->koeficijent < 0)
				printf("%dx%d\n\n", P->koeficijent, P->eksponent);
			else
				printf("+%dx%d\n\n", P->koeficijent, P->eksponent);

			P = P->next;
		}
		else
		{
			if (P->koeficijent < 0)
				printf("%dx%d ", P->koeficijent, P->eksponent);
			else
				printf("+%dx%d ", P->koeficijent, P->eksponent);

			P = P->next;
		}
	}
	printf("\n");
	return 0;
}

int Suma(Poli P1, Poli P2, Poli suma)
{
	Poli temp = NULL;

	while (P1 != NULL && P2 != NULL)
	{
		if (P1->eksponent == P2->eksponent)
		{
			Alociranje(suma, P1->koeficijent + P2->koeficijent, P1->eksponent);
			P1 = P1->next;
			P2 = P2->next;
		}
		else if (P1->eksponent > P2->eksponent)
		{
			Alociranje(suma, P1->koeficijent, P1->eksponent);
			P1 = P1->next;
		}
		else
		{
			Alociranje(suma, P2->koeficijent, P2->eksponent);
			P2 = P2->next;
		}
	}

	if (P1 != NULL)
	{
		temp = P1;
	}
	else
	{
		temp = P2;
	}
	while (temp != NULL)
	{
		Alociranje(suma, temp->koeficijent, temp->eksponent);
		temp = temp->next;
	}
	return 0;
}

int Produkt(Poli p1, Poli p2, Poli produkt)
{
	Poli pocetakP2 = p2;
	Poli pocetakProdukt = produkt;
	Poli trenutni = NULL;
	Poli prethodni = NULL;

	while (p1 != NULL)
	{
		while (p2 != NULL)
		{
			Alociranje(produkt, (p1->koeficijent * p2->koeficijent), (p1->eksponent + p2->eksponent));
			p2 = p2->next;
		}
		p1 = p1->next;
		p2 = pocetakP2;
	}

	produkt = pocetakProdukt->next;

	while (produkt->next != NULL)
	{
		trenutni = produkt;
		produkt = produkt->next;
		while (produkt->next != NULL)
		{
			if (trenutni->eksponent == produkt->eksponent)
			{
				trenutni->koeficijent += produkt->koeficijent;
				prethodni = TraziPret(produkt->eksponent, trenutni->next);
				prethodni->next = produkt->next;
				free(produkt);
				produkt = prethodni;
			}
			produkt = produkt->next;
		}
		produkt = trenutni;
		produkt = produkt->next;
	}
	return 0;
}

Poli TraziPret(int eksponent, Poli P)
{
	Poli prev = P;

	P = P->next;

	while (P != NULL && P->eksponent != eksponent)
	{
		prev = P;
		P = P->next;
	}

	if (P != NULL)
		return prev;

	else
		return NULL;
}