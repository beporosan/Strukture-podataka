#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 1024
#define MAX_BODOVA 50.0
#define ERROR_OPENING_FILE 1
/*Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/


typedef struct {
    char ime[50];
    char prezime[50];
    int bodovi;
} Student;

int count_rows(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("error opening file!\n");
        return ERROR_OPENING_FILE;
    }

    int i = 0;
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, fp)) {
        i++;
    }

    fclose(fp);
    return i;
}

void read_student(const char* filename, Student* student, int br_studenta) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("error opening file!\n");
        return;
    }

    for (int i = 0; i < br_studenta; i++) {
        fscanf(fp, "%s %s %d", student[i].ime, student[i].prezime, &student[i].bodovi);
    }

    fclose(fp);
}

void print_student(Student* student, int br_studenta) {
    for (int i = 0; i < br_studenta; i++) {
        double relativniBodovi = (student[i].bodovi / MAX_BODOVA) * 100;
        printf("Ime: %s, Prezime: %s, Bodovi: %d, Relativni bodovi: %.2f%%\n",
            student[i].ime, student[i].prezime, student[i].bodovi, relativniBodovi);
    }
}

int main() {
    const char* file = "student.txt";

    int br_studenta = count_rows(file);
    if (br_studenta == -1) {
        return 1;
    }

    Student* student = (Student*)malloc(br_studenta * sizeof(Student));
    if (!student) {
        printf("Greska pri alociranju memorije.\n");
        return 1;
    }

    read_student(file, student, br_studenta);

    print_student(student, br_studenta);

    free(student);

    return 0;
}
