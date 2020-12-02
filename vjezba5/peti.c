/*Za dvije sortirane liste L1 i L2 (mogu se pro�itati iz datoteke ili unijeti ru�no,
		bitno je
		samo da su sortirane), napisati program koji stvara novu vezanu listu tako da ra�una :
		a) L1?L2,
		b) L1?L2.
		Liste osim pokaziva�a na slijede�u strukturu imaju i jedan cjelobrojni element, po
		kojem su sortirane*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

	typedef struct lista* Pozicija;
	typedef struct lista {
		int broj;
		Pozicija next;
	}Lista;

	int citajizDat(Pozicija);
	int ispis(Pozicija);
	int P(Pozicija, Pozicija, Pozicija);
	int U(Pozicija, Pozicija, Pozicija);

	int main() {
		Lista head1, head2, presjek, unija;

		head1.next = NULL;
		head2.next = NULL;
		presjek.next = NULL;
		unija.next = NULL;
		citajizDat(&head1);
		citajizDat(&head2);

		printf("\nLista1:");
		ispis(head1.next);
		printf("\nLista2:");
		ispis(head2.next);

		P(head1.next, head2.next, &presjek);

		printf("\nPresjek:");
		ispis(presjek.next);
		U(head1.next, head2.next, &unija);
		printf("\nUnija:");
		ispis(unija.next);

		return 0;
	}
	int citajizDat(Pozicija P) {
		Pozicija q, temp;
		char ime[20];
		FILE* fp;
		printf("Unesite ime datoteke:\n");
		scanf("%s", ime);

		fp = fopen(ime, "r");

		if (fp == NULL) {
			printf("Greska u otvaranju!");
			return -1;
		}


		while (!feof(fp)) {
			q = (Pozicija)malloc(sizeof(Lista));
			if (q == NULL) {
				printf("Greska!");
			}

			fscanf(fp, "%d", &q->broj);
			temp = P;

			while (temp->next != NULL && temp->next->broj <= q->broj)
				temp = temp->next;

			q->next = temp->next;
			temp->next = q;


		}
		fclose(fp);

		return 0;
	}
	int ispis(Pozicija P) {
		while (P != NULL) {
			printf(" %d", P->broj);
			P = P->next;
		}
		return 0;
	}
	int P(Pozicija P1, Pozicija P2, Pozicija  Pr) {
		Pozicija q, pom;
		pom = Pr;
		while (P1 && P2) {
			if (P1->broj < P2->broj)
				P1 = P1->next;
			else if (P1->broj > P2->broj)
				P2 = P2->next;

			else {
				Pozicija q;
				q = (Pozicija)malloc(sizeof(Lista));

				if (q == NULL) {
					printf("Greska");
				}

				q->broj = P1->broj;

				q->next = Pr->next;
				Pr->next = q;
				pom = q;

				P1 = P1->next;
				P2 = P2->next;
			}
		}




		return 0;
	}
	int U(Pozicija P1, Pozicija P2, Pozicija Un) {
		Pozicija q, pom, temp;
		pom = Un;
		while (P1 && P2) {
			q = (Pozicija)malloc(sizeof(Lista));
			if (q == NULL) {
				printf("Greska\n");
			}

			if (P1->broj < P2->broj) {
				q->broj = P1->broj;
				P1 = P1->next;
			}
			else if (P1->broj > P2->broj) {
				q->broj = P2->broj;
				P2 = P2->next;
			}

			else {
				q->broj = P1->broj;
				P1 = P1->next;
				P2 = P2->next;
			}

			if (pom->broj == q->broj)
				free(q);

			else {
				q->next = pom->next;
				pom->next = q;
				pom = q;
			}
		}

		if (P1)
			temp = P1;
		else
			temp = P2;

		while (temp) {
			q = (Pozicija)malloc(sizeof(Lista));
			if (q == NULL)
			{
				printf("Greska");
				break;
			}
			else
			{
				q->broj = temp->broj;

				if (pom->broj == q->broj)
					free(q);
				else
				{
					q->next = pom->next;
					pom->next = q;
					pom = q;
				}

				temp = temp->next;
			}
		}



		return 0;
	}
