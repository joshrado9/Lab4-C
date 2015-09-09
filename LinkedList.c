
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode * e;
	if (list->head == NULL)
	{
		return 0;
	}
	e = list->head;
	while (e != NULL)
	{
		if (e->value == value)
		{
			return 1;
		}
		e = e->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * e;
	if (list->head == NULL)
	{
		return 0;
	}
	e = list->head;
	if (e->value == value)
	{
		list->head = e->next;
	}
	while (e->next != NULL)
	{
		if (e->next->value == value)
		{
			e->next = e->next->next;
			return 1;
		}
		e = e->next;
	}
	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode * e;
	if (list->head == NULL)
	{
		return 0;
	}
	e = list->head;
	int count = 0;
	while (e != NULL && count < ith)
	{
		e = e->next;
		count ++;
	}
	if (count == ith)
	{
		*value = e->value;
		return 1;
	}
	return 0;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * e;
	if (list->head == NULL)
	{
		return 0;
	}
	e = list->head;
	int count = 0;
	while (e != NULL && count < ith - 1)
	{
		e = e->next;
		count ++;
	}
	if (count == ith - 1)
	{
		e->next = e->next->next;
		return 1;
	}
	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	ListNode * e;
	if (list->head == NULL)
	{
		return 0;
	}
	e = list->head;
	int count = 0;
	while (e != NULL)
	{
		count ++;
		e = e->next;
	}
	return count;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	ListNode * e;
	FILE * fd = fopen(file_name, "w");
	if (fd == NULL)
	{
		return 0;
	}
	e = list->head;
	while (e != NULL)
	{
		fprintf(fd, "%d\n", e->value);
		e = e->next;
	}
	fclose(fd);
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	ListNode * e;
	FILE * fd = fopen(file_name, "r");
	if (fd == NULL)
	{
		return 0;
	}
	e = list->head;
	if (e != NULL)
	{
		list->head = NULL;
	}
	int val = 0;
	fscanf(fd, "%d", &val);
	while (!feof(fd))
	{
		llist_add(list, val);
		fscanf(fd, "%d", &val);
	}
	
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
	ListNode * e;
	e = list->head;
	int llength = llist_number_elements(list);
	int counti = 0;
	while (counti < llength)
	{
		int countj = 0;
		while (countj < llength - counti)
		{
			ListNode * f = e;
			int i = 0;
			while (i < countj)
			{
				f = f->next;
				i++;
			}
			if (ascending)
			{
				if (e->value > f->value)
				{
					int tempval = e->value;
					e->value = f->value;
					f->value = tempval;
				}
			}
			else
			{
				if (e->value < f->value)
				{
					int tempval = e->value;
					e->value = f->value;
					f->value = tempval;
				}
			}
			countj ++;
		}
		e = e->next;
		counti ++;
	}
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	ListNode * e;
	if (list->head == NULL)
	{
		return 0;
	}
	e = list->head;
	*value = e->value;
	list->head = e->next;
	free(e);
	return 1;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
	ListNode * e;
	if (list->head == NULL)
	{
		return 0;
	}
	e = list->head;
	while (e->next->next != NULL)
	{
		e = e->next;
	}
	*value = e->next->value;
	free(e->next);
	e->next = NULL;
	return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
		llist_add(list, value);
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
	ListNode * e;
	if (list->head == NULL)
	{
		llist_add(list, value);
		return;
	}
	e = list->head;
	while(e->next != NULL)
	{
		e = e->next;
	}
	ListNode * n = (ListNode *)  malloc(sizeof(ListNode));
	n->value = value;
	n->next = NULL;
	
	e->next = n;
	
	
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
	ListNode * e;
	e = list->head;
	while (e != NULL)
	{
		free(e);
		e = e->next;
	}
	list->head = NULL;
}
