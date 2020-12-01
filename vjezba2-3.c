/*2. Definirati strukturu osoba (ime, prezime, godina rodenja) i napisati program koji:
a) dinamicki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamicki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable.
3. Prethodnom zadatku dodati funkcije :
a) dinamièki dodaje novi element iza odreðenog elementa,
b) dinamièki dodaje novi element ispred odreðenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) èita listu iz datoteke.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 256
typedef struct osoba* Pozicija;
typedef struct osoba
{
	char ime[MAX];
	char prezime[MAX];
	int godinarodenja;
	Pozicija next;
}Osoba;
int UnosP(Pozicija P);

int Ispis(Pozicija P);
int UnosK(Pozicija P);
Pozicija TrazipoPrez(Pozicija P);
Pozicija Traziprethodni(Pozicija P);
int Brisielement(Pozicija P);
int Sortiranjeprez(Pozicija);
int Citajizdatoteke(Pozicija);
int Unososobe(Pozicija P);
int dodajiza(Pozicija P);
int dodajispred(Pozicija P);
int upisudatoteku(Pozicija P);
int main()
{
	Osoba head;
	head.next = NULL;
	char izbor = '0';
	char prezime[MAX];
	while (izbor != 'z')
	{
		printf("Odaberite: \n");
		printf("1- za dodavanje elementa na pocetak liste.\n");
		printf("2- za ispis liste.\n");
		printf("3- za dodavanje elementa na kraj liste.\n");
		printf("4-za trazenje elementa po prezimenu.\n");
		printf("5-za brisanje odredenog elementa.\n");
		printf("6-ako zelite dodati element iza odredenog elementa u listi.\n");
		printf("7-ako zelite dodati element ispred odredenog elementa u listi.\n");
		printf("8-ako zelite upisati listu u datoteku.\n");
		printf("z-za izlaz\n");
		printf("Vas izbor je: \n");
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
			UnosP(&head);
			break;
		case '2':
			Ispis(head.next);
			break;
		case '3':
			UnosK(&head);
			break;
		case '4':
			TrazipoPrez(head.next);
			break;
		case '5':
			Brisielement(&head);
			break;
		case '6':
			dodajiza(&head);
			break;
		case '7':
			dodajispred(&head);
			break;
		case '8':
			upisudatoteku(&head);
			break;
		case 'z':
			printf("Izlaz");
			break;
		default:
			printf("\nNepostojec izbor\n");
			break;
		}
	}
	return 0;
}
int Unososobe(Pozicija P)
{
	printf("Unesite ime: \n");
	scanf("%s", P->ime);
	printf("Unesite prezime: \n");
	scanf("%s", P->prezime);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &P->godinarodenja);
	return 0;

}
int UnosP(Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL)
	{
		printf("Greska!\n");
		return -1;
	}
	Unososobe(q);
	q->next = P->next;
	P->next = q;
	return 0;
}
int Ispis(Pozicija P)
{
	printf("Lista: \n");
	if (P == NULL)
	{
		printf("Prazna lista. \n");
		return -1;
	}
	while (P != NULL)
	{
		printf("ime: %s\n", P->ime);
		printf("prezime: %s\n", P->prezime);
		printf("godina rodenja: %d\n", P->godinarodenja);
		P = P->next;
	}
	printf("\n");
	return 0;
}
int UnosK(Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL)
	{
		printf("Greska!\n");
		return -1;
	}
	Unososobe(q);
	while (P->next != NULL)
	{
		P = P->next;
	}
	q->next = P->next;
	P->next = q;
	return 0;
}
Pozicija TrazipoPrez(Pozicija P)
{
	char prezime[MAX];
	printf("Unesite prezime koje zelite pretraziti: ");
	scanf("%s", prezime);
	Pozicija x = NULL;
	while (P != NULL)
	{
		if (strcmp(P->prezime, prezime) == 0)
		{
			printf("Pronadena osoba s prezimenom %s\n", prezime);
			printf("ime osobe: %s\n", P->ime);
			printf("prezime osobe: %s\n", P->prezime);
			printf("godina rodenja osobe: %d\n", P->godinarodenja);
			x = P;
		}
		P = P->next;
	}
	if (x == NULL)
	{
		printf("osoba s %s prezimenom ne postoji u listi.\n", prezime);
	}
}
Pozicija Traziprethodni(Pozicija P, Pozicija temp)
{
	while (P->next != temp)
		P = P->next;
	return P;
}

int Brisielement(Pozicija P)
{
	printf("Koji element zelite izbrisati?\n");
	Pozicija temp = TrazipoPrez(P);
	Pozicija prev = Traziprethodni(P, temp);
	prev->next = temp->next;
	free(temp);
	return 0;
}
int dodajiza(Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	Unososobe(q);
	printf("Iza kojeg clana zelite unijeti novi element? ");
	Pozicija a = TrazipoPrez(P);
	q->next = a->next;
	a->next = q;
	return 0;
}
int dodajispred(Pozicija P)
{
	Pozicija q = (Pozicija)malloc(sizeof(Osoba));
	Unososobe(q);
	printf("Ispred kojeg prezimena zelite ubaciti novi element? \n");
	Pozicija a = TrazipoPrez(P);
	Pozicija prev = Traziprethodni(P, a);
	prev->next = q;
	q->next = a;
	return 0;
}
int upisudatoteku(Pozicija P)
{
	FILE* fp;
	char imedatoteke[20] = { 0 };
	printf("Unesite ime datoteke: \n");
	scanf("%s", imedatoteke);
	fp = fopen(imedatoteke, "w");
	Pozicija temp = P->next;
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return -1;
	}
	else
	{
		while (temp != NULL)
		{
			fprintf(fp, "%s %s %d\n", temp->ime, temp->prezime, temp->godinarodenja);

			temp = temp->next;

		}
		fclose(fp);
	}
	return 0;
}
int Sortiranjeprez(Pozicija P)
{
	Pozicija pom, glavna, preth, end;
		end = NULL;
	while (P->next != end) 
	{
		preth = P;
		glavna = P->next;
	while (glavna->next != end) 
	{
		if (strcmp(glavna->prezime, glavna->next->prezime) > 0) 
		{
			pom = glavna->next;
			preth->next = pom;
			glavna->next = pom->next;
			pom->next = glavna;

			glavna = pom;
		}
		preth = glavna;
		glavna = glavna->next;
	}
	end = glavna;
}

return 0;

}
int Citajizdatoteke(Pozicija P)
{
		Pozicija temp = NULL;

		FILE* fp;
		char imedatoteke[20];

		printf("Unesite ime datoteke:\n\n");
		scanf("%s", &imedatoteke);

		fp = fopen(imedatoteke, "r");

		if (fp == NULL)
		{
			printf("Greska u otvaranju datoteke!\n");
			return -1;
		}

		while (!feof(fp))
		{
			temp = (Pozicija)malloc(sizeof(Osoba));

			fscanf(fp, "%s %s %d", temp->ime, temp->prezime, &temp->godinarodenja);

			temp->next = P->next;
			P->next = temp;
			P = temp;
		}
		fclose(fp);

		return 0;
	}

																														