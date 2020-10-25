/*2. Definirati strukturu osoba (ime, prezime, godina rodenja) i napisati program koji:
a) dinamicki dodaje novi element na poèetak liste,
b) ispisuje listu,
c) dinamicki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odreðeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable.*/
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
void UnosP(Pozicija P);

void Ispis(Pozicija P);
void UnosK(Pozicija P);
Pozicija TrazipoPrez(Pozicija P);
Pozicija Trazipreth(char*, Pozicija P);
void Brisi(char*, Pozicija P);
void Unososobe(Pozicija P);
int main()
{
	Osoba head;
	head.next = NULL;
	char izbor='0';
	char prezime[MAX];
	while (izbor != 'z')
	{
		printf("Odaberite: \n");
		printf("1- za dodavanje elementa na pocetak liste.\n");
		printf("2- za ispis liste.\n");
		printf("3- za dodavanje elementa na kraj liste.\n");
		printf("4-za trazenje elementa po prezimenu.\n");
		printf("5-za brisanje odredenog elementa.\n");
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
			printf("Unesite prezime koje zelite izbrisati: ");
			scanf("%s", prezime);
			Brisi(prezime, &head);
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
void Unososobe(Pozicija P)
{
	printf("Unesite ime: \n");
	scanf("%s", P->ime);
	printf("Unesite prezime: \n");
	scanf("%s", P->prezime);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &P->godinarodenja);

}
void UnosP(Pozicija P)
{
	Pozicija q;
	q= (Pozicija)malloc(sizeof(Osoba));
	Unososobe(q);
	q->next = P->next;
	P->next = q;
}
void Ispis(Pozicija P)
{
	printf("Lista: \n");
	if (P == NULL)
	{
		printf("Prazna lista. \n");
	}
	while (P != NULL)
	{
		printf("ime: %s\n", P->ime);
		printf("prezime: %s\n", P->prezime);
		printf("godina rodenja: %d\n", P->godinarodenja);
		P = P->next;
	}
	printf("\n");
}
void UnosK(Pozicija P)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	Unososobe(q);
	while (P->next != NULL)
	{
		P = P->next;
	}
	q->next = P->next;
	P->next = q;
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
Pozicija TraziPreth(char* prezime, Pozicija P)
{
	Pozicija prev = P;
	P = P->next;
	while (P != NULL && strcmp(P->prezime, prezime))
	{
		prev = P;
		P = P->next;
	}
	if (P == NULL)
	{
		printf("Element ne postoji u listi. ");
		return NULL;
	}
	return prev;
}
void Brisi(char* prezime, Pozicija P)
{
	Pozicija prev;
	prev = TraziPreth(prezime, P);
	if (prev != NULL)
	{
		P = prev->next;
		prev->next = P->next;
		free(P);
	}
}




