/*Napisati program koji iz datoteke čita postfiks izraz i zatim stvara stablo proračuna.Iz
gotovog stabla proračuna upisati u datoteku infiks izraz. */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SIZE 11

typedef struct Tree
{
	char data[DATA_SIZE];
	struct Tree* left;
	struct Tree* right;
}Tree;

typedef struct List
{
	struct Tree* treeNode;
	struct List* next;
}List;

Tree* Create(char* data)
{
	Tree* new = (Tree*)malloc(sizeof(Tree));
	if (new == NULL)
	{
		printf("Malloc failed!");
		return -1;
	}
	strcpy(new->data, data);
	new->left = NULL;
	new->right = NULL;
	return new;
}

int PushFront(List* head, Tree* treeNode)
{
	List* position = (List*)malloc(sizeof(List));
	if (position == NULL)
	{
		printf("Malloc failed!");
		return -1;
	}
	position->treeNode = treeNode;
	position->next = head->next;
	head->next = position;
}

int PushBack(List* head, Tree* treeNode)
{
	List* temp = head;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	return PushFront(temp, treeNode);
}

Tree* PopFront(List* head)
{
	List* first = head->next;
	Tree* result = NULL;
	if (first == NULL)
	{
		return 0;
	}
	head->next = first->next;
	result = first->treeNode;
	free(first);
	return result;
}

int IsNumber(char* data)
{
	int number = 0;
	if (sscanf(data, " %d", &number) == 1)
	{
		return 1;
	}
	return 0;
}

Tree* ReadFromFile(char* filename)
{
	FILE* data = fopen(filename, "r");
	List head;
	head.next = NULL;
	Tree* result = NULL;
	char character[DATA_SIZE] = { 0 };
	if (data == NULL)
	{
		printf("\nDatoteka ne postoji!");
		return 0;
	}
	else
	{
		while (feof(data) != 1)
		{
			Tree* node = NULL;
			node = Create(character);
			if (node == NULL)
			{
				fclose(data);
				return 0;
			}
			fscanf(data, "%s", &character);
			if (IsNumber(character) != 0)
			{
				PushFront(&head, node);
			}
			else
			{
				PopFront(&head);
				if (node == NULL)
				{
					printf("\nKrivi postfix zapis! 04");
					return 0;
				}
				node->left = PopFront(&head);
				if (node->left == NULL)
				{
					printf("\nKrivi postfix zapis! 03");
					return 0;
				}
				PushFront(&head, node);
			}
		}
	}
	result = PopFront(&head);
	if (result == NULL)
	{
		printf("\nKrivi postfix zapis! 01");
	}
	if (PopFront(&head) != NULL)
	{
		printf("\nKrivi postfix zapis! 02");
	}
	else
	{
		return result;
	}
}

void PrintInOrder(List* head, Tree* current)
{
	if (current == NULL)
	{
		return;
	}
	PrintInOrder(head, current->left);
	PushBack(head, current);
	PrintInOrder(head, current->right);
}

int main()
{
	char filename[1024] = { 0 };
	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);
	Tree* test = ReadFromFile(filename);
	if (test == NULL)
	{
		return 1;
	}
	List head;
	head.next = NULL;
	PrintInOrder(&head, test);
	List* p;
	for (p = head.next, p != NULL; p = p->next;)
	{
		printf("%d");
	}
	;
	return 0;
}
