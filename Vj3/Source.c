#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE (1024)
#define PROGRAM_ERROR (-1)
#define NOT_FOUND (0)

struct osoba;
typedef struct osoba* Position;
struct osoba {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int godina;
	Position Next;
};

int BrisiSve(Position P);
int UnosP(Position P);
int UnosK(Position P);
Position Trazi(Position P);
int Brisi(Position P);
int Ispis(Position P);
int UnosO(Position P);
int UnosIza(Position P);
int UnosIspred(Position P);
int Sort(Position P);
int UnosDat(Position P);
int IspisDat(Position P);

int main(void) {
	struct osoba Head = {
		.ime = {0},
		.prezime = {0},
		.godina = 0,
		.Next = NULL
	};
	int op = 0;

	do {
		op = 0;
		printf(
			"*\t*\t*\t*\n"
			"Odaberite zeljenu operaciju:\n"
			"1) Dodaj na pocetak\n"
			"2) Dodaj na kraj\n"
			"3) Trazi po prezimenu\n"
			"4) Brisi zeljeni element\n"
			"5) Ispis liste\n"
			"6) Unos iza osobe\n"
			"7) Unos ispred osobe\n"
			"8) Sortiranje osoba\n"
			"9) Unos osoba u dokument\n"
			"10) Ispis osoba iz dokument\n"
			"0) Izlaz\n"
			"*\t*\t*\t*\n");
		scanf_s(" %d", &op);

		switch (op) {
		case 1:
			printf("Odabrali ste unos na pocetak:\n");
			UnosP(&Head);
			break;
		case 2:
			printf("Odabrali ste unos na kraj:\n");
			UnosK(&Head);
			break;
		case 3:
			printf("Odabrali ste trazenje po prezimenu:\n");
			Trazi(Head.Next);
			break;
		case 4:
			printf("Odabrali ste brisanje osobe:\n");
			Brisi(&Head);
			break;
		case 5:
			printf("Odabrali ste ispis liste:\n");
			Ispis(Head.Next);
			break;
		case 6:
			printf("Odabrali ste unos iza osobe:\n");
			UnosIza(&Head);
			break;
		case 7:
			printf("Odabrali ste unos ispred osobe:\n");
			UnosIspred(&Head);
			break;
		case 8:
			printf("Odabrali ste sortiranje osoba:\n");
			Sort(&Head);
			break;
		case 9:
			printf("Odabrali ste unos osoba u dokument:\n");
			UnosDat(Head.Next);
			break;
		case 10:
			printf("Odabrali ste ispis osoba iz dokument:\n");
			IspisDat(Head.Next);
			break;
		case 0:
			printf("Odabrali ste izlaz:\n");
			break;
		}
	} while (op != 0);

	BrisiSve(&Head);
	return EXIT_SUCCESS;
}

int UnosP(Position P) {
	Position Q;

	Q = (Position)malloc(sizeof(struct osoba));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	UnosO(Q);

	Q->Next = P->Next;
	P->Next = Q;

	return EXIT_SUCCESS;
}

int UnosK(Position P) {
	Position Q;

	while (P->Next != NULL) {
		P = P->Next;
	}

	Q = (Position)malloc(sizeof(struct osoba));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	UnosO(Q);
	P->Next = Q;
	Q->Next = NULL;

	return EXIT_SUCCESS;
}

Position Trazi(Position P) {
	char trazenoPrezime[MAX_LINE] = { 0 };
	int brojac = 0;

	printf("Unesite prezime trazene osobe: ");
	scanf_s(" %s", trazenoPrezime, MAX_LINE);

	while (P != NULL && strcmp(trazenoPrezime, P->prezime) != 0) {
		P = P->Next;
		brojac++;
	}

	if (P != NULL) {
		printf("Trazena osoba nalazi se na %d. mjestu.\n", brojac);
		return P;
	}
	else {
		printf("Nije pronadena trazena osoba!");
		return NOT_FOUND;
	}
}


int Brisi(Position P) {

	Position temp = NULL;

	temp = Trazi(P);
	
	if (temp != NULL) {
		P->Next = temp->Next;
		free(temp);
	}

	return EXIT_SUCCESS;
}

int Ispis(Position P) {
	while (P != NULL) {
		printf("%s ", P->ime);
		printf("%s ", P->prezime);
		printf("%d\n", P->godina);
		P = P->Next;
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int BrisiSve(Position P) {
	Position temp;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int UnosO(Position P) {
	printf("Ime nove osobe: ");
	scanf_s("%s", P->ime, MAX_LINE);
	printf("Prezime nove osobe: ");
	scanf_s("%s", P->prezime, MAX_LINE);
	printf("Godina rodenja nove osobe: ");
	scanf_s("%d", &(P->godina));

	return EXIT_SUCCESS;
}

int UnosIza(Position P) {
	Position Q;
	char trazenoPrezime[MAX_LINE] = { 0 };

	Q = (Position)malloc(sizeof(struct osoba));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	printf("Unesite prezime trazene osobe: ");
	scanf_s("%s", trazenoPrezime, MAX_LINE);

	while (P != NULL && strcmp(trazenoPrezime, P->prezime) != 0) {
		P = P->Next;
	}

	if (P != NULL) {
		UnosO(Q);
		Q->Next = P->Next;
		P->Next = Q;
	}
	else {
		printf("Nije pronadena trazena osoba!");
		return PROGRAM_ERROR;
	}
	return EXIT_SUCCESS;
}

int UnosIspred(Position P) {
	Position Q;
	char trazenoPrezime[MAX_LINE] = { 0 };

	Q = (Position)malloc(sizeof(struct osoba));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	printf("Unesite prezime trazene osobe: ");
	scanf_s("%s", trazenoPrezime, MAX_LINE);

	while (P->Next != NULL && strcmp(trazenoPrezime, P->Next->prezime) != 0) {
		P = P->Next;
	}

	if (P->Next != NULL) {
		UnosO(Q);
		Q->Next = P->Next;
		P->Next = Q;
	}
	else {
		printf("Nije pronadena trazena osoba!");
		return PROGRAM_ERROR;
	}
	return EXIT_SUCCESS;
}
int Sort(Position P) {
	Position Q, prev_Q, temp, end;

	Q = (Position)malloc(sizeof(struct osoba));

	if (Q == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	end = NULL;

	while (P->Next != end) {
		prev_Q = P;
		Q = P->Next;
		while (Q->Next != end) {
			if (strcmp(Q->prezime, Q->Next->prezime) > 0) {
				temp = Q->Next;
				prev_Q->Next = temp;
				Q->Next = temp->Next;
				temp->Next = Q;

				Q = temp;
			}
			prev_Q = Q;
			Q = Q->Next;
		}
		end = Q;
	}
	return EXIT_SUCCESS;
}

int UnosDat(Position P) {

	FILE* fp = NULL;

	fp = fopen("Osobe.txt", "w");
	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument Osobe.txt se nije otvorio!\r\n");
		return PROGRAM_ERROR;
	}

	while (P != NULL) {
		fprintf(fp, "\nIme osobe: %s\nPrezime osobe: %s\nGodina rodenja: %d\n", P->ime, P->prezime, P->godina);
		P = P->Next;
	}
	fclose(fp);
	return EXIT_SUCCESS;
}

int IspisDat(Position P) {
	char ime[MAX_LINE] = { 0 };
	char prezime[MAX_LINE] = { 0 };
	int godina = 0;

	FILE* fp = NULL;

	fp = fopen("Osobe.txt", "r");
	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument Osobe.txt se nije otvorio!\r\n");
		return PROGRAM_ERROR;
	}

	while (P != NULL) {
		fscanf(fp, "\nIme osobe: %s\nPrezime osobe: %s\nGodina rodenja: %d\n", &ime, &prezime, &godina);
		printf("\nIme osobe: %s\nPrezime osobe: %s\nGodina rodenja: %d\n", ime, prezime, godina);
		P = P->Next;
	}
	fclose(fp);

	return EXIT_SUCCESS;
}