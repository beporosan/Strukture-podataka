#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _person* position;

typedef struct _person {

	char fname[32], lname[32];
	int birth_year;

	position next;
}person;

position create_person(position head, char* fname, char* lname, int birth_year);
int prepend_list(position head, char* fname, char* lname, int birth_year);
int append_list(position head, char* fname, char* lname, int birth_year);
//int insert_after(position previous, position to_insert);
int print_list(position first);
position find_last(position head);
position find_by_lname(position first, char* lname);
//find_previous

int main() {
	person head = { .fname = "",.lname = "", .birth_year = 0 };


	return 0;
}

position create_person(position head, char* fname, char* lname, int birth_year) {
	position new_person = NULL;
	new_person = (position*)malloc(sizeof(person));
	if (!new_person) {
		printf("Malloc failed");
		return NULL;
	}

	strcpy(new_person->fname, fname);
	strcpy(new_person->lname, lname);
	new_person->birth_year = birth_year;
	new_person->next = NULL;
	return new_person;

}

int prepend_list(position head, char* fname, char* lname, int birth_year) {
	position new_person = NULL;
	new_person = create_person(fname, lname, birth_year);
	if (!new_person) {
		return -1;
	}
	new_person->next = head->next; 
	head->next = new_person;
	return EXIT_SUCCESS;
}


int append_list(position head, char* fname, char* lname, int birth_year) {
	position new_person = NULL, last = NULL;
	new_person = create_person( fname, lname, birth_year);
	if (!new_person) {
		return -1;
	}
	new_person->next = last->next;
	last = find_last(head);
	last->next = new_person;
	//int insert_after(position previous, position to_insert);
}

int print_list(position first) {
	position temp = first;
	while (temp)
	{
		printf("First name: %s\n Last name: %s \n Godina %d");
		temp = temp->next;
	}
}

position find_last(position head) {
	position temp = head;
	while (temp->next) {
		temp = temp->next;
	}
	return temp;
}

position find_by_lname(position first, char* lname) {
	position temp;
	temp = first;

	while (temp) {
		if (strcmp(temp->lname,lname) == 0){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}