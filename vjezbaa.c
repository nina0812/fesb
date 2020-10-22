#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Studenti
{
	char ime[20];
	char prezime[20];
	int apsolutnibrojb;
	float relativnibrojb;
}Student;
Student* Dinamickaalokacijamemorije(int a);
int brojanjeredaka(char niz[]);
void citanje(char niz[], int a, Student* listaStudenata);
void ispisStudenata(int a, Student* listaStudenata);

int main()
{
	Student* listaStudenata;
	int broj;
	char niz[100] = { 0 };
	broj = brojanjeredaka(niz);
	printf("Broj redaka je: %d\n", broj);
	listaStudenata = Dinamickaalokacijamemorije(broj);
	citanje(niz, broj, listaStudenata);
	ispisStudenata(broj, listaStudenata);
	return 0;
}
int brojanjeredaka(char niz[])
{
	FILE* fp;
	fp = fopen("studenti.txt", "r");
	int brojac = 0;
	int i;
	if (fp == NULL)
	{
		printf("Datoteka nije dobro otvorena.\n");
	}
	else
	{
		printf("Dobro otvorena datoteka.\n");
	}
	//citanje redaka
	printf("\n");
	while (!feof(fp))
	{
		strcpy(niz, "\0");
		fgets(niz, 100, fp);
		if (strlen(niz) > 1)
		{
			brojac++;
		}

	}
	return brojac;
	fclose(fp);
}
Student* Dinamickaalokacijamemorije(int n)
{
	return (Student*)malloc(n * sizeof(Student));
}
void citanje(char niz[], int a, Student* listaStudenata)
{
	int i = 0;
	int max = 0;
	FILE* fp;
	fp = fopen("studenti.txt", "r");
	if (fp == NULL)
	{
		printf("Nije dobro otvorena datoteka.");
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %d", listaStudenata[i].ime, listaStudenata[i].prezime, &listaStudenata[i].apsolutnibrojb);
			if (listaStudenata[i].apsolutnibrojb > max)
				max = listaStudenata[i].apsolutnibrojb;
			i++;
		}
	}
	fclose(fp);
	for (i = 0; i < a; i++)
	{
		listaStudenata[i].relativnibrojb = listaStudenata[i].apsolutnibrojb / (float)max * 100;
	}
}
void ispisStudenata(int a, Student* listaStudenata)
{
	int i = 0;
	for (i = 0; i < a; i++)
	{
		printf("%s %s %d %f", listaStudenata[i].ime, listaStudenata[i].prezime, listaStudenata[i].apsolutnibrojb, listaStudenata[i].relativnibrojb);
		printf("\n");
	}
}
