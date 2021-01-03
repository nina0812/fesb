/*Napisati program koji pomoću vezanih listi(stabala) predstavlja strukturu direktorija.
Omogućiti unos novih direktorija i pod - direktorija, ispis sadržaja direktorija i
povratak u prethodni direktorij.Točnije program treba preko menija simulirati
korištenje DOS naredbi : 1 - "md", 2 - "cd dir", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct direktorij* Pozicija;
typedef struct direktorij
{
	char ime[100];
	Pozicija next;
	Pozicija child;
}Direktorij;
typedef struct stog* pozicija;
typedef struct stog
{
	Pozicija data;
	pozicija Next;
}Stog;
int MakeDir(Pozicija, pozicija);
int PrintDirectory(Pozicija);
Pozicija ChangeDirectory(Pozicija);
int Push(Pozicija, pozicija);
Pozicija cdt(pozicija);
Pozicija Find(Pozicija, char*);
Pozicija stvoricvor(int);
pozicija stvoricvor1(int);
int umetnipodatke(Pozicija);
int main()
{
	Pozicija root = NULL;
	root = stvoricvor(1);
	Pozicija trenutni = root;
	pozicija stack = NULL;
	stack = stvoricvor1(1);
	char izbor = '0';
	printf("Unesite ime root direktorija: \n");
	scanf("%s", root->ime);
	strcat(root->ime, "://");
	while (izbor != 'z')
	{
		printf("Odaberite: \n");
		printf("1- Make directory.\n");
		printf("2- Print directory.\n");
		printf("3- Change directory.\n");
		printf("4- Vrati se u prethodni direktorij.\n");
		printf("z-za izlaz.\n");
		printf("Vas izbor je: \n");
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
		{
			MakeDir(trenutni, stack);
			break;
		}
		case '2':
		{
			PrintDirectory(trenutni);
			break;
		}
		case '3':
		{
			trenutni = ChangeDirectory(trenutni);
			break;
		}
		case '4':
		{
			trenutni = cdt(stack);
			break;
		}
		case 'z':
		{
			printf("Izlaz.\n");
			break;
		}
		default:
		{
			printf("Nepostojec odabir.\n");
		}
		}

	}
	return 0;
}
Pozicija cdt(pozicija stack)
{
	pozicija temp = NULL;
	Pozicija q = NULL;
	q = stvoricvor(1);
	temp = stack->Next;
	q = temp->data;
	stack->Next = temp->Next;
	free(temp);
	return q;
}
int MakeDir(Pozicija trenutni, pozicija stack)
{
	Pozicija q = NULL;
	if (trenutni == NULL)
	{
		printf("Ne postoji root direktorij.\n");
		return -1;
	}
	q = stvoricvor(1);
	umetnipodatke(q);
	Push(trenutni, stack);
	if (trenutni->child == NULL)
	{
		trenutni->child = q;
		return 0;
	}
	trenutni = trenutni->child;
	while (trenutni->next != NULL)
	{
		trenutni = trenutni->next;
	}
	q->next = trenutni->next;
	trenutni->next = q;
	return 0;
}
int PrintDirectory(Pozicija trenutni)
{
	int brojdirektorija = 0;
	if (trenutni == NULL)
	{
		printf("Ne postoji root direktorij.\n");
		return -1;
	}
	printf("Direktorij od %s:\n", trenutni->ime);
	trenutni = trenutni->child;
	if (trenutni == NULL)
	{
		return 1;
	}
	while (trenutni != NULL)
	{
		printf(" %s\n", trenutni->ime);
		trenutni = trenutni->next;
		brojdirektorija++;
	}
	printf("Broj direktorija je: %d\n", brojdirektorija);
	return 0;
}
Pozicija ChangeDirectory(Pozicija trenutni)
{
	Pozicija q = NULL;
	q = stvoricvor(1);
	char ime[20] = { 0 };
	printf("Unesite ime zeljenog direktorija:\n");
	scanf("%s", ime);
	q = Find(trenutni, ime);
	return q;
}
Pozicija Find(Pozicija P, char* ime)
{
	if (P == NULL)
	{
		printf("Greska.\n");
		return NULL;
	}
	P = P->child;
	while (P != NULL && strcmp(P->ime, ime) != 0)
	{
		P = P->next;
	}
	if (P == NULL)
	{
		printf("Trazeni direktorij ne postoji.\n");
		return NULL;
	}
	else
	{
		printf("Pronaden je direktorij %s\n", P->ime);
	}
	return P;
}

int umetnipodatke(Pozicija q)
{
	printf("Unesite ime direktorija.\n");
	scanf("%s", q->ime);
	return 0;
}
Pozicija stvoricvor(int n)
{
	Pozicija q;
	q = (Pozicija)malloc(n * sizeof(Direktorij));
	if (q == NULL)
	{
		printf("Greska u alociranju memorije.");
		return NULL;
	}
	q->next = NULL;
	q->child = NULL;
	return q;
}
pozicija stvoricvor1(int n)
{
	pozicija q;
	q = (pozicija)malloc(n * sizeof(Stog));
	if (q == NULL)
	{
		printf("Greska u alociranju memorije.");
		return NULL;
	}
	q->data = NULL;
	q->Next = NULL;
	return q;
}
int Push(Pozicija trenutni, pozicija stack)
{
	pozicija q = NULL;
	q = stvoricvor1(1);
	q->data = trenutni;
	q->Next = stack->Next;
	stack->Next = q;
	return 0;
}
