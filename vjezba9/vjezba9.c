/*. Napisati program koji omogućava rad s binarnim stablom pretraživanja.Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa.*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node;
typedef struct node* Pozicija;
typedef struct node
{
	int El;
	Pozicija Right;
	Pozicija Left;
}Node;

Pozicija Insert(Pozicija, int);
void Print(Pozicija);
Pozicija FindMin(Pozicija);
Pozicija FindMax(Pozicija);
Pozicija Delete(Pozicija, int);
Pozicija Find(Pozicija, int);

int main()
{
	Pozicija root = NULL;
	Pozicija find = NULL;
	char izbor = '0';
	int a = 0;
    while(izbor!='z')
	{
		printf("\nOdaberite: \n");
		printf("1.- Unos\n");
		printf("2.- Ispis\n");
		printf("3.- Brisanje\n");
		printf("4.- Trazenje\n");
		printf("Vas izbor je: \n");
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case '1':
		{
			printf("\nUnesite broj koji zelite dodati: ");
			scanf(" %d", &a);
			root = Insert(root, a);
			break;
		}
		case '2':
		{
			if (root == NULL)
				printf("\nStablo je prazno");
			else
				Print(root);
			break;
		}
		case '3':
		{
			printf("\nUnesite broj koji zelite izbrisati : ");
			scanf(" %d", &a);
			root = Delete(root, a);
			break;
		}
		case '4':
		{
			printf("\nUnesite broj koji trazite : ");
			scanf(" %d", &a);
			find = Find(root, a);
			if (find != NULL)
				printf("\nTrazeni element %d se nalazi na adresi %x", find->El, find);
			else
				printf("\nTrazeni broj %d nije pronaden.", a);
			break;
		}
		case 'z':
		{
			printf("Izlaz.\n");
			break;
		}
		default:
		{
			printf("\nPogresan izbor!\nPokusajte ponovno.\n");
		}
		}
	}
	return 0;
}

Pozicija Insert(Pozicija P, int n)
{
	if (P == NULL)
	{
		P = (Pozicija)malloc(sizeof(Node));
		if (P)
		{
			P->El = n;
			P->Left = NULL;
			P->Right = NULL;
		}
	}
	else if (P->El < n)
		P->Right = Insert(P->Right, n);
	else if (P->El > n)
		P->Left = Insert(P->Left, n);
	else
		printf("\nElement vec postoji u stablu.");
	return P;
}

void Print(Pozicija P)
{
	if (P != NULL)
	{
		Print(P->Left);
		printf(" %d", P->El);
		Print(P->Right);
	}
}

Pozicija FindMin(Pozicija P)
{
	if (P == NULL)
		return P;
	else if (P->Left == NULL)
		return P;
	else
		return FindMin(P->Left);
}

Pozicija FindMax(Pozicija P)
{
	if (P != NULL)
	{
		while (P->Right != NULL)
			P = P->Right;
	}
	return P;
}

Pozicija Find(Pozicija P, int n)
{
	if (P == NULL)
		return NULL;
	else
		if (P->El > n)
			return Find(P->Left, n);
		else if (P->El < n)
			return Find(P->Right, n);
		else
			return P;
}

Pozicija Delete(Pozicija P, int n)
{
	Pozicija tmp;
	if (P == NULL)
		printf("\nElement %d nije pronaden.", n);
	else if (n < P->El)
		P->Left = Delete(P->Left, n);
	else if (n > P->El)
		P->Right = Delete(P->Right, n);
	else
	{
		if (P->Left != NULL && P->Right != NULL)
		{
			//trazimo najveci element u lijevom podstablu ili najmanji u desnom
			tmp = FindMin(P->Right);
			P->El = tmp->El;
			P->Right = Delete(P->Right, tmp->El);
			/*tmp = FindMax(P->Left); tr
			P->El = tmp->El;
			P->Left = Delete(P->Left, tmp->El);*/
			
		}
		else
		{
			tmp = P;
			if (P->Left == NULL)
				P = P->Right;
			else
				P = P->Left;
			free(tmp);
		}
	}

	return P;
}
