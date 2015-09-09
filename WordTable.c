
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
	}

	// Word not found.

	// Make sure that the array has space.
	// Expand the wordArray here.
	if (wtable->nWords == wtable->maxWords)
	{
		wtable->wordArray=(WordInfo*)realloc(wtable->wordArray,wtable->maxWords*2*sizeof(WordInfo));
		for (int i = wtable->maxWords; i < wtable->maxWords * 2; i ++)
		{
			llist_init(&wtable->wordArray[i].positions);
		}
		wtable->maxWords *= 2;
	}

	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print( &wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	// Write your code here
	for (int i = 0; i < wtable->nWords; i ++)
	{
		if (strcmp(word, wtable->wordArray[i].word) == 0)
		{
			return &wtable->wordArray[i].positions;
		}
	}
	return NULL;
}

//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

#define isaletter(ch) ((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))



// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	// Write your code here
	int c = 0;
	char * word = malloc(sizeof(char) * 100);
	char * e = word;
	*word = fgetc(fd);
	if(*word == EOF)
	{
		return NULL;
	}
	while (1)
	{ 
		if (!isaletter(*word))
		{
			*word = '\0';
			return e;
		}
		word ++;
		*word = fgetc(fd);
	}
        return NULL;
}

// Conver string to lower case
void toLower(char *s) {
	// Write your code here
	// to convert one char to lower case. You have to do it for all chars in string.
	int i = 0;
	if (s == NULL)
	{
		return;
	}
	char ch = s[i];
	while (ch != '\0')
	{
		if (ch >= 'A' && ch <= 'Z')
		{
			ch = (ch - 'A') + 'a';
			s[i] = ch;
		}
		i ++;
		ch = s[i];
	}
}


// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
	// Write your code here
	FILE * fd = fopen(fileName, "r");
	if (fd == NULL)
	{
		return 0;
	}
	char * s;;
	int pos;
	int count = 0;
	pos = ftell(fd);
	s = nextword(fd);
	while (!isaletter(*s))
	{
		pos = ftell(fd);
		s = nextword(fd);
	}
	toLower(s);
	while (s != NULL)
	{
		wtable_add(wtable, s, pos);
		if (verbose == 1)
		{
			printf("%d: word=%s, pos=%d\n",count, s, pos);
		}
		count ++;
		pos = ftell(fd);
		s = nextword(fd);
		while (s!= NULL && !isaletter(*s) && *s == '\0')
		{
			pos = ftell(fd);
			s = nextword(fd);
		}
		toLower(s);
	}
	
	return 0;	
}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
	// Write your code here
	int i = 0;
	while(i < wtable->nWords - 1)
	{
		int j = i + 1;
		while(j < wtable->nWords)
		{
			if (strcmp(wtable->wordArray[i].word, 
wtable->wordArray[j].word) >= 1)
			{
				//Switch
				char * tempword = wtable->wordArray[i].word;
				wtable->wordArray[i].word = wtable->wordArray[j].word;
				wtable->wordArray[j].word = tempword;

				LinkedList temppos = wtable->wordArray[i].positions;
				wtable->wordArray[i].positions = wtable->wordArray[j].positions;
				wtable->wordArray[j].positions = temppos;
			}
			j ++;
		}
		i ++;
	}
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	// Write your code here
	printf("===== Segments for word \"%s\" in book \"%s\" =====\n", word, fileName);
	//Cycle through positions of the word and print 200 positions
	//after those positions
	LinkedList * temp = wtable_getPositions(wtable, word);
	ListNode * e;
	FILE * fd = fopen(fileName, "r");
	e = temp->head;
	while (e != NULL)
	{
		printf("---------- pos=%d-----\n......", e->value);
		fseek(fd, e->value, SEEK_SET);
		for (int i = 0; i < 200; i ++)
		{
			int ch = fgetc(fd);
			printf("%c", ch);
		}
		printf("......\n");
		e = e->next;
	}
}
