#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define PROGRAM_ERROR (-1)									
#define MALLOC_ERROR (0)									
#define LINE_LENGTH 128										

struct polinom;
typedef struct polinom* Position;
typedef struct polinom {
	int coef;
	int exp;
	Position Next;
}Polinom;

Position Stvori(void);
int UnosDat(Position pHead, Position dHead);
int UnosSort(Position Head, int coef, int exp);
int Ispis(Position Head);
int Dodaj(Position sum, int coef, int exp);
int Suma(Position pHead, Position dHead);
int Umnozak(Position pHead, Position dHead);
int UkloniDuple(Position Head);
int BrisiNula(Position Head);
int BrisiSve(Position Head);

int main(void) {
	Position pHead = NULL;	//Prvi polinom
	Position dHead = NULL;	//Drugi polinom
	Position sHead = NULL;	//Polinom sume
	Position uHead = NULL;	//Polinom umnoska

	pHead = Stvori();
	dHead = Stvori();

	UnosDat(pHead, dHead);

	printf("Prva lista:\n");
	Ispis(pHead);

	printf("\nDruga lista:\n");
	Ispis(dHead);


	sHead = Suma(pHead, dHead);
	if (sHead == NULL) {
		printf("\nGreska u zbrajanju!");
		return PROGRAM_ERROR;
	}

	printf("\nZbroj lista:\n");
	Ispis(sHead);

	uHead = Umnozak(pHead, dHead);
	if (uHead == NULL) {
		printf("\nGreska u mnozenju!");
		return PROGRAM_ERROR;
	}

	printf("\nLista umnoska:\n");
	Ispis(uHead);

	BrisiSve(pHead);

	BrisiSve(dHead);

	BrisiSve(sHead);

	BrisiSve(uHead);

	return EXIT_SUCCESS;
}

Position Stvori(void) {
	Position Head = NULL;
	Head = (Position)malloc(sizeof(Polinom));

	if (Head == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return MALLOC_ERROR;
	}

	Head->Next = NULL;
	Head->exp = 0;
	Head->coef = 0;
	return Head;
}

int UnosDat(Position pHead, Position dHead) {

	int coef = 0, exp = 0, n = 0;
	char buffer[LINE_LENGTH] = { 0 };
	char* buf = NULL;
	int unos = 0;

	FILE* fp = NULL;
	fp = fopen("polinomi.txt", "r");

	if (NULL == fp) {
		printf("Doslo je do pogreske, dokument polinomi.txt se nije otvorio!\r\n");
		return PROGRAM_ERROR;
	}

	fgets(buffer, LINE_LENGTH, fp);
	buf = buffer;

	while (strlen(buf) != 0) {
		sscanf(buf, "%d %d %n", &coef, &exp, &n);
		if (coef == 0) {
			buf += n;
		}
		else {
			unos = UnosSort(pHead, coef, exp);
			buf += n;
		}
	}

	fgets(buffer, LINE_LENGTH, fp);
	buf = buffer;

	while (strlen(buf) != 0) {
		sscanf(buf, "%d %d %n", &coef, &exp, &n);
		if (coef == 0) {
			buf += n;
		}
		else {
			unos = UnosSort(dHead, coef, exp);
			buf += n;
		}
	}

	return EXIT_SUCCESS;
}

int UnosSort(Position Head, int coef, int exp) {

	Position P = Head;
	Position N = NULL;	//Novi
	Position temp = NULL;

	while (P->Next != NULL && P->Next->exp >= exp) {
		P = P->Next;
	}

	N = (Position)malloc(sizeof(Polinom));

	if (N == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	N->coef = coef;
	N->exp = exp;

	N->Next = P->Next;
	P->Next = N;

	UkloniDuple(Head);
	BrisiNula(Head);
	return EXIT_SUCCESS;
}

int Ispis(Position Head) {
	Position P = Head->Next;  
	int prvi = 1;         

	while (P != NULL) {
		if (P->exp != 0) {
			if (P->coef >= 0 && !prvi) {
				printf(" + ");
			}
			printf("%dx^%d", P->coef, P->exp);
		}
		else {
			if (P->coef >= 0 && !prvi) {
				printf(" + ");
			}
			printf("%d", P->coef);
		}

		prvi = 0;
		P = P->Next;
	}

	printf("\n");
	return EXIT_SUCCESS;
}

int Dodaj(Position sum, int coef, int exp) {

	Position P = sum;
	Position D = NULL;

	while (P->Next != NULL) {
		P = P->Next;
	}

	D = (Position)malloc(sizeof(Polinom));

	if (D == NULL) {
		printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
		return PROGRAM_ERROR;
	}

	D->coef = coef;
	D->exp = exp;

	D->Next = P->Next;
	P->Next = D;

	return EXIT_SUCCESS;
}

int Suma(Position pHead, Position dHead) {

	Position P = pHead->Next;
	Position D = dHead->Next;
	Position sum = NULL;

	sum = Stvori();

	while (P != NULL && D != NULL) {

		if (P->exp > D->exp) {							//ako je potencija prvog veca od drugog
			Dodaj(sum, P->coef, P->exp);
			P = P->Next;
		}

		else if (P->exp < D->exp) {						//ako je potencija drugog veca od prvog
			Dodaj(sum, D->coef, D->exp);
			D = D->Next;
		}

		else if (P->exp == D->exp) {											//ako su iste potencije
			Dodaj(sum, P->coef + D->coef, P->exp);
			P = P->Next;
			D = D->Next;
		}
	}

	while (P != NULL) {									//ako ostane samo jedna
		Dodaj(sum, P->coef, P->exp);
		P = P->Next;
	}
	while (D != NULL) {
		Dodaj(sum, D->coef, D->exp);
		D = D->Next;
	}

	return sum;
}

int Umnozak(Position pHead, Position dHead) {

	Position P = pHead->Next;
	Position D = dHead->Next;
	Position umn = NULL;

	umn = Stvori();

	while (P != NULL) {
		while (D != NULL) {
			UnosSort(umn, P->coef * D->coef, P->exp + D->exp);
			D = D->Next;
		}
		P = P->Next;
		D = dHead->Next;
	}
	return umn;
}

int UkloniDuple(Position Head)
{
	Position P = Head;
	Position D = NULL;
	Position Z = NULL;

	if (P == NULL)
		return PROGRAM_ERROR;

	while (P->Next != NULL)
	{
		if (P->exp == P->Next->exp)					//ako uzastopne pozicije imaju isti eksponent, zbraja koeficijente, brise visak
		{
			P->coef = P->coef + P->Next->coef;
			D = P->Next->Next;
			free(P->Next);
			P->Next = D;

		}
		else
		{
			P = P->Next;
		}


	}
	return EXIT_SUCCESS;
}

int BrisiNula(Position Head) {
	Position P = Head;
	Position temp = P->Next;
	while (P->Next->Next != NULL && P->Next->coef != 0) {
		P = P->Next;
	}
	temp = P->Next;
	if (temp->coef == 0) {
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int BrisiSve(Position Head) {
	Position P = Head;
	Position temp = NULL;
	while (P->Next != NULL)
	{
		temp = P->Next;
		P->Next = temp->Next;
		free(temp);
	}
	return EXIT_SUCCESS;
}